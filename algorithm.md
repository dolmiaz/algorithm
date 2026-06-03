# 追加アルゴリズム

## 最優先

| **#** | **アルゴリズム名**           | **カテゴリ** | **用途**                         | **入力**                       | **戻り値**               | **計算量**                           | **前提条件**                 | **依存ヘッダ**         | **推奨ヘッダ名**          | **優先度** |
| ----- | ---------------------------- | ------------ | -------------------------------- | ------------------------------ | ------------------------ | ------------------------------------ | ---------------------------- | ---------------------- | ------------------------- | ---------- |
| 1     | DSU / Union-Find             | データ構造   | 連結判定、集合併合、Kruskal      | n, merge(a,b), same(a,b)       | 根、併合成否、集合サイズ | 初期化 O(n)、操作ならし O(\alpha(n)) | 静的な頂点集合               | basic.hpp              | library/dsu.hpp           | S          |
| 2     | Fenwick Tree                 | データ構造   | 点更新・区間和                   | 配列長 n, add(i,x), sum(l,r)   | 累積和・区間和           | O(\log n)                            | 可換群、主に加算             | basic.hpp              | library/fenwick.hpp       | S          |
| 3     | Segment Tree                 | データ構造   | 点更新・区間クエリ               | モノイド、配列、区間 [l,r)     | 区間集約値               | 構築 O(n)、操作 O(\log n)            | 結合律、単位元               | basic.hpp              | library/segtree.hpp       | S          |
| 4     | Lazy Segment Tree            | データ構造   | 区間更新・区間取得               | 作用付きモノイド、区間、更新値 | 区間集約値               | O(\log n)                            | 更新作用が合成可能           | basic.hpp, segtree.hpp | library/lazy_segtree.hpp  | S          |
| 5     | modint                       | 数学         | mod 四則演算、組合せ、DP         | 値、mod、演算                  | mod 付き値               | 各演算 O(1)、pow O(\log n)           | mod は正、逆元は互いに素     | basic.hpp              | library/modint.hpp        | S          |
| 6     | Combination / Factorial      | 数学         | nCr, nPr, 重複組合せ             | 最大 N, n,r                    | 組合せ値                 | 前計算 O(N)、取得 O(1)               | mod が素数なら逆元前計算可   | basic.hpp, modint.hpp  | library/combination.hpp   | S          |
| 7     | Z Algorithm                  | 文字列       | パターン検索、周期判定           | 文字列 s                       | Z 配列                   | O(\|s\|)                             | 文字列がランダムアクセス可能 | basic.hpp              | library/string.hpp        | S          |
| 8     | SCC / 強連結成分分解         | グラフ       | 有向グラフの成分縮約、2-SAT      | 有向グラフ                     | 成分番号、DAG            | O(V+E)                               | 有向グラフ                   | basic.hpp, graph.hpp   | library/scc.hpp           | S          |
| 9     | LCA / Lowest Common Ancestor | 木           | 木上距離、祖先判定               | 木、根、クエリ u,v             | 最近共通祖先             | 前処理 O(N\log N)、クエリ O(\log N)  | 木または森                   | basic.hpp, graph.hpp   | library/tree.hpp          | S          |
| 10    | Topological Sort             | グラフ       | DAG の順序、DP                   | 有向グラフ                     | トポロジカル順、DAG 判定 | O(V+E)                               | 有向グラフ                   | basic.hpp, graph.hpp   | library/dag.hpp           | S          |
| 11    | 0-1 BFS                      | 最短路       | 重み 0/1 の最短路                | グラフ、始点                   | 距離、親                 | O(V+E)                               | 辺重みが 0 または 1          | basic.hpp, graph.hpp   | library/shortest_path.hpp | S          |
| 12    | Bellman-Ford                 | 最短路       | 負辺あり最短路、負閉路検出       | 辺リスト、始点                 | 距離、負閉路判定         | O(VE)                                | 重み付き有向/無向            | basic.hpp, graph.hpp   | library/shortest_path.hpp | S          |
| 13    | Warshall-Floyd               | 最短路       | 全点対最短路                     | 隣接行列、頂点数               | 距離行列                 | O(N^3)                               | N が比較的小さい             | basic.hpp              | library/shortest_path.hpp | S          |
| 14    | Kruskal MST                  | グラフ       | 最小全域木                       | 辺リスト、頂点数               | MST 重み、採用辺         | O(E\log E)                           | 無向重み付きグラフ           | basic.hpp, dsu.hpp     | library/mst.hpp           | S          |
| 15    | 座標圧縮                     | 汎用         | 値域圧縮、Fenwick/Segtree 前処理 | 配列                           | 圧縮配列、復元配列       | O(N\log N)                           | 比較可能な値                 | basic.hpp              | library/compress.hpp      | S          |
| 16    | LIS                          | DP           | 最長増加部分列                   | 配列                           | 長さ、復元用親           | O(N\log N)                           | 比較可能な列                 | basic.hpp              | library/dp.hpp            | S          |
| 17    | 素数篩 / SPF                 | 数論         | 素数列挙、高速素因数分解         | 上限 N                         | 素数表、最小素因数       | O(N\log\log N) または O(N)           | 上限が事前に分かる           | basic.hpp              | library/number_theory.hpp | S          |
| 18    | 拡張 Euclid / mod 逆元       | 数論         | 一次不定方程式、逆元             | a,b, a,m                       | gcd、係数、逆元          | O(\log \min(a,b))                    | 逆元は gcd が 1              | basic.hpp              | library/number_theory.hpp | S          |
| 19    | 2D Imos / 差分配列           | 累積和       | 長方形加算、グリッド集計         | H,W, 矩形更新                  | 最終グリッド             | 更新 O(1)、復元 O(HW)                | オフライン更新               | basic.hpp, cumsum.hpp  | library/imos.hpp          | S          |
| 20✅   | Grid BFS                     | グリッド     | 迷路最短路、到達可能判定         | グリッド、始点、壁条件         | 距離、親                 | O(HW)                                | 各移動コストが等しい         | basic.hpp, grid.hpp    | library/grid_search.hpp   | S          |



