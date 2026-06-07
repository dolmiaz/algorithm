# C++ Competitive Programming Template

C++17 向けの競技プログラミング用テンプレート集です。

`main.cpp` は提出用の全部入りテンプレートです。`library/` には再利用可能な部品、`snippets/` には問題ごとに編集する雛形を置きます。

## Environment

- Language: C++17
- Compiler assumption: GCC / Clang with GNU extension support
- Main dependency: standard library and `bits/stdc++.h`
- License: MIT License

`bits/stdc++.h` を使うため、標準 C++ だけの環境ではそのままコンパイルできない場合があります。

## Repository Layout

```text
algorithm/
├── main.cpp
├── scripts/
│   └── bundle_main.py
├── library/
│   ├── basic.hpp
│   ├── io.hpp
│   ├── grid.hpp
│   ├── cumsum.hpp
│   ├── compress.hpp
│   ├── binary_search.hpp
│   ├── dsu.hpp
│   ├── fenwick.hpp
│   ├── graph.hpp
│   ├── graph_search.hpp
│   └── shortest_path.hpp
├── snippets/
│   └── dp.cpp
└── verify/
```

`library/segtree.hpp`, `library/modint.hpp`, `library/string.hpp`, `library/tree.hpp` は現時点では未実装です。

## Submission Template

`main.cpp` は AtCoder などに貼り付ける単一ファイルの提出用テンプレートです。`solve()` を問題ごとに書き換えて使います。

```bash
g++ -std=gnu++17 -O2 -Wall -Wextra main.cpp -o main
```

複数テストケース形式では `MULTI_TEST_CASES=1` を定義します。

```bash
g++ -std=gnu++17 -O2 -Wall -Wextra -DMULTI_TEST_CASES=1 main.cpp -o main
```

## Bundle Script

`library/` のヘッダを `main.cpp` に反映します。

```bash
python3 scripts/bundle_main.py
```

スクリプトは `library/*.hpp` を対象にし、`#include "..."` のローカル依存を先に展開します。`main.cpp` の `// ============== 解答用 ==============` 以降は保持します。

## basic.hpp

基本型、コンテナ alias、定数、ループ macro を定義します。

| Name | Specification |
| --- | --- |
| `ll` | `long long` |
| `ull` | `unsigned long long` |
| `ld` | `long double` |
| `V<T>` | `vector<T>` |
| `minpq<T>` | 小さい値から取り出す `priority_queue` |
| `maxpq_ll` | `ll` 用の大きい値から取り出す `priority_queue` |
| `pii` | `pair<int, int>` |
| `pll` | `pair<ll, ll>` |
| `PI` | `3.141592653589793238L` |
| `INF` | `(1 << 30) - 1` |
| `INF_L` | `1LL << 60` |
| `INF_D` | `1e100` |
| `INF_DL` | `1e100L` |
| `ABC` | 大文字アルファベット |
| `abc` | 小文字アルファベット |
| `modNum` | `998244353` |
| `rep(i, n)` | `i = 0, 1, ..., n - 1` |
| `rep1(i, n)` | `i = 1, 2, ..., n` |
| `rrep(i, n)` | `i = n - 1, n - 2, ..., 0` |
| `rrep1(i, n)` | `i = n, n - 1, ..., 1` |
| `all(x)` | `begin(x), end(x)` |
| `rall(x)` | `rbegin(x), rend(x)` |

ループ macro の `n` は `int` に変換されます。

## io.hpp

出力補助、値更新、整数除算、再帰ラムダ補助を提供します。

| Name | Specification |
| --- | --- |
| `chmin(a, b)` | `a > b` のとき `a = b` に更新し `true`、それ以外は `false` |
| `chmax(a, b)` | `a < b` のとき `a = b` に更新し `true`、それ以外は `false` |
| `sgn(x)` | 正なら `1`、ゼロなら `0`、負なら `-1` |
| `clampv(x, lo, hi)` | `x` を `[lo, hi]` に収める |
| `ceil_div(a, b)` | 整数の数学的な切り上げ除算 |
| `floor_div(a, b)` | 整数の数学的な切り下げ除算 |
| `println(args...)` | 引数を空白区切りで出力し、末尾に改行 |
| `println()` | 改行だけを出力 |
| `printAll(vec)` | `vec` の各要素を 1 行ずつ出力 |
| `yes(c)` | `c` が true なら `Yes`、false なら `No` |
| `YES(c)` | `c` が true なら `YES`、false なら `NO` |
| `tri0(x)` | `0 + 1 + ... + (x - 1)` |
| `tri1(x)` | `1 + 2 + ... + x` |
| `yc(f)` | 再帰ラムダ用の y-combinator |

