#include <algorithm>
#include <array>
#include <bits/stdc++.h>
#include <cmath>
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <string>
#include <utility>
#include <vector>
using namespace std;

// ===== bundled from library/basic.hpp =====
// Basic aliases, constants, and macros for C++17 competitive programming.


// ============== 基本型 ==============
using ll = long long;
using ull = unsigned long long;
using ld = long double;
template <typename T> using V = vector<T>;
template <typename T> using minpq = priority_queue<T, V<T>, greater<T>>;
using maxpq_ll = priority_queue<ll>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

// ============== 定数 ==============
constexpr ld PI = 3.141592653589793238L;
constexpr int INF = (1 << 30) - 1;
constexpr ll INF_L = (1LL << 60);
constexpr double INF_D = 1e100;
constexpr ld INF_DL = 1e100L;
const string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string abc = "abcdefghijklmnopqrstuvwxyz";
constexpr ll modNum = 998244353;

// ============== マクロ ==============
#define rep(i, n) for (int i = 0, i##_n = static_cast<int>(n); i < i##_n; i++)
#define rep1(i, n) for (int i = 1, i##_n = static_cast<int>(n); i <= i##_n; i++)
#define rrep(i, n) for (int i = static_cast<int>(n) - 1; i >= 0; i--)
#define rrep1(i, n) for (int i = static_cast<int>(n); i >= 1; i--)
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)

// ===== bundled from library/grid.hpp =====
// Grid direction constants and small helpers for grid traversal.


// ============== グリッド方向 ==============
inline constexpr array<int, 4> DR4 = {-1, 0, 1, 0};
inline constexpr array<int, 4> DC4 = {0, 1, 0, -1};
inline constexpr array<char, 4> DIR4 = {'U', 'R', 'D', 'L'};
inline constexpr array<char, 4> dir4 = {'u', 'r', 'd', 'l'};
inline constexpr array<int, 8> DR8 = {-1, -1, 0, 1, 1,  1, 0, -1};
inline constexpr array<int, 8> DC8 = { 0,  1, 1, 1, 0, -1, -1, -1};
inline const array<string, 8> DIR8 = {"U", "UR", "R", "DR", "D", "DL", "L", "UL"};
inline const array<string, 8> dir8 = {"u", "ur", "r", "dr", "d", "dl", "l", "ul"};

inline bool in_grid(const int i, const int j, const int H, const int W) {
    return 0 <= i && i < H && 0 <= j && j < W;
}

struct Grid {
    int H{}, W{};
    V<string> cell;
    V<string> v, h;
    char block = '#';
    char wall = '1';

    Grid() = default;

    Grid(const int H_, const int W_, const char block_ = '#', const char wall_ = '1'):
    H(H_), W(W_),
    cell(H, string(W, '.')),
    v(H, string(max(0, W - 1), '0')),
    h(max(0, H - 1), string(W, '0')),
    block(block_), wall(wall_) {}

    Grid(
        const int H_,
        const int W_,
        const V<string> &v_,
        const V<string> &h_,
        const char block_ = '#',
        const char wall_ = '1'
    ):  H(H_), W(W_),
        cell(H_, string(W_, '.')),
        v(v_),
        h(h_),
        block(block_),
        wall(wall_) {}

    [[nodiscard]] bool in(const int i, const int j) const {
        return in_grid(i, j, H, W);
    }

    [[nodiscard]] int id(const int i, const int j) const {
        return i * W + j;
    }

    [[nodiscard]] pii rc(const int id) const {
        return {id / W, id % W};
    }

    [[nodiscard]] bool is_block(const int i, const int j) const {
        return cell[i][j] == block;
    }

    [[nodiscard]] bool passable(const int i, const int j) const {
        return in(i, j) && !is_block(i, j);
    }

    [[nodiscard]] bool has_wall(const int i, const int j, const int d) const {
        if (d == 0) {
            if (i == 0) return true;
            return h[i - 1][j] == wall;
        }
        if (d == 1) {
            if (j == W - 1) return true;
            return v[i][j] == wall;
        }
        if (d == 2) {
            if (i == H - 1) return true;
            return h[i][j] == wall;
        }
        if (d == 3) {
            if (j == 0) return true;
            return v[i][j - 1] == wall;
        }
        return true;
    }