## グラフ・木

有向グラフ・木・フロー系が不足

| **#** | **アルゴリズム名**                      | **カテゴリ**   | **用途**                         | **入力**              | **戻り値**               | **計算量**                          | **前提条件**            | **依存ヘッダ**                    | **推奨ヘッダ名**                   | **優先度** |
| ----- | --------------------------------------- | -------------- | -------------------------------- | --------------------- | ------------------------ | ----------------------------------- | ----------------------- | --------------------------------- | ---------------------------------- | ---------- |
| 21    | 二部グラフ判定                          | グラフ         | 2 色塗り、奇閉路判定             | 無向グラフ            | 色配列、成否             | O(V+E)                              | 無向グラフ              | basic.hpp, graph.hpp              | library/graph_search.hpp           | A          |
| 22    | LowLink                                 | グラフ         | 橋、関節点検出                   | 無向グラフ            | ord, low, 橋、関節点     | O(V+E)                              | 無向グラフ              | basic.hpp, graph.hpp              | library/lowlink.hpp                | A          |
| 23    | 橋分解 / 2-edge-connected components    | グラフ         | 橋を除いた成分圧縮               | 無向グラフ            | 成分番号、橋木           | O(V+E)                              | LowLink が必要          | lowlink.hpp                       | library/lowlink.hpp                | B          |
| 24    | 二重頂点連結成分                        | グラフ         | 関節点ベースの成分分解           | 無向グラフ            | 成分リスト               | O(V+E)                              | 無向グラフ              | lowlink.hpp                       | library/biconnected.hpp            | B          |
| 25    | Euler Tour                              | 木             | 部分木クエリ、LCA 前処理         | 木、根                | in, out, order           | O(N)                                | 木                      | basic.hpp, graph.hpp              | library/tree.hpp                   | A          |
| 26    | 木の直径                                | 木             | 最長パス、木 DP 初期解析         | 木                    | 直径長、端点、パス       | O(N)                                | 木、重みあり/なし       | basic.hpp, graph.hpp              | library/tree.hpp                   | A          |
| 27    | 木上距離                                | 木             | dist(u,v)                        | 木、根、LCA           | 距離                     | 前処理後 O(\log N)                  | LCA 前処理済み          | tree.hpp                          | library/tree.hpp                   | A          |
| 28    | Binary Lifting                          | 木・関数グラフ | k 個先の祖先、関数反復           | next 配列、最大 K     | k-step 先                | 前処理 O(N\log K)、クエリ O(\log K) | 遷移先が一意            | basic.hpp                         | library/binary_lifting.hpp         | A          |
| 29    | Functional Graph                        | グラフ         | サイクル検出、到達時刻、k 回遷移 | next 配列             | cycle id、深さ、遷移先   | O(N) または O(N\log K)              | 各頂点の出次数が 1      | basic.hpp, binary_lifting.hpp     | library/functional_graph.hpp       | A          |
| 30    | Rerooting DP                            | 木 DP          | 全方位木 DP、各頂点を根にした値  | 木、merge、add_root   | 各根の DP 値             | O(N)                                | 結合可能な DP           | basic.hpp, graph.hpp              | library/rerooting.hpp              | A          |
| 31    | Heavy-Light Decomposition               | 木             | 木パスクエリ、部分木クエリ       | 木、根                | head, pos, parent, depth | 構築 O(N)、パス分解 O(\log N)       | 木                      | basic.hpp, graph.hpp, segtree.hpp | library/hld.hpp                    | A          |
| 32    | Centroid Decomposition                  | 木             | 距離条件クエリ、動的木クエリ     | 木                    | 重心木、親               | O(N\log N)                          | 木                      | basic.hpp, graph.hpp              | library/centroid_decomposition.hpp | C          |
| 33    | DSU on Tree                             | 木             | 部分木ごとの色数・頻度集計       | 木、頂点値            | 各頂点の答え             | O(N\log N) または O(N)              | オフライン木クエリ      | basic.hpp, graph.hpp              | library/dsu_on_tree.hpp            | C          |
| 34    | DAG longest path                        | グラフ DP      | DAG 上最長路                     | DAG、重み             | 最長距離                 | O(V+E)                              | DAG                     | basic.hpp, dag.hpp                | library/dag.hpp                    | A          |
| 35    | 有向閉路検出                            | グラフ         | DAG 判定、サイクル復元           | 有向グラフ            | 閉路、成否               | O(V+E)                              | 有向グラフ              | basic.hpp, graph.hpp              | library/cycle_detection.hpp        | A          |
| 36    | 無向閉路検出                            | グラフ         | 木判定、サイクル復元             | 無向グラフ            | 閉路、成否               | O(V+E)                              | 無向グラフ              | basic.hpp, graph.hpp              | library/cycle_detection.hpp        | B          |
| 37    | Dinic 最大流                            | フロー         | 最大流、二部マッチング変換       | 辺、source, sink      | 最大流量、残余グラフ     | O(EV^2)、実用高速                   | 容量非負                | basic.hpp                         | library/maxflow.hpp                | A          |
| 38    | Min-Cost Flow                           | フロー         | 最小費用流、割当、輸送           | 辺、容量、費用、流量  | 最小費用、流量           | O(FE\log V) 目安                    | 費用付き容量グラフ      | basic.hpp                         | library/mincostflow.hpp            | B          |
| 39    | Hopcroft-Karp                           | マッチング     | 二部最大マッチング               | 左右頂点数、辺        | マッチ数、対応           | O(E\sqrt V)                         | 二部グラフ              | basic.hpp                         | library/bipartite_matching.hpp     | A          |
| 40    | Kuhn Matching                           | マッチング     | 小さめ二部マッチング             | 二部グラフ            | マッチング               | O(VE)                               | 二部グラフ              | basic.hpp                         | library/bipartite_matching.hpp     | B          |
| 41    | 2-SAT                                   | 論理・グラフ   | 真偽制約、割当判定               | 変数数、節            | 充足可否、割当           | O(N+M)                              | CNF の各節が 2 リテラル | basic.hpp, scc.hpp                | library/twosat.hpp                 | A          |
| 42    | Namori 分解                             | グラフ         | 頂点数＝辺数の無向連結グラフ処理 | 無向グラフ            | サイクル、木成分         | O(N)                                | 各成分に閉路 1 個       | basic.hpp, graph.hpp              | library/namori.hpp                 | B          |
| 43    | 全方位 Dijkstra / Multi-source Dijkstra | 最短路         | 複数始点最短距離                 | グラフ、始点集合      | 距離、最寄り始点         | O((V+E)\log V)                      | 辺重み非負              | basic.hpp, graph.hpp              | library/shortest_path.hpp          | A          |
| 44    | K-th shortest path                      | 最短路         | 第 k 短経路                      | グラフ、始点、終点、k | 候補距離                 | 実装方式依存                        | 非負辺推奨              | basic.hpp, graph.hpp              | library/k_shortest_path.hpp        | C          |
| 45    | Dominator Tree                          | グラフ         | 有向グラフ支配関係               | 有向グラフ、始点      | immediate dominator      | O((V+E)\log V) など                 | 到達可能部分を扱う      | basic.hpp, graph.hpp              | library/dominator_tree.hpp         | C          |