`ceil_div` と `floor_div` は `b != 0` を前提にします。

## grid.hpp

グリッド探索用の方向定数、座標補助、壁付きグリッド、グリッド BFS を提供します。座標は 0-indexed です。

| Name | Specification |
| --- | --- |
| `DR4`, `DC4` | 上、右、下、左の順の行・列差分 |
| `DIR4`, `dir4` | `U, R, D, L` / `u, r, d, l` |
| `DR8`, `DC8` | 上、右上、右、右下、下、左下、左、左上の順の行・列差分 |
| `DIR8`, `dir8` | `U, UR, R, DR, D, DL, L, UL` / 小文字版 |
| `in_grid(r, c, h, w)` | `0 <= r < h` かつ `0 <= c < w` なら true |
| `Grid` | `H`, `W`, `cell`, `v`, `h`, `block`, `wall` を持つグリッド構造体 |
| `Grid(H, W, block, wall)` | `cell` を `.`、壁情報 `v/h` を `0` で初期化する |
| `Grid(H, W, v, h, block, wall)` | 壁情報を指定して初期化する。`cell` は `.` で初期化する |
| `Grid::in(i, j)` | `in_grid(i, j, H, W)` |
| `Grid::id(i, j)` | `i * W + j` |
| `Grid::rc(id)` | `{id / W, id % W}` |
| `Grid::is_block(i, j)` | `cell[i][j] == block` なら true |
| `Grid::passable(i, j)` | 範囲内かつ block でなければ true |
| `Grid::has_wall(i, j, d)` | 方向 `d` に壁があれば true |
| `Grid::can_go(i, j, d)` | 方向 `d` へ壁なしで移動でき、移動先が通行可能なら true |
| `Grid::neighbors4(i, j)` | `U,R,D,L` 順で通行可能な隣接マスを返す |
| `read_grid(H, W, block)` | `H` 行の `cell` を読み込む |
| `read_grid_with_walls(H, W, wall)` | `H` 行の `v`、`H - 1` 行の `h` を読み込む |

`h` または `w` が 0 以下の場合、通常の非負座標は範囲外になります。

`Grid` の方向 `d` は `0:U`, `1:R`, `2:D`, `3:L` です。`v[i][j]` は `(i,j)` と `(i,j+1)` の間、`h[i][j]` は `(i,j)` と `(i+1,j)` の間の壁を表します。`has_wall` は外周と不正な方向を壁ありとして扱います。`v/h` のサイズは `Grid` の `H/W` と整合していることを前提にします。

## grid_search.hpp

`Grid` 上の 4 近傍 BFS と経路復元を提供します。各移動コストは 1 です。

| Name | Specification |
| --- | --- |
| `GridBFS_Info` | `dist`, `parent`, `parent_dir` を持つ BFS 結果 |
| `grid_bfs(g, s)` | 始点 `s` から BFS し、未到達距離を `-1` とする |
| `restore_grid_path(parent, s, t)` | `parent` から `s` から `t` への座標列を返す。不可能なら空 |
| `restore_grid_moves4(parent_dir, s, t)` | `DIR4` に基づく移動文字列を返す。不可能なら空文字 |

`grid_bfs` の始点 `s` は範囲内で通行可能であることを前提にします。`parent_dir` は到達したマスへ入る方向 `0:U`, `1:R`, `2:D`, `3:L` を保持します。始点から始点への復元では、座標列は `{s}`、移動文字列は空文字です。

## cumsum.hpp

1 次元・2 次元の累積和と、左右からの累積最大値を提供します。

| Name | Specification |
| --- | --- |
| `prefix_sum_1d(vec)` | 長さ `n + 1` の累積和を返す。`ps[0] = 0`, `ps[i + 1] = ps[i] + vec[i]` |
| `range_sum_1d(ps, l, r)` | 半開区間 `[l, r)` の和を返す |
| `prefix_sum_2d(grid)` | `(h + 1) x (w + 1)` の 2 次元累積和を返す |
| `range_sum_2d(ps, r1, c1, r2, c2)` | 半開矩形 `[r1, r2) x [c1, c2)` の和を返す |
| `Prefix_Max_Info<T>` | `L`, `R` を持つ累積最大値情報 |
| `prefix_max_1d(vec)` | `L[i + 1] = max(vec[0..i])`, `R[i + 1] = max(vec[i..n-1])` を返す |