    [[nodiscard]] bool can_go(const int i, const int j, const int d) const {
        if (d < 0 || 4 <= d) return false;
        if (!in(i, j)) return false;
        if (has_wall(i, j, d)) return false;

        const int ni = i + DR4[d];
        const int nj = j + DC4[d];

        return passable(ni, nj);
    }

    [[nodiscard]] V<pii> neighbors4(const int i, const int j) const {
        V<pii> res;

        rep(d, 4) {
            if (!can_go(i, j, d)) continue;

            const int ni = i + DR4[d];
            const int nj = j + DC4[d];

            res.emplace_back(ni, nj);
        }

        return res;
    }
};

inline Grid read_grid(const int H, const int W, const char block = '#') {
    Grid g(H, W, block);
    rep(i, H) cin >> g.cell[i];

    return g;
}

inline Grid read_grid_with_walls(const int H, const int W, const char wall = '1') {
    Grid g(H, W, '#', wall);

    rep(i, H) cin >> g.v[i];
    rep(i, H - 1) cin >> g.h[i];

    return g;
}

// ===== bundled from library/grid_search.hpp =====
// Grid Algorithms.


struct GridBFS_Info {
    V<V<int>> dist;
    V<V<pii>> parent;
    V<V<int>> parent_dir;
};

inline GridBFS_Info grid_bfs(const Grid& g, const pair<int, int> s) {
    GridBFS_Info info;

    info.dist.assign(g.H, V<int>(g.W, -1));
    info.parent.assign(g.H, V<pii>(g.W, {-1, -1}));
    info.parent_dir.assign(g.H, V<int>(g.W, -1));

    queue<pii> q;
    info.dist[s.first][s.second] = 0;
    q.push(s);

    while (!q.empty()) {
        auto [i, j] = q.front();
        q.pop();

        V<pii> neighbors = g.neighbors4(i, j);

        for (const auto neighbor : neighbors) {
            const auto [ni, nj] = neighbor;

            if (info.dist[ni][nj] != -1) continue;

            const int di = ni - i, dj = nj - j;
            const int dir = (dj == 0 ? di + 1 : (dj == 1 ? 1 : 3));

            info.dist[ni][nj] = info.dist[i][j] + 1;
            info.parent[ni][nj] = {i, j};
            info.parent_dir[ni][nj] = dir;

            q.emplace(ni, nj);
        }
    }

    return info;
}

inline V<pii> restore_grid_path(const V<V<pii>> &parent, const pii s, const pii t) {
    V<pii> path;

    pii now = t;

    while (true) {
        path.emplace_back(now);

        if (now == s) break;

        pii p = parent[now.first][now.second];

        if (p == pii{-1, -1}) return {};

        now = p;
    }

    reverse(all(path));
    return path;
}

inline string restore_grid_moves4(const V<V<int>> &parent_dir, const pii s, const pii t) {
    string moves;

    pii now = t;

    while (now != s) {
        const int dir = parent_dir[now.first][now.second];

        if (dir < 0 || dir >= 4) return "";

        moves.push_back(DIR4[dir]);

        const int pi = now.first - DR4[dir];
        const int pj = now.second - DC4[dir];

        now = {pi, pj};
    }

    reverse(all(moves));
    return moves;
}

// ===== bundled from library/io.hpp =====
// Small input/output and general utility helpers.


// ============== ユーティリティ ==============
template <class T, class U> bool chmin(T &a, const U &b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}
template <class T, class U> bool chmax(T &a, const U &b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}
template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template <class T> T clampv(T x, T lo, T hi) { return x < lo ? lo : (x > hi ? hi : x); }
template <class T> T ceil_div(T a, T b) {
    if (b < 0)
        a = -a, b = -b;
    if (a >= 0)
        return (a + b - 1) / b;
    return a / b;
}
template <class T> T floor_div(T a, T b) {
    if (b < 0)
        a = -a, b = -b;
    if (a >= 0)
        return a / b;
    return (a - (b - 1)) / b;
}