## データ構造

| **#** | **アルゴリズム名**                | **カテゴリ**           | **用途**                        | **入力**                  | **戻り値**          | **計算量**                        | **前提条件**                | **依存ヘッダ** | **推奨ヘッダ名**                  | **優先度** |
| ----- | --------------------------------- | ---------------------- | ------------------------------- | ------------------------- | ------------------- | --------------------------------- | --------------------------- | -------------- | --------------------------------- | ---------- |
| 46    | Weighted Union-Find               | データ構造             | 差分制約、ポテンシャル管理      | n, merge(a,b,w)           | 矛盾判定、diff(a,b) | O(\alpha(n))                      | 群演算、差分が定義可能      | basic.hpp      | library/weighted_dsu.hpp          | A          |
| 47    | Rollback Union-Find               | データ構造             | オフライン動的連結性            | merge, snapshot, rollback | 巻き戻し可能 DSU    | merge O(\alpha(n))、rollback O(1) | 経路圧縮は基本使わない      | basic.hpp      | library/rollback_dsu.hpp          | B          |
| 48    | Range Add Fenwick                 | データ構造             | 区間加算・一点取得              | 区間 [l,r), 値            | 点の値              | O(\log n)                         | 差分管理                    | fenwick.hpp    | library/fenwick.hpp               | A          |
| 49    | Range Add Range Sum Fenwick       | データ構造             | 区間加算・区間和                | 区間、値                  | 区間和              | O(\log n)                         | 2 本 Fenwick を使う         | fenwick.hpp    | library/fenwick.hpp               | A          |
| 50    | Fenwick lower_bound               | データ構造             | 累積和が x 以上になる最小 index | Fenwick、閾値 x           | index               | O(\log n)                         | 値が非負で累積和単調        | fenwick.hpp    | library/fenwick.hpp               | A          |
| 51    | 2D Fenwick Tree                   | データ構造             | 点更新・矩形和                  | H,W, 点更新、矩形         | 矩形和              | O(\log H\log W)                   | 座標範囲が管理可能          | basic.hpp      | library/fenwick_2d.hpp            | B          |
| 52    | Dual Segment Tree                 | データ構造             | 区間更新・一点取得              | 区間、更新作用            | 点の最終値          | O(\log n)                         | 更新作用が合成可能          | basic.hpp      | library/dual_segtree.hpp          | B          |
| 53    | Sparse Table                      | データ構造             | 静的 RMQ、gcd/min/max           | 配列、冪等演算            | 区間値              | 構築 O(N\log N)、取得 O(1)        | 冪等な結合演算              | basic.hpp      | library/sparse_table.hpp          | A          |
| 54    | Disjoint Sparse Table             | データ構造             | 静的区間和・min など            | 配列、モノイド            | 区間値              | 構築 O(N\log N)、取得 O(1)        | 結合律                      | basic.hpp      | library/disjoint_sparse_table.hpp | B          |
| 55    | Sqrt Decomposition                | データ構造             | 区間更新・区間取得の汎用分割    | 配列、クエリ              | クエリ結果          | 典型 O(\sqrt N)                   | 問題ごとに調整              | basic.hpp      | library/sqrt_decomposition.hpp    | B          |
| 56    | Mo’s Algorithm                    | データ構造・オフライン | 区間クエリ順序最適化            | 区間クエリ列              | 各クエリ答え        | O((N+Q)\sqrt N \cdot f)           | add/remove が実装可能       | basic.hpp      | library/mo.hpp                    | B          |
| 57    | SWAG / Sliding Window Aggregation | データ構造             | キュー上の区間集約、尺取り      | push/pop/fold             | 現在窓の集約値      | ならし O(1)                       | モノイド                    | basic.hpp      | library/swag.hpp                  | B          |
| 58    | Li Chao Tree                      | データ構造             | 直線集合の最小/最大値           | 直線、クエリ x            | 最小/最大値         | O(\log C)                         | x 座標範囲が既知または動的  | basic.hpp      | library/li_chao_tree.hpp          | B          |
| 59    | Convex Hull Trick                 | データ構造・DP最適化   | 一次式 DP の高速化              | 直線追加、x クエリ        | 最小/最大値         | 単調版 O(1)、一般 O(\log N)       | 傾きまたは x が単調なら簡単 | basic.hpp      | library/cht.hpp                   | B          |
| 60    | Ordered Set / PBDS wrapper        | データ構造             | k 番目取得、順位取得            | key, insert, erase        | order, kth          | O(\log n)                         | GNU 拡張あり                | basic.hpp      | library/ordered_set.hpp           | B          |
| 61    | Randomized Treap                  | データ構造             | 動的列、平衡二分木              | split, merge, insert      | 木、区間操作結果    | 期待 O(\log N)                    | 乱択優先度                  | basic.hpp      | library/treap.hpp                 | C          |
| 62    | Binary Trie                       | データ構造             | xor 最小/最大、mex、multiset    | 整数追加・削除・検索      | xor 最適値、個数    | O(\log A)                         | 値の bit 幅固定             | basic.hpp      | library/binary_trie.hpp           | A          |
| 63    | Trie                              | データ構造・文字列     | 辞書、prefix 検索               | 文字列追加・検索          | ノード、出現数      | O(\text{文字数})                  | alphabet が決まる           | basic.hpp      | library/trie.hpp                  | A          |
| 64    | Lazy Deletable Heap               | データ構造             | 削除可能 priority_queue         | push, erase, top          | 最小/最大           | O(\log n)                         | 遅延削除用 map/heap         | basic.hpp      | library/erasable_heap.hpp         | B          |
| 65    | Interval Set                      | データ構造             | 区間の併合、mex、被覆判定       | 区間追加/削除/検索        | 区間集合            | O(\log n) 目安                    | 半開区間で統一推奨          | basic.hpp      | library/interval_set.hpp          | B          |