`prefix_sum_2d` は空の `grid` に対して `1 x 1` のゼロ行列を返します。空でない `grid` は長方形であることを前提にします。区間取得関数は `ps` の有効範囲内の index を前提にします。

## compress.hpp

座標圧縮用の構造体を提供します。値の集合を昇順・重複なしに整理し、元の値と圧縮後 index を相互に扱います。

| Name | Specification |
| --- | --- |
| `Compress<T>` | 座標圧縮用構造体。内部配列 `xs` を持つ |
| `Compress()` | 空で初期化する |
| `Compress(v)` | `v` を受け取り、即座に `build()` して圧縮表を作る |
| `add(x)` | 値 `x` を追加する |
| `add(vec)` | `vec` の全要素を追加する |
| `build()` | `xs` を昇順にソートし、重複を削除する |
| `get(x)` | `lower_bound(xs, x)` の位置を返す |
| `val(i)` | 圧縮後 index `i` に対応する元の値を返す |
| `size()` | 圧縮後の要素数を返す |

`add()` の後は `build()` を呼んでから `get()` / `val()` を使うことを前提にします。`get(x)` は `x` が未登録でも挿入位置を返します。`val(i)` は `0 <= i < size()` を前提にします。

## binary_search.hpp

ソート済み配列と単調述語に対する二分探索補助を提供します。

| Name | Specification |
| --- | --- |
| `binary_search_index(vec, x)` | `x` が存在すれば最初の位置、存在しなければ `-1` |
| `first_ge(a, x)` | `x` 以上となる最初の index。なければ `a.size()` |
| `first_gt(a, x)` | `x` より大きい最初の index。なければ `a.size()` |
| `last_lt(a, x)` | `x` 未満となる最後の index。なければ `-1` |
| `last_le(a, x)` | `x` 以下となる最後の index。なければ `-1` |
| `binary_search_min(ok, ng, pred)` | `pred(ok) == true`, `pred(ng) == false` のとき、条件を満たす最小側の値を返す |
| `binary_search_max(ok, ng, pred)` | `pred(ok) == true`, `pred(ng) == false` のとき、条件を満たす最大側の値を返す |

配列は昇順ソート済みであることを前提にします。`binary_search_min/max` は整数型の探索幅で、`ok` と `ng` が異なる側にある単調述語を前提にします。

## dsu.hpp

Union-Find / Disjoint Set Union を提供します。頂点は 0-indexed です。

| Name | Specification |
| --- | --- |
| `DSU(n)` | `0, 1, ..., n - 1` をそれぞれ独立した集合として初期化する |
| `DSU::parent_or_size` | 根では集合サイズの負数、根でない頂点では親の頂点番号を保持する |
| `DSU::leader(x)` | `x` が属する集合の代表元を返す。経路圧縮を行う |
| `DSU::merge(a, b)` | `a` と `b` の集合を併合する。別集合なら `true`、同じ集合なら `false` |
| `DSU::same(a, b)` | `a` と `b` が同じ集合なら `true` |
| `DSU::size(x)` | `x` が属する集合の要素数を返す |
| `DSU::count_groups()` | 現在の集合数を返す |

`leader`, `merge`, `same`, `size` の引数は `0 <= x < n` を前提にします。`merge` は小さい集合を大きい集合へつなぐ方針で併合します。同じサイズの集合では第 2 引数側の代表元が併合後の代表元になります。

## fenwick.hpp

Fenwick Tree / Binary Indexed Tree による 1 次元配列の点更新・区間和取得を提供します。index は 0-indexed、区間は半開区間です。

| Name | Specification |
| --- | --- |
| `Fenwick<T>` | `T` 型の値を管理する Fenwick Tree |
| `Fenwick()` | 空で初期化する |
| `Fenwick(n)` | 長さ `n`、全要素 `T(0)` で初期化する |
| `Fenwick::init(n)` | 長さ `n`、全要素 `T(0)` に初期化し直す |
| `Fenwick::add(i, x)` | `a[i] += x` |
| `Fenwick::sum(r)` | 半開区間 `[0, r)` の総和を返す |
| `Fenwick::sum(l, r)` | 半開区間 `[l, r)` の総和を返す |
| `Fenwick::get(i)` | `a[i]` を返す |
| `Fenwick::set(i, x)` | `a[i] = x` に更新する |
| `Fenwick::push(x)` | 末尾に値 `x` を追加し、長さを 1 増やす |
| `Fenwick::lower_bound(w)` | `sum(i) < w <= sum(i + 1)` となる最小の `i` を返す。存在しなければ `size` |
| `RangeFenwick<T>` | 区間加算・区間和取得用の Fenwick Tree |
| `RangeFenwick()` | 空で初期化する |
| `RangeFenwick(n)` | 長さ `n`、全要素 `T(0)` で初期化する |
| `RangeFenwick::init(n)` | 長さ `n`、全要素 `T(0)` に初期化し直す |
| `RangeFenwick::add(l, r, x)` | 半開区間 `[l, r)` の各要素に `x` を加算する |
| `RangeFenwick::sum(r)` | 半開区間 `[0, r)` の総和を返す |
| `RangeFenwick::sum(l, r)` | 半開区間 `[l, r)` の総和を返す |
| `RangeFenwick::get(i)` | `a[i]` を返す |
| `RangeFenwick::set(i, x)` | `a[i] = x` に更新する |