// ============== printヘルパ ==============
template <class T> void print_one(const T &x) { cout << x; }
template <class T, class... Ts> void print_one(const T &x, const Ts &...xs) {
    cout << x << ' ';
    print_one(xs...);
}
inline void println() {
    cout << '\n';
}
template <class T, class... Ts> void println(const T &x, const Ts &...xs) {
    cout << x;
    ((cout << ' ' << xs), ...);
    cout << '\n';
}
template <class T> void printAll(const V<T> &t) {
    rep(i, t.size()) cout << t[i] << '\n';
}
inline void yes(const bool c = true) { cout << (c ? "Yes" : "No") << '\n'; }
inline void YES(const bool c = true) { cout << (c ? "YES" : "NO") << '\n'; }

// ============== 数学ヘルパ ==============
// Sum of 0...(x-1)
template <class T> T tri0(T x) {
    return x * (x - 1) / 2;
}
// Sum of 1...x
template <class T> T tri1(T x) {
    return (x + 1) * x / 2;
}

// ============== 再帰ラムダ ==============
template <class F> struct y_combinator {
    F f;
    template <class... Args> decltype(auto) operator()(Args &&...args) const {
        return f(*this, std::forward<Args>(args)...);
    }
};
template <class F> y_combinator<F> yc(F &&f) { return {std::forward<F>(f)}; }

// ===== bundled from library/cumsum.hpp =====
// One-dimensional and two-dimensional prefix sum helpers.


// ============== 累積和 ==============
// 1D --- 0, s[1], s[2], ...型
template <class T> V<T> prefix_sum_1d(const V<T> &vec) {
    const int n = static_cast<int>(vec.size());
    V<T> ps(n + 1, T{});
    rep(i, n) ps[i + 1] = ps[i] + vec[i];

    return ps;
}

template <class T> T range_sum_1d(const V<T> &ps, const int l, const int r) {
    return ps[r] - ps[l];
}

// 2D
// 0 0       0       ...
// 0 s[1][1] s[1][2] ...
// 0 s[2][1] s[2][2] ...
// . ...     ...
template <class T> V<V<T>> prefix_sum_2d(const V<V<T>> &grid) {
    const int n = static_cast<int>(grid.size());
    if (n == 0) return V<V<T>>(1, V<T>(1, T{}));

    const int m = static_cast<int>(grid[0].size());
    V<V<T>> ps(n + 1, V<T>(m + 1, T{}));

    rep(i, n) ps[i + 1] = prefix_sum_1d(grid[i]);
    rep(i, n) {
        rep(j, m + 1) ps[i + 1][j] += ps[i][j];
    }

    return ps;
}

template <class T> T range_sum_2d(const V<V<T>> &ps, const int r1, const int c1, const int r2, const int c2) {
    return ps[r2][c2] - ps[r1][c2] - ps[r2][c1] + ps[r1][c1];
}

// 累積MAX
// A[0], A[1], A[2], ..., A[N - 1]
// lowest, L[0], L[1], L[2], ..., L[N - 1], lowest
// lowest, R[0], R[1], R[2], ..., R[N - 1], lowest
template <class T> struct Prefix_Max_Info {
    V<T> L, R;
};
template <class T> Prefix_Max_Info<T> prefix_max_1d(const V<T> &vec) {
    const int n = static_cast<int>(vec.size());
    Prefix_Max_Info<T> info;
    info.L.assign(n + 2, numeric_limits<T>::lowest());
    info.R.assign(n + 2, numeric_limits<T>::lowest());
    rep(i, n) info.L[i + 1] = max(info.L[i], vec[i]);
    rrep(i, n) info.R[i + 1] = max(info.R[i + 2], vec[i]);
    return info;
}

// ===== bundled from library/binary_search.hpp =====
// Binary search helpers for sorted containers and monotone predicates.


