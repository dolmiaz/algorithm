#!/usr/bin/env python3
"""Bundle library headers into main.cpp for submission.

library/*.hpp を用途別グループごとの依存順に展開し、
main.cpp の解答用セクション以降を残して提出用の全部入りテンプレートを更新する。
"""

from __future__ import annotations

import re
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
LIBRARY_DIR = ROOT / "library"
MAIN_CPP = ROOT / "main.cpp"
SOLUTION_MARKER = "// ============== 解答用 =============="

LOCAL_INCLUDE_RE = re.compile(r'^\s*#include\s+"([^"]+)"\s*$')
SYSTEM_INCLUDE_RE = re.compile(r"^\s*#include\s*<([^>]+)>\s*$")
HEADER_GROUPS = [
    ("Base", [
        "basic.hpp",
        "io.hpp",
    ]),
    ("Grid", [
        "grid.hpp",
        "grid_search.hpp",
    ]),
    ("Range / Prefix", [
        "cumsum.hpp",
        "imos.hpp",
        "fenwick.hpp",
    ]),
    ("Math / Number Theory", [
        "math.hpp",
        "modint.hpp",
        "number_theory.hpp",
        "crt.hpp",
        "floor_sum.hpp",
        "mobius.hpp",
        "prime_test.hpp",
        "pollard_rho.hpp",
        "discrete_log.hpp",
        "primitive_root.hpp",
        "garner.hpp",
    ]),
    ("Linear Algebra / Polynomial", [
        "matrix.hpp",
        "linear_algebra.hpp",
        "xor_basis.hpp",
        "convolution.hpp",
        "fps.hpp",
        "linear_recurrence.hpp",
        "berlekamp_massey.hpp",
        "subset_transform.hpp",
        "fwht.hpp",
    ]),
    ("Index / Search", [
        "compress.hpp",
        "binary_search.hpp",
    ]),
    ("Set / Connectivity", [
        "dsu.hpp",
    ]),
    ("Graph", [
        "graph.hpp",
        "graph_search.hpp",
        "shortest_path.hpp",
        "dag.hpp",
        "coloring.hpp",
    ]),
]


def resolve_header(name: str, current_dir: Path) -> Path:
    candidates = [
        current_dir / name,
        LIBRARY_DIR / name,
        ROOT / name,
    ]
    for path in candidates:
        if path.exists():
            return path.resolve()
    raise FileNotFoundError(f"local include not found: {name}")


def collect_headers(path: Path, seen: set[Path], order: list[Path]) -> None:
    path = path.resolve()
    if path in seen:
        return

    seen.add(path)
    text = path.read_text(encoding="utf-8")
    for line in text.splitlines():
        match = LOCAL_INCLUDE_RE.match(line)
        if match:
            collect_headers(resolve_header(match.group(1), path.parent), seen, order)

    order.append(path)


def body_without_guards(path: Path, system_includes: set[str]) -> str:
    lines: list[str] = []
    for line in path.read_text(encoding="utf-8").splitlines():
        if line.strip() == "#pragma once":
            continue
        if LOCAL_INCLUDE_RE.match(line):
            continue
        system_match = SYSTEM_INCLUDE_RE.match(line)
        if system_match:
            system_includes.add(system_match.group(1))
            continue
        if line.strip() == "using namespace std;":
            continue
        lines.append(line.rstrip())

    while lines and lines[0] == "":
        lines.pop(0)
    while lines and lines[-1] == "":
        lines.pop()

    return "\n".join(lines)


def solution_section() -> str:
    text = MAIN_CPP.read_text(encoding="utf-8")
    pos = text.find(SOLUTION_MARKER)
    if pos == -1:
        raise RuntimeError(f"{SOLUTION_MARKER!r} not found in main.cpp")
    return text[pos:].rstrip() + "\n"


def main() -> None:
    header_order = [name for _, names in HEADER_GROUPS for name in names]
    priority = {name: i for i, name in enumerate(header_order)}
    grouped_names = set(header_order)
    remaining_headers = sorted(
        (path for path in LIBRARY_DIR.glob("*.hpp") if path.name not in grouped_names),
        key=lambda path: (priority.get(path.name, len(priority)), path.name),
    )
    seen: set[Path] = set()
    groups: list[tuple[str, list[Path]]] = []

    for group_name, names in HEADER_GROUPS:
        order: list[Path] = []
        for name in names:
            header = LIBRARY_DIR / name
            if header.exists():
                collect_headers(header, seen, order)
        groups.append((group_name, order))

    if remaining_headers:
        order = []
        for header in remaining_headers:
            collect_headers(header, seen, order)
        groups.append(("Other", order))

    system_includes: set[str] = set()
    group_parts: list[str] = []
    for group_name, order in groups:
        parts: list[str] = []
        for header in order:
            body = body_without_guards(header, system_includes)
            if not body:
                continue
            rel = header.relative_to(ROOT)
            parts.append(f"// ===== bundled from {rel} =====\n{body}")
        if parts:
            group_parts.append(f"// ===== {group_name} =====\n\n" + "\n\n".join(parts))

    include_lines = "\n".join(f"#include <{name}>" for name in sorted(system_includes))
    bundled = (
        f"{include_lines}\n"
        "using namespace std;\n\n"
        + "\n\n".join(group_parts).rstrip()
        + "\n\n"
        + solution_section()
    )

    MAIN_CPP.write_text(bundled, encoding="utf-8")


if __name__ == "__main__":
    main()
