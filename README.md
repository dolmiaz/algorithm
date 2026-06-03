# C++ Competitive Programming Template

競技プログラミング向けの C++17 テンプレート集です。

`main.cpp` は AtCoder などにそのまま貼り付ける提出用の「全部入りテンプレート」として残しつつ、今後ライブラリとして育てやすいように、再利用可能な部品を `library/`、問題ごとに改造する雛形を `snippets/` に分けています。

## Environment

- Language: C++17
- Compiler assumption: GCC / Clang with GNU extension support
- Main dependency: standard library and `bits/stdc++.h`
- License: MIT License

`bits/stdc++.h` を使っているため、標準C++だけの環境ではそのままコンパイルできない場合があります。

## Repository Layout

```text
algorithm/
├── main.cpp
├── library/
│   ├── basic.hpp
│   ├── io.hpp
│   ├── grid.hpp
│   ├── cumsum.hpp
│   ├── binary_search.hpp
│   ├── graph.hpp
│   ├── graph_search.hpp
│   └── shortest_path.hpp
├── snippets/
│   └── dp.cpp
└── README.md
```

## File Roles

- `main.cpp`: 提出用の全部入りテンプレートです。基本型、入出力補助、グリッド、累積和、二分探索、グラフ、DFS/BFS、連結成分、Dijkstra、`solve()` / `main()` を単一ファイルにまとめています。
- `library/`: そのまま再利用できる完成済みの関数・構造体を置く場所です。各ヘッダには `#pragma once` と短い説明コメントを付けています。
- `snippets/`: 問題ごとに状態や遷移を書き換える前提の雛形を置く場所です。
- `verify/`: 動作確認用コードを置く場所です。

## Library Files

| File | Contents |
| --- | --- |
| `library/basic.hpp` | `ll`, `ull`, `ld`, `V<T>`, priority queue alias, `pii`, `pll`, `INF`, `INF_L`, `PI`, `rep`, `all` などの基本要素 |
| `library/io.hpp` | `println`, `printAll`, `yes`, `YES`, `chmin`, `chmax`, `ceil_div`, `floor_div`, `yc` などの出力・汎用補助 |
| `library/grid.hpp` | `DR4`, `DC4`, `DIR4`, `DR8`, `DC8`, `DIR8`, `in_grid` などのグリッド探索補助 |
| `library/cumsum.hpp` | `prefix_sum_1d`, `prefix_sum_2d`, `range_sum_1d`, `range_sum_2d`, `prefix_max_1d` |
| `library/binary_search.hpp` | `binary_search_index`, `first_ge`, `first_gt`, `last_lt`, `last_le`, `binary_search_min`, `binary_search_max` |
| `library/graph.hpp` | `Edge`, `Graph`, `add_edge`, `add_edge_internal`, `read_graph` |
| `library/graph_search.hpp` | `DFS_Info`, `dfs_all`, `BFS_Info`, `bfs`, `bfs_multi`, `restore_path`, `CC_Info`, `connected_components` |
| `library/shortest_path.hpp` | `Dijkstra_Info`, `dijkstra`, `restore_shortest_path` |

既存の `library/dsu.hpp`, `library/fenwick.hpp`, `library/segtree.hpp`, `library/modint.hpp`, `library/string.hpp`, `library/tree.hpp` は、今後の拡張用ファイルとして残しています。

## Snippets

| File | Contents |
| --- | --- |
| `snippets/dp.cpp` | DP の状態・初期値・遷移を問題ごとに書き換えるための雛形 |

既存の `snippets/*_test.cpp` は動作確認や検証用の一時コードとして残しています。

## Usage

提出用には `main.cpp` の `solve()` を問題ごとに書き換えて使います。

```bash
g++ -std=gnu++17 -O2 -Wall -Wextra main.cpp -o main
```

複数テストケース形式の問題では、コンパイル時に `MULTI_TEST_CASES=1` を定義します。

```bash
g++ -std=gnu++17 -O2 -Wall -Wextra -DMULTI_TEST_CASES=1 main.cpp -o main
```

ライブラリとして使う場合は、必要なヘッダだけを include します。

```cpp
#include "library/basic.hpp"
#include "library/graph.hpp"
#include "library/shortest_path.hpp"
```

## Notes

- `main.cpp` は include だけの短いファイルにはせず、提出先に貼れる全部入りテンプレートとして維持します。
- `library/` は完成済み部品、`snippets/` は問題ごとに編集する雛形として使い分けます。
- グラフの外部 index は `Graph::one_indexed` に従います。アルゴリズム内部の配列添字は 0-indexed です。
- 二分探索補助は、対象配列がソート済みであることを前提にしています。

## TODO

- DSU
- Fenwick Tree
- Segment Tree
- modint
- SCC
- LCA
- Z Algorithm