// ============== 二分探索 ==============
// return -> 0-indexed
template <class T, class F> int binary_search_index(const V<F> &vec, T x) {
    int pos = lower_bound(all(vec), x) - vec.begin();
    if (pos < static_cast<int>(vec.size()) && vec[pos] == x) return pos;
    return -1;
}
template <class T>
int first_ge(const V<T>& a, T x) {
    return lower_bound(all(a), x) - a.begin();
}
template <class T>
int first_gt(const V<T>& a, T x) {
    return upper_bound(all(a), x) - a.begin();
}
template <class T>
int last_lt(const V<T>& a, T x) {
    int p = lower_bound(all(a), x) - a.begin();
    return p - 1;
}
template <class T>
int last_le(const V<T>& a, T x) {
    int p = upper_bound(all(a), x) - a.begin();
    return p - 1;
}
template <class T, class F> T binary_search_min(T ok, T ng, F pred) {
    while (abs(ok - ng) > 1) {
        T mid = ng + (ok - ng) / 2;
        if (pred(mid)) ok = mid;
        else ng = mid;
    }
    return ok;
}
template <class T, class F> T binary_search_max(T ok, T ng, F pred) {
    while (abs(ng - ok) > 1) {
        T mid = ok + (ng - ok) / 2;
        if (pred(mid)) ok = mid;
        else ng = mid;
    }
    return ok;
}

// ===== bundled from library/graph.hpp =====
// Graph data structures and input helpers.


// ============== グラフテンプレ ==============
struct Edge {
    int to;
    ll w;
    Edge() : to(0), w(1) {}
    Edge(int _to, ll _w = 1) : to(_to), w(_w) {}
};

struct Graph {
    V<V<Edge>> graph;
    bool undirected = true;
    bool weighted = false;
    bool one_indexed = true;

    Graph() = default;

    explicit Graph(const int n, const bool _undirected = true, const bool _weighted = false, const bool _one_indexed = true)
        : graph(n),
          undirected(_undirected),
          weighted(_weighted),
          one_indexed(_one_indexed) {}

    [[nodiscard]] int size() const {
        return static_cast<int>(graph.size());
    }

    [[nodiscard]] int to_internal(const int v) const {
        return one_indexed ? v - 1 : v;
    }

    [[nodiscard]] int to_external(const int v) const {
        return one_indexed ? v + 1 : v;
    }
};

inline void add_edge_internal(Graph &g, const int a, const int b, const ll w = 1) {
    g.graph[a].emplace_back(b, w);
    if (g.undirected) {
        g.graph[b].emplace_back(a, w);
    }
}

inline void add_edge(Graph &g, int a, int b, const ll w = 1) {
    a = g.to_internal(a);
    b = g.to_internal(b);
    add_edge_internal(g, a, b, w);
}

inline Graph read_graph(
    const int n,
    const int m,
    const bool undirected = true,
    const bool weighted = false,
    const bool one_indexed = true
) {
    Graph g(n, undirected, weighted, one_indexed);

    rep(_, m) {
        int a, b;
        ll w = 1;

        if (weighted) {
            cin >> a >> b >> w;
        } else {
            cin >> a >> b;
        }

        add_edge(g, a, b, w);
    }

    return g;
}

// ===== bundled from library/graph_search.hpp =====
// DFS, BFS, path restoration, and connected-component helpers.


// ============== グラフアルゴリズム ==============
// ============== DFS ==============
struct DFS_Info {
    V<int> used, parent, tin, tout, comp_id, order;
    int comp_cnt = 0;
    int timer = 0;
};

inline DFS_Info dfs_all(const Graph &graph) {
    DFS_Info info;

    const auto &g = graph.graph;
    const int n = graph.size();

    info.used.assign(n, 0);
    info.parent.assign(n, -1);
    info.tin.assign(n, -1);
    info.tout.assign(n, -1);
    info.comp_id.assign(n, -1);
    info.order.reserve(n);

    const auto dfs = yc([&](auto self, int v, const int p) -> void {
        info.used[v] = 1;
        info.parent[v] = p;
        info.tin[v] = info.timer++;
        info.comp_id[v] = info.comp_cnt;
        info.order.push_back(v);

        for (const auto &e : g[v]) {
            const int to = e.to;
            if (info.used[to]) continue;
            self(to, v);
        }

        info.tout[v] = info.timer;
    });

    rep(v, n) {
        if (info.used[v]) continue;
        dfs(v, -1);
        info.comp_cnt++;
    }

    return info;
}

// ============== BFS ==============
struct BFS_Info {
    V<int> dist, parent;
    V<int> order, source;
};