`Fenwick` と `RangeFenwick` の長さは `size` に保持されます。`add`, `get`, `set` の index は `0 <= i < size`、`sum(r)` は `0 <= r <= size`、`sum(l, r)` は `0 <= l <= r <= size` を前提にします。`lower_bound(w)` は `w <= T(0)` なら `0` を返します。正しく使うには各要素が非負で、累積和が単調非減少であることを前提にします。`RangeFenwick::add(l, r, x)` は `l >= r` なら何もしません。`T` は `T(0)`, `+=`, `-`, `<`, `<=` が使える型であることを前提にします。

## graph.hpp

隣接リスト形式のグラフと入力補助を提供します。

| Name | Specification |
| --- | --- |
| `Edge` | 行き先 `to` と重み `w` を持つ辺。デフォルト重みは `1` |
| `Graph(n, undirected, weighted, one_indexed)` | 頂点数と設定を指定して構築 |
| `Graph::graph` | 内部 0-indexed の隣接リスト |
| `Graph::size()` | 頂点数 |
| `Graph::to_internal(v)` | 外部 index を内部 0-indexed に変換 |
| `Graph::to_external(v)` | 内部 0-indexed を外部 index に変換 |
| `add_edge_internal(g, a, b, w)` | 内部 index の辺を追加 |
| `add_edge(g, a, b, w)` | `Graph::one_indexed` に従って辺を追加 |
| `read_graph(n, m, undirected, weighted, one_indexed)` | 標準入力から `m` 本の辺を読み込む |

`undirected = true` では逆向きの辺も追加します。`weighted = false` の入力では辺重みを読まず、重み `1` とします。`one_indexed = true` では外部入力を 1-indexed として扱い、内部では 0-indexed で保持します。

## graph_search.hpp

DFS、BFS、経路復元、連結成分分解を提供します。入力頂点は `Graph::one_indexed` に従う外部 index です。

| Name | Specification |
| --- | --- |
| `DFS_Info` | `used`, `parent`, `tin`, `tout`, `comp_id`, `order`, `comp_cnt`, `timer` |
| `dfs_all(g)` | 全頂点を DFS し、到達順と連結成分を返す |
| `BFS_Info` | `dist`, `parent`, `order`, `source` |
| `bfs(g, s)` | 単一起点 BFS。未到達距離は `-1` |
| `bfs_multi(g, starts)` | 複数始点 BFS。各始点の距離は `0` |
| `restore_path(g, parent, s, t)` | `parent` から `s` から `t` への経路を外部 index で返す。不可能なら空 |
| `CC_Info` | `comp_id`, `comp_size`, `comp_cnt` |
| `connected_components(g)` | BFS による連結成分分解 |

`dfs_all` と `connected_components` は有向グラフでも隣接リストに従って探索します。無向連結成分として使う場合は `undirected = true` の `Graph` を使います。

## shortest_path.hpp

Dijkstra 法による単一起点最短路を提供します。辺重みは非負であることを前提にします。

| Name | Specification |
| --- | --- |
| `Dijkstra_Info` | `dist`, `parent`, `order` |
| `dijkstra(g, s)` | `s` から各頂点への最短距離を返す。未到達距離は `INF_L` |
| `restore_shortest_path(g, parent, s, t)` | Dijkstra の `parent` から最短路を外部 index で返す。不可能なら空 |

`dijkstra` の始点は `Graph::one_indexed` に従う外部 index です。`parent` は内部 0-indexed の頂点番号を保持します。

## Verification

完成済みテンプレートのテストは以下で実行します。

```bash
bash verify/run_all.sh
```

## TODO

- Segment Tree
- modint
- SCC
- LCA
- Z Algorithm
