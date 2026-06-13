#!/usr/bin/env bash
set -euo pipefail

CXX=${CXX:-g++}
CXXFLAGS="-std=gnu++17 -O2 -Wall -Wextra -I."

tests=(
    verify/compile_all.cpp
    verify/basic_grid_io_test.cpp
    verify/grid_test.cpp
    verify/binary_search_test.cpp
    verify/cumsum_test.cpp
    verify/imos_test.cpp
    verify/fenwick_test.cpp
    verify/compress.cpp
    verify/dsu_test.cpp
    verify/graph_search_test.cpp
    verify/shortest_path_test.cpp
)

for file in "${tests[@]}"; do
    exe="/tmp/$(basename "$file" .cpp)"
    echo "[compile] $file"
    "$CXX" $CXXFLAGS "$file" -o "$exe"

    echo "[run] $exe"
    "$exe"
done

echo "All verify tests passed."