inline BFS_Info bfs(const Graph &graph, int s) {
    BFS_Info info;

    const auto &g = graph.graph;
    const int n = graph.size();

    s = graph.to_internal(s);

    info.dist.assign(n, -1);
    info.parent.assign(n, -1);
    info.source.assign(n, -1);
    info.order.reserve(n);

    queue<int> q;

    info.dist[s] = 0;
    info.source[s] = s;
    q.push(s);

    while (!q.empty()) {
        const int v = q.front();
        q.pop();

        info.order.push_back(v);

        for (const auto &e : g[v]) {
            const int to = e.to;
            if (info.dist[to] != -1) continue;

            info.dist[to] = info.dist[v] + 1;
            info.parent[to] = v;
            info.source[to] = info.source[v];

            q.push(to);
        }
    }

    return info;
}

inline V<int> restore_path(const Graph &graph, const V<int> &parent, int s, int t) {
    V<int> path;

    s = graph.to_internal(s);
    t = graph.to_internal(t);

    if (s == t) {
        path.push_back(s);
    } else {
        if (parent[t] == -1) return {};

        for (int v = t; v != -1; v = parent[v]) {
            path.push_back(v);
            if (v == s) break;
        }

        if (path.back() != s) return {};

        reverse(all(path));
    }

    for (auto &v : path) {
        v = graph.to_external(v);
    }

    return path;
}

inline BFS_Info bfs_multi(const Graph &graph, const V<int> &starts) {
    BFS_Info info;

    const auto &g = graph.graph;
    const int n = graph.size();

    info.dist.assign(n, -1);
    info.parent.assign(n, -1);
    info.source.assign(n, -1);
    info.order.reserve(n);

    queue<int> q;

    for (int s : starts) {
        s = graph.to_internal(s);

        if (info.dist[s] != -1) continue;

        info.dist[s] = 0;
        info.source[s] = s;
        q.push(s);
    }

    while (!q.empty()) {
        const int v = q.front();
        q.pop();

        info.order.push_back(v);

        for (const auto &e : g[v]) {
            const int to = e.to;

            if (info.dist[to] != -1) continue;

            info.dist[to] = info.dist[v] + 1;
            info.parent[to] = v;
            info.source[to] = info.source[v];

            q.push(to);
        }
    }

    return info;
}

// ============== 連結成分 ==============
struct CC_Info {
    V<int> comp_id;
    V<int> comp_size;
    int comp_cnt = 0;
};

inline CC_Info connected_components(const Graph &graph) {
    CC_Info info;

    const auto &g = graph.graph;
    const int n = graph.size();

    info.comp_id.assign(n, -1);

    rep(s, n) {
        if (info.comp_id[s] != -1) continue;

        queue<int> q;
        q.push(s);
        info.comp_id[s] = info.comp_cnt;

        int sz = 0;

        while (!q.empty()) {
            const int v = q.front();
            q.pop();

            sz++;

            for (const auto &e : g[v]) {
                const int to = e.to;

                if (info.comp_id[to] != -1) continue;

                info.comp_id[to] = info.comp_cnt;
                q.push(to);
            }
        }

        info.comp_size.push_back(sz);
        info.comp_cnt++;
    }

    return info;
}

// ===== bundled from library/shortest_path.hpp =====
// Shortest path algorithms for Graph.


// ============== Dijkstra ==============
struct Dijkstra_Info {
    V<ll> dist;
    V<int> parent;
    V<int> order;
};

inline Dijkstra_Info dijkstra(const Graph &graph, int s) {
    Dijkstra_Info info;

    const auto &g = graph.graph;
    const int n = graph.size();

    s = graph.to_internal(s);

    info.dist.assign(n, INF_L);
    info.parent.assign(n, -1);
    info.order.reserve(n);

    minpq<pair<ll, int>> pq;

    info.dist[s] = 0;
    pq.emplace(0, s);

    while (!pq.empty()) {
        const auto [d, v] = pq.top();
        pq.pop();

        if (d != info.dist[v]) continue;

        info.order.push_back(v);

        for (const auto &e : g[v]) {
            const int to = e.to;
            const ll nd = info.dist[v] + e.w;

            if (info.dist[to] <= nd) continue;

            info.dist[to] = nd;
            info.parent[to] = v;

            pq.emplace(nd, to);
        }
    }

    return info;
}