## 数学・数論

| **#** | **アルゴリズム名**           | **カテゴリ**     | **用途**                      | **入力**           | **戻り値**      | **計算量**                        | **前提条件**                   | **依存ヘッダ**               | **推奨ヘッダ名**              | **優先度** |
| ----- | ---------------------------- | ---------------- | ----------------------------- | ------------------ | --------------- | --------------------------------- | ------------------------------ | ---------------------------- | ----------------------------- | ---------- |
| 66    | fast pow                     | 数学             | 累乗、mod 累乗                | a,n, optional mod  | a^n             | O(\log n)                         | 乗法が定義済み                 | basic.hpp                    | library/math.hpp              | S          |
| 67    | Chinese Remainder Theorem    | 数論             | 合同式の統合                  | mod 配列、余り配列 | 解、lcm mod     | O(k\log M)                        | mod が互いに素でなくても対応可 | number_theory.hpp            | library/crt.hpp               | A          |
| 68    | floor_sum                    | 数論             | \sum \lfloor (ai+b)/m \rfloor | n,m,a,b            | 和              | O(\log m)                         | 整数範囲に注意                 | basic.hpp                    | library/floor_sum.hpp         | A          |
| 69    | 約数列挙                     | 数論             | 約数全探索                    | 整数 n             | 約数配列        | O(\sqrt n)                        | n>0                            | basic.hpp                    | library/number_theory.hpp     | A          |
| 70    | 素因数分解                   | 数論             | 約数個数、約数和、判定        | 整数 n             | (p,e) 配列      | 試し割り O(\sqrt n)、SPF なら高速 | n>0                            | number_theory.hpp            | library/number_theory.hpp     | A          |
| 71    | Euler phi                    | 数論             | 互いに素な数の個数            | n                  | \varphi(n)      | O(\sqrt n) または前計算 O(N)      | n>0                            | number_theory.hpp            | library/number_theory.hpp     | B          |
| 72    | Möbius function              | 数論             | 包除、約数変換                | 上限 N             | \mu 配列        | O(N) または O(N\log\log N)        | 前計算型                       | number_theory.hpp            | library/mobius.hpp            | B          |
| 73    | Garner Algorithm             | 数論             | 非互いに素/複数 mod の復元    | 余り、mod 群       | 任意 mod での値 | O(k^2)                            | mod の扱いに注意               | crt.hpp, modint.hpp          | library/garner.hpp            | C          |
| 74    | Miller-Rabin                 | 数論             | 64-bit 素数判定               | 整数 n             | 素数判定        | O(\log n) 定数回                  | 64-bit 用基底を固定            | basic.hpp                    | library/prime_test.hpp        | B          |
| 75    | Pollard Rho                  | 数論             | 大きな整数の素因数分解        | 64-bit 整数        | 素因数          | 期待高速                          | Miller-Rabin と併用            | prime_test.hpp               | library/pollard_rho.hpp       | C          |
| 76    | Baby-step Giant-step         | 数論             | 離散対数                      | a,b,m              | x: a^x=b        | O(\sqrt m)                        | gcd 条件に注意                 | basic.hpp, number_theory.hpp | library/discrete_log.hpp      | C          |
| 77    | primitive root               | 数論             | NTT、原始根取得               | 素数 mod           | 原始根          | 因数分解依存                      | mod が素数                     | number_theory.hpp            | library/primitive_root.hpp    | B          |
| 78    | Matrix exponentiation        | 線形代数         | 線形漸化式、遷移累乗          | 行列、指数         | 行列累乗        | O(n^3\log k)                      | 行列積が定義可能               | basic.hpp, modint.hpp        | library/matrix.hpp            | A          |
| 79    | Gaussian Elimination         | 線形代数         | 連立方程式、rank              | 行列               | 解、rank        | O(NM^2) 目安                      | 体上、または実数誤差管理       | basic.hpp, modint.hpp        | library/linear_algebra.hpp    | B          |
| 80    | XOR Linear Basis             | 線形代数         | xor 最大化、独立性判定        | 整数列             | 基底、最大 xor  | O(N\log A)                        | bit 幅固定                     | basic.hpp                    | library/xor_basis.hpp         | A          |
| 81    | NTT                          | 畳み込み         | 多項式畳み込み                | 多項式 A,B         | convolution     | O(N\log N)                        | NTT-friendly mod               | basic.hpp, modint.hpp        | library/convolution.hpp       | B          |
| 82    | FFT convolution              | 畳み込み         | 任意 mod / 実数畳み込み       | 数列 A,B           | convolution     | O(N\log N)                        | 誤差に注意                     | basic.hpp                    | library/convolution.hpp       | C          |
| 83    | Formal Power Series basic    | 多項式           | FPS 逆元、微分、積分          | 多項式             | 多項式          | 実装内容に依存                    | modint 前提が楽                | modint.hpp, convolution.hpp  | library/fps.hpp               | C          |
| 84    | Kitamasa                     | 線形漸化式       | k 項目の高速計算              | 初期値、係数、k    | 第 k 項         | O(d^2\log k)                      | 線形漸化式                     | basic.hpp, modint.hpp        | library/linear_recurrence.hpp | C          |
| 85    | Berlekamp-Massey             | 線形漸化式       | 数列から最小漸化式推定        | 数列               | 係数            | O(N^2)                            | 体上の数列                     | modint.hpp                   | library/berlekamp_massey.hpp  | C          |
| 86    | Subset Zeta/Möbius Transform | bit DP           | 部分集合和変換                | 長さ 2^N 配列      | 変換後配列      | O(N2^N)                           | bitmask 添字                   | basic.hpp                    | library/subset_transform.hpp  | B          |
| 87    | FWHT                         | bit DP・畳み込み | xor/or/and 畳み込み           | 長さ 2^N 配列      | 畳み込み        | O(N2^N)                           | 演算種別を固定                 | basic.hpp, modest.hpp        | library/fwht.hpp              | B          |