inline V<int> restore_shortest_path(const Graph &graph, const V<int> &parent, int s, int t) {
    V<int> path;

    s = graph.to_internal(s);
    t = graph.to_internal(t);

    if (s == t) {
        path.push_back(s);
    } else {
        if (parent[t] == -1) return {};

        for (int v = t; v != -1; v = parent[v]) {
            path.push_back(v);
            if (v == s) break;
        }

        if (path.back() != s) return {};

        reverse(all(path));
    }

    for (auto &v : path) {
        v = graph.to_external(v);
    }

    return path;
}

// ===== bundled from library/compress.hpp =====
template <class T>
struct Compress {
    V<T> xs;

    Compress() = default;

    explicit Compress(const V<T> &v) {
        xs = v;
        build();
    }

    void add(const T &x) {
        xs.push_back(x);
    }

    void add(const V<T> &vec) {
        xs.insert(xs.end(), all(vec));
    }

    void build() {
        sort(all(xs));
        xs.erase(unique(all(xs)), xs.end());
    }

    int get(const T x) {
        return lower_bound(all(xs), x) - xs.begin();
    }

    T val(const int i) const {
        return xs[i];
    }

    int size() const {
        return static_cast<int>(xs.size());
    }
};

// ===== bundled from library/dsu.hpp =====
struct DSU {
    vector<int> parent_or_size;
    int group_count;

    explicit DSU(const int n) {
        parent_or_size.assign(n, -1);
        group_count = n;
    }

    int leader(const int x){
        if (parent_or_size[x] < 0) return x;
        return parent_or_size[x] = leader(parent_or_size[x]);
    }

    bool merge(int a, int b) {
        const int leader_a = leader(a);
        const int leader_b = leader(b);

        if (leader_a == leader_b) return false;

        if (abs(parent_or_size[leader_a]) > abs(parent_or_size[leader_b])) {
            parent_or_size[leader_a] += parent_or_size[leader_b];
            parent_or_size[leader_b] = leader_a;
            group_count--;
            return true;
        }
        parent_or_size[leader_b] += parent_or_size[leader_a];
        parent_or_size[leader_a] = leader_b;
        group_count--;
        return true;
    }

    bool same(int a, int b) {
        return leader(a) == leader(b);
    }

    int size(int x) {
        x = leader(x);
        return -parent_or_size[x];
    }

    int count_groups() const {
        return group_count;
    }
};

// ===== bundled from library/fenwick.hpp =====
template <class T>
struct Fenwick {
    V<T> bit;
    int n;

    Fenwick() : n(0) {}

    explicit Fenwick(const int n_) {
        init(n_);
    }

    void init(const int n_) {
        n = n_;
        bit.assign(n + 1, T(0));
    }

private:
    static int low_bit(const int idx) {
        return idx & -idx;
    }

public:
    void add(int idx, const T x) {
        idx++;
        while (idx <= n) {
            bit[idx] += x;
            idx += low_bit(idx);
        }
    }

    T sum(int r) const {
        T res = T(0);
        while (r > 0) {
            res += bit[r];
            r -= low_bit(r);
        }
        return res;
    }

    T sum(const int l, const int r) const {
        return sum(r) - sum(l);
    }

    T get(const int idx) const {
        return sum(idx, idx + 1);
    }

    void set(int idx, const T x) {
        add(idx, x - get(idx));
    }

    int lower_bound(T w) const {
        if (w <= T(0)) return 0;

        int idx = 0;

        int k = 1;
        while ((k << 1) <= n) k <<= 1;

        for (; k > 0; k >>= 1) {
            const int next = idx + k;

            if (next <= n && bit[next] < w) {
                idx = next;
                w -= bit[next];
            }
        }

        return idx;
    }
};

// ============== 解答用 ==============
#ifndef MULTI_TEST_CASES
#define MULTI_TEST_CASES 0
#endif

void solve() {

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
#if MULTI_TEST_CASES
    int T;
    if (!(cin >> T))
        return 0;
    while (T--)
        solve();
#else
    solve();
#endif
    return 0;
}