## 文字列

| **#** | **アルゴリズム名**         | **カテゴリ** | **用途**                          | **入力**               | **戻り値**            | **計算量**                          | **前提条件**                   | **依存ヘッダ**      | **推奨ヘッダ名**          | **優先度** |
| ----- | -------------------------- | ------------ | --------------------------------- | ---------------------- | --------------------- | ----------------------------------- | ------------------------------ | ------------------- | ------------------------- | ---------- |
| 88    | KMP / prefix function      | 文字列       | パターン検索、border              | 文字列                 | prefix 配列、出現位置 | O(N+M)                              | 文字比較可能                   | basic.hpp           | library/string.hpp        | A          |
| 89    | Rolling Hash               | 文字列       | 部分文字列一致、LCP               | 文字列、区間           | hash、比較結果        | 構築 O(N)、取得 O(1)                | 衝突リスクあり、多重 hash 推奨 | basic.hpp           | library/rolling_hash.hpp  | A          |
| 90    | Manacher                   | 文字列       | 回文半径                          | 文字列                 | 各中心の回文半径      | O(N)                                | 文字列                         | basic.hpp           | library/manacher.hpp      | B          |
| 91    | Suffix Array               | 文字列       | 辞書順 suffix、部分文字列検索     | 文字列                 | suffix array          | O(N\log N)                          | 文字列                         | basic.hpp           | library/suffix_array.hpp  | B          |
| 92    | LCP Array                  | 文字列       | suffix 間 LCP、異なる部分文字列数 | 文字列、SA             | LCP 配列              | O(N)                                | SA 構築済み                    | suffix_array.hpp    | library/suffix_array.hpp  | B          |
| 93    | Aho-Corasick               | 文字列       | 複数パターン検索                  | パターン集合、テキスト | 出現数、オートマトン  | 構築 O(\Sigma \|p\|)、検索 O(\|s\|) | alphabet が決まる              | basic.hpp, trie.hpp | library/aho_corasick.hpp  | C          |
| 94    | Run Length Encoding        | 文字列・配列 | 連続要素圧縮                      | 文字列/配列            | (値,長さ) 配列        | O(N)                                | 等価比較可能                   | basic.hpp           | library/rle.hpp           | A          |
| 95    | Palindromic Tree / Eertree | 文字列       | 異なる回文部分文字列管理          | 文字列                 | 回文ノード木          | O(N)                                | 文字列                         | basic.hpp           | library/eertree.hpp       | C          |
| 96    | Lyndon Factorization       | 文字列       | 最小表現、周期性                  | 文字列                 | Lyndon 分解           | O(N)                                | 全順序あり                     | basic.hpp           | library/lyndon.hpp        | C          |
| 97    | Levenshtein Distance       | 文字列 DP    | 編集距離                          | 2 文字列               | 距離                  | O(NM)                               | 長さが大きすぎない             | basic.hpp           | library/edit_distance.hpp | C          |



## DP・探索・最適化

| **#** | **アルゴリズム名**                 | **カテゴリ** | **用途**                      | **入力**            | **戻り値**        | **計算量**               | **前提条件**         | **依存ヘッダ**        | **推奨ヘッダ名**            | **優先度** |
| ----- | ---------------------------------- | ------------ | ----------------------------- | ------------------- | ----------------- | ------------------------ | -------------------- | --------------------- | --------------------------- | ---------- |
| 98    | Knapsack helpers                   | DP           | 0/1 ナップサック、個数制限    | 重さ、価値、容量    | 最大価値など      | O(NW) など               | 容量が manageable    | basic.hpp             | library/knapsack.hpp        | A          |
| 99    | Bitset Knapsack                    | DP           | 到達可能和判定                | 重さ列              | 到達可能 bitset   | O(NW / word)             | 容量上限あり         | basic.hpp             | library/knapsack.hpp        | A          |
| 100   | Digit DP snippet                   | DP           | 桁制約の数え上げ              | 上限文字列、状態    | 個数・最大値など  | 状態数依存               | 問題ごとに状態設計   | basic.hpp, modint.hpp | snippets/digit_dp.cpp       | A          |
| 101   | Tree DP snippet                    | DP           | 木上最大/最小/数え上げ        | 木、根              | DP 配列           | O(N)                     | 木                   | basic.hpp, graph.hpp  | snippets/tree_dp.cpp        | A          |
| 102   | Interval DP snippet                | DP           | 区間マージ、括弧列、ゲーム    | 長さ N              | DP テーブル       | 典型 O(N^3)              | 区間長順に処理       | basic.hpp             | snippets/interval_dp.cpp    | B          |
| 103   | Rerooting DP template              | DP・木       | 各頂点を根とした答え          | 木、演算            | 各頂点の値        | O(N)                     | merge が結合的だと楽 | basic.hpp, graph.hpp  | library/rerooting.hpp       | A          |
| 104   | Divide and Conquer DP Optimization | DP最適化     | dp[i][j] の遷移高速化         | コスト関数、DP 段数 | DP                | O(KN\log N) など         | 最適決定点の単調性   | basic.hpp             | library/dp_optimization.hpp | C          |
| 105   | Knuth Optimization                 | DP最適化     | 区間 DP 高速化                | コスト、DP          | DP                | O(N^2)                   | 四角不等式・単調性   | basic.hpp             | library/dp_optimization.hpp | C          |
| 106   | SMAWK                              | DP最適化     | totally monotone 行列の行最小 | 行列アクセス関数    | 各行最小位置      | O(N+M)                   | totally monotone     | basic.hpp             | library/smawk.hpp           | C          |
| 107   | Slope Trick                        | DP最適化     | 絶対値関数 DP                 | 操作列              | 最小値、関数      | O(Q\log Q)               | 凸区分線形関数       | basic.hpp             | library/slope_trick.hpp     | C          |
| 108   | Ternary Search                     | 探索         | 単峰関数の最小/最大           | 範囲、関数          | argmin/argmax     | 整数 O(\log N)、実数反復 | 単峰性               | basic.hpp             | library/search.hpp          | B          |
| 109   | Real Binary Search                 | 探索         | 実数解、最小値判定            | lo, hi, predicate   | 近似値            | O(\text{反復回数})       | 単調性、誤差許容     | basic.hpp             | library/binary_search.hpp   | A          |
| 110   | Next Combination                   | 全探索       | k 個選択列挙                  | n,k                 | 次の bitmask/配列 | 1 遷移 O(1) or O(k)      | bit 幅に注意         | basic.hpp             | library/enumerate.hpp       | B          |
| 111   | Submask Enumeration helpers        | 全探索       | 部分集合列挙                  | bitmask             | submask 列挙      | 合計 O(3^N) 型           | bitmask DP           | basic.hpp             | library/enumerate.hpp       | A          |
| 112   | Meet-in-the-middle helper          | 全探索       | 半分全列挙                    | 配列、分割          | 候補集合          | O(2^{N/2})               | N が 40 前後         | basic.hpp             | library/mitm.hpp            | B          |



## グリッド・累積和・座標系

| **#** | **アルゴリズム名**               | **カテゴリ**     | **用途**               | **入力**             | **戻り値**           | **計算量**            | **前提条件**         | **依存ヘッダ**        | **推奨ヘッダ名**        | **優先度** |
| ----- | -------------------------------- | ---------------- | ---------------------- | -------------------- | -------------------- | --------------------- | -------------------- | --------------------- | ----------------------- | ---------- |
| 113   | Flood Fill                       | グリッド         | 連結成分塗り分け       | グリッド、壁条件     | 成分番号、成分サイズ | O(HW)                 | 4/8 近傍を選択       | basic.hpp, grid.hpp   | library/grid_search.hpp | A          |
| 114   | Grid shortest path restore       | グリッド         | 迷路の経路復元         | 始点、終点、壁条件   | 距離、経路           | O(HW)                 | 等重み移動           | grid.hpp              | library/grid_search.hpp | A          |
| 115   | 0-1 Grid BFS                     | グリッド         | 壁破壊、方向転換コスト | グリッド、コスト 0/1 | 最短距離             | O(HW)                 | 移動コストが 0/1     | basic.hpp, grid.hpp   | library/grid_search.hpp | A          |
| 116   | Grid to Graph converter          | グリッド・グラフ | マスを頂点化           | H,W, 通行条件        | id(r,c), graph       | O(HW)                 | 頂点数 HW が許容     | grid.hpp, graph.hpp   | library/grid_graph.hpp  | B          |
| 117   | Coordinate helper                | グリッド         | id = r*w+c, 復元       | r,c,H,W              | id, pair             | O(1)                  | 0-index 推奨         | basic.hpp, grid.hpp   | library/grid.hpp        | A          |
| 118   | 3D Grid directions               | グリッド         | 立体 BFS               | x,y,z                | 6 方向配列           | O(1)                  | 3D グリッド          | basic.hpp             | library/grid3d.hpp      | C          |
| 119   | 1D Imos                          | 累積和           | 区間加算               | 長さ、区間更新       | 最終配列             | 更新 O(1)、復元 O(N)  | オフライン           | basic.hpp, cumsum.hpp | library/imos.hpp        | A          |
| 120   | Difference Array 2D with restore | 累積和           | 矩形加算               | H,W, 矩形            | 最終値               | 更新 O(1)、復元 O(HW) | 半開区間で統一       | cumsum.hpp            | library/imos.hpp        | A          |
| 121   | Prefix min/max 2D                | 累積和           | 左上矩形の min/max     | グリッド             | prefix min/max       | O(HW)                 | 演算に応じて条件あり | basic.hpp             | library/cumsum.hpp      | B          |



## 幾何

| **#** | **アルゴリズム名**          | **カテゴリ** | **用途**                 | **入力**     | **戻り値**         | **計算量** | **前提条件**              | **依存ヘッダ**  | **推奨ヘッダ名**                    | **優先度** |
| ----- | --------------------------- | ------------ | ------------------------ | ------------ | ------------------ | ---------- | ------------------------- | --------------- | ----------------------------------- | ---------- |
| 122   | Point / Vector 2D           | 幾何         | 点・ベクトル演算         | 座標         | 加減算、dot, cross | O(1)       | 整数/実数を型で分ける     | basic.hpp       | library/geometry.hpp                | A          |
| 123   | CCW / orientation           | 幾何         | 向き判定、交差判定の基礎 | 3 点         | 向き               | O(1)       | オーバーフロー注意        | geometry.hpp    | library/geometry.hpp                | A          |
| 124   | Segment Intersection        | 幾何         | 線分交差判定             | 2 線分       | 交差成否           | O(1)       | 端点含む/含まないを明確化 | geometry.hpp    | library/geometry.hpp                | A          |
| 125   | Distance line/segment/point | 幾何         | 最近距離                 | 点・線分     | 距離               | O(1)       | 実数誤差に注意            | geometry.hpp    | library/geometry.hpp                | B          |
| 126   | Convex Hull                 | 幾何         | 凸包、面積、最遠点       | 点集合       | 凸包頂点列         | O(N\log N) | 同一直線点の扱いを決める  | geometry.hpp    | library/convex_hull.hpp             | A          |
| 127   | Polygon Area                | 幾何         | 多角形面積               | 頂点列       | 符号付き面積       | O(N)       | 頂点順序                  | geometry.hpp    | library/polygon.hpp                 | A          |
| 128   | Point in Polygon            | 幾何         | 内外判定                 | 多角形、点   | inside/on/outside  | O(N)       | 単純多角形                | geometry.hpp    | library/polygon.hpp                 | B          |
| 129   | Rotating Calipers           | 幾何         | 凸多角形の直径           | 凸包         | 最大距離ペア       | O(N)       | 凸包が必要                | convex_hull.hpp | library/rotating_calipers.hpp       | B          |
| 130   | Closest Pair                | 幾何         | 最近点対                 | 点集合       | 最小距離           | O(N\log N) | 実数/整数座標             | geometry.hpp    | library/closest_pair.hpp            | C          |
| 131   | Circle Geometry             | 幾何         | 円と直線/円の交点        | 円、直線、円 | 交点               | O(1)       | 実数誤差                  | geometry.hpp    | library/circle.hpp                  | C          |
| 132   | Half-plane Intersection     | 幾何         | 線形制約領域             | 半平面集合   | 凸多角形           | O(N\log N) | 実装難、誤差注意          | geometry.hpp    | library/half_plane_intersection.hpp | C          |



## 入出力・デバッグ・テンプレ基盤

| **#** | **アルゴリズム名**               | **カテゴリ** | **用途**                 | **入力**   | **戻り値**           | **計算量**                      | **前提条件**        | **依存ヘッダ** | **推奨ヘッダ名**     | **優先度** |
| ----- | -------------------------------- | ------------ | ------------------------ | ---------- | -------------------- | ------------------------------- | ------------------- | -------------- | -------------------- | ---------- |
| 133   | FastScanner                      | 入出力       | 大量入力高速化           | stdin      | int, ll, string など | 入力長に線形                    | C++17、低レベル I/O | basic.hpp      | library/fast_io.hpp  | B          |
| 134   | FastPrinter                      | 入出力       | 大量出力高速化           | 値、文字列 | 出力                 | 出力量に線形                    | flush 管理          | basic.hpp      | library/fast_io.hpp  | C          |
| 135   | Container input operators        | 入出力       | vector/pair の入力簡略化 | cin >> v   | 入力済み container   | O(N)                            | 型が入力可能        | basic.hpp      | library/io.hpp       | A          |
| 136   | Container output operators       | 入出力       | vector/pair の出力簡略化 | container  | 出力                 | O(N)                            | 型が出力可能        | basic.hpp      | library/io.hpp       | A          |
| 137   | Debug macro                      | デバッグ     | ローカルのみ変数表示     | 任意変数   | stderr 出力          | 表示量依存                      | #ifdef LOCAL        | basic.hpp      | library/debug.hpp    | B          |
| 138   | Timer utility                    | デバッグ     | 実行時間確認             | 開始時刻   | 経過時間             | O(1)                            | ローカル用          | basic.hpp      | library/debug.hpp    | C          |
| 139   | custom_hash                      | 汎用         | unordered_map ハック対策 | key        | hash 値              | O(1)                            | splitmix64 など     | basic.hpp      | library/hash.hpp     | B          |
| 140   | Random utility                   | 汎用         | 乱択、Treap、テスト生成  | 範囲       | 乱数                 | O(1)                            | seed 管理           | basic.hpp      | library/random.hpp   | C          |
| 141   | Argument sort / argsort          | 汎用         | ソート順 index 取得      | 配列       | index 配列           | O(N\log N)                      | 比較可能            | basic.hpp      | library/utility.hpp  | B          |
| 142   | Compress with restore class      | 汎用         | 座標圧縮の構造体化       | 値集合     | id, value            | 構築 O(N\log N)、取得 O(\log N) | 静的値集合          | basic.hpp      | library/compress.hpp | S          |
| 143   | Safe midpoint / overflow helpers | 汎用         | 二分探索の overflow 防止 | l,r        | mid                  | O(1)                            | 整数型              | basic.hpp      | library/utility.hpp  | B          |
| 144   | ckmin/ckmax alias set            | 汎用         | chmin/chmax の命名統一   | 参照、値   | 更新成否             | O(1)                            | 既存と重複注意      | io.hpp         | library/io.hpp       | C          |