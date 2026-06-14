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

// ===== Base =====

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

// ===== Grid =====

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


struct GridBFS {
    const Grid *grid = nullptr;
    pii source = {-1, -1};
    V<V<int>> dist;
    V<V<pii>> parent;
    V<V<int>> parent_dir;

    GridBFS() = default;

    GridBFS(const Grid &g, const pii& s) {
        build(g, s);
    }

    void build(const Grid &g, const pii& s) {
        grid = &g;
        source = s;

        dist.assign(g.H, V<int>(g.W, -1));
        parent.assign(g.H, V<pii>(g.W, {-1, -1}));
        parent_dir.assign(g.H, V<int>(g.W, -1));

        queue<pii> q;
        dist[s.first][s.second] = 0;
        q.push(s);

        while (!q.empty()) {
            auto [i, j] = q.front();
            q.pop();

            V<pii> neighbors = g.neighbors4(i, j);

            for (const auto neighbor : neighbors) {
                const auto [ni, nj] = neighbor;

                if (dist[ni][nj] != -1) continue;

                const int di = ni - i, dj = nj - j;
                const int dir = (dj == 0 ? di + 1 : (dj == 1 ? 1 : 3));

                dist[ni][nj] = dist[i][j] + 1;
                parent[ni][nj] = {i, j};
                parent_dir[ni][nj] = dir;

                q.emplace(ni, nj);
            }
        }
    }

    [[nodiscard]] V<pii> path(const pii& t) const {
        V<pii> res;

        pii now = t;

        while (true) {
            res.emplace_back(now);

            if (now == source) break;

            pii p = parent[now.first][now.second];
            if (p == pii{-1, -1}) return {};

            now = p;
        }

        reverse(all(res));
        return res;
    }

    [[nodiscard]] string moves4(const pii& t) const {
        string moves;

        pii now = t;

        while (now != source) {
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
};

// ===== Range / Prefix =====

// ===== bundled from library/cumsum.hpp =====
// Prefix sum and prefix maximum helpers.


// ============== 累積和 ==============
template <class T>
struct PrefixSum1D {
    int size{};
    V<T> ps;

    PrefixSum1D() : size(0), ps(1, T{}) {}

    explicit PrefixSum1D(const V<T> &vec) {
        build(vec);
    }

    void build(const V<T> &vec) {
        size = static_cast<int>(vec.size());
        ps.assign(size + 1, T{});
        rep(i, size) ps[i + 1] = ps[i] + vec[i];
    }

    T sum(const int r) const {
        return ps[r];
    }

    T sum(const int l, const int r) const {
        return ps[r] - ps[l];
    }
};

template <class T>
struct PrefixSum2D {
    int H{}, W{};
    V<V<T>> ps;

    PrefixSum2D() : H(0), W(0), ps(1, V<T>(1, T{})) {}

    explicit PrefixSum2D(const V<V<T>> &grid) {
        build(grid);
    }

    void build(const V<V<T>> &grid) {
        H = static_cast<int>(grid.size());
        W = H == 0 ? 0 : static_cast<int>(grid[0].size());
        ps.assign(H + 1, V<T>(W + 1, T{}));

        rep(i, H) {
            rep(j, W) {
                ps[i + 1][j + 1] = ps[i + 1][j] + ps[i][j + 1] - ps[i][j] + grid[i][j];
            }
        }
    }

    T sum(const int r1, const int c1, const int r2, const int c2) const {
        return ps[r2][c2] - ps[r1][c2] - ps[r2][c1] + ps[r1][c1];
    }
};

// 累積MAX
template <class T>
struct PrefixMax1D {
    int size{};
    V<T> pref, suff;

    PrefixMax1D() : size(0), pref(1, numeric_limits<T>::lowest()), suff(1, numeric_limits<T>::lowest()) {}

    explicit PrefixMax1D(const V<T> &vec) {
        build(vec);
    }

    void build(const V<T> &vec) {
        size = static_cast<int>(vec.size());
        pref.assign(size + 1, numeric_limits<T>::lowest());
        suff.assign(size + 1, numeric_limits<T>::lowest());

        rep(i, size) pref[i + 1] = max(pref[i], vec[i]);
        rrep(i, size) suff[i] = max(suff[i + 1], vec[i]);
    }

    T prefix_max(const int r) const {
        return pref[r];
    }

    T suffix_max(const int l) const {
        return suff[l];
    }
};

// ===== bundled from library/imos.hpp =====
template <class T>
struct Imos1D {
    int n;
    V<T> diff;
    bool built = false;

    explicit Imos1D(int _n) : n(_n), diff(_n + 1, T{}) {}

    // [l, r)にxを加算
    void add(const int l, const int r, const T x) {
        if (l >= r) return;
        diff[l] += x;
        diff[r] -= x;
    }

    // [l, r]にxを加算
    void add_closed(const int l, const int r, const T x) {
        add(l, r + 1, x);
    }

    // 実際の配列を返す
    V<T> build() {
        V<T> res(n);
        T cur = T{};

        rep(i, n) {
            cur += diff[i];
            res[i] = cur;
        }

        built = true;
        return res;
    }
};

// ===== bundled from library/fenwick.hpp =====
// 外部 index: 0-indexed
// 内部 index: 1-indexed
// bit[i] は a[i - low_bit(i), i) の和を持つ
// sum(r) は a[0] + ... + a[r - 1] を返す
template <class T>
struct Fenwick {
    V<T> bit;
    int size;

    Fenwick() : size(0) {
    }

    explicit Fenwick(const int size_) {
        init(size_);
    }

    void init(const int size_) {
        size = size_;
        bit.assign(size + 1, T(0));
    }

private:
    static int to_internal(const int idx) {
        return idx + 1;
    }

    static int low_bit(const int idx) {
        return idx & -idx;
    }

public:
    void add(int idx, const T x) {
        idx++;
        while (idx <= size) {
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

    void set(const int i, const T x) {
        add(i, x - get(i));
    }

    void push(const T x) {
        const int old_size = size;

        if (bit.empty()) bit.push_back(T(0));

        ++size;
        bit.push_back(T(0));

        const int i = size;
        bit[i] = x + sum(i - low_bit(i), old_size);
    }

    int lower_bound(T w) const {
        if (w <= T(0)) return 0;

        int idx = 0;

        int k = 1;
        while ((k << 1) <= size) k <<= 1;

        for (; k > 0; k >>= 1) {
            const int next = idx + k;

            if (next <= size && bit[next] < w) {
                idx = next;
                w -= bit[next];
            }
        }

        return idx;
    }
};

template <class T>
struct RangeFenwick {
    int size{};
    Fenwick<T> bit0;
    Fenwick<T> bit1;

    RangeFenwick() : size(0) {
    }

    explicit RangeFenwick(const int size_) {
        init(size_);
    }

    void init(const int size_) {
        size = size_;
        bit0.init(size);
        bit1.init(size);
    }

private:
    void add_bit(Fenwick<T>& bit, const int idx, const T x) {
        if (idx < size) bit.add(idx, x);
    }

public:
    void add(const int l, const int r, const T x) {
        if (l >= r) return;

        add_bit(bit0, l, x);
        add_bit(bit0, r, -x);

        add_bit(bit1, l, x * T(l));
        add_bit(bit1, r, -x * T(r));
    }

    T sum(const int r) const {
        return bit0.sum(r) * T(r) - bit1.sum(r);
    }

    T sum(const int l, const int r) const {
        return sum(r) - sum(l);
    }

    T get(const int idx) const {
        return sum(idx, idx + 1);
    }

    void set(const int idx, const T x) {
        add(idx, idx + 1, x - get(idx));
    }
};

// ===== Index / Search =====

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

    [[nodiscard]] int size() const {
        return static_cast<int>(xs.size());
    }
};

// ===== bundled from library/binary_search.hpp =====
// Binary search helpers for sorted containers and monotone predicates.


// ============== 二分探索 ==============
template <class T>
struct BinarySearch {
    V<T> a;

    BinarySearch() = default;

    explicit BinarySearch(const V<T> &sorted_vec) {
        build(sorted_vec);
    }

    void build(const V<T> &sorted_vec) {
        a = sorted_vec;
    }

    int index(const T &x) const {
        const int pos = lower_bound(all(a), x) - a.begin();
        if (pos < static_cast<int>(a.size()) && a[pos] == x) return pos;
        return -1;
    }

    int first_ge(const T &x) const {
        return lower_bound(all(a), x) - a.begin();
    }

    int first_gt(const T &x) const {
        return upper_bound(all(a), x) - a.begin();
    }

    int last_lt(const T &x) const {
        return first_ge(x) - 1;
    }

    int last_le(const T &x) const {
        return first_gt(x) - 1;
    }

    template <class U, class F>
    static U min_true(U ok, U ng, F pred) {
        while (abs(ok - ng) > 1) {
            U mid = ng + (ok - ng) / 2;
            if (pred(mid)) ok = mid;
            else ng = mid;
        }
        return ok;
    }

    template <class U, class F>
    static U max_true(U ok, U ng, F pred) {
        while (abs(ng - ok) > 1) {
            U mid = ok + (ng - ok) / 2;
            if (pred(mid)) ok = mid;
            else ng = mid;
        }
        return ok;
    }
};

// ===== Set / Connectivity =====

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

    [[nodiscard]] int count_groups() const {
        return group_count;
    }
};

// ===== Graph =====

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

    void add_edge_internal(const int a, const int b, const ll w = 1) {
        graph[a].emplace_back(b, w);
        if (undirected) {
            graph[b].emplace_back(a, w);
        }
    }

    void add_edge(int a, int b, const ll w = 1) {
        a = to_internal(a);
        b = to_internal(b);
        add_edge_internal(a, b, w);
    }
};

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

        g.add_edge(a, b, w);
    }

    return g;
}

// ===== bundled from library/graph_search.hpp =====
// DFS, BFS, path restoration, and connected-component helpers.


// ============== グラフアルゴリズム ==============
// ============== DFS ==============
struct GraphDFS {
    const Graph *graph_ref = nullptr;
    V<int> used, parent, tin, tout, comp_id, order, post_order;
    int comp_cnt = 0;
    int timer = 0;

    GraphDFS() = default;

    explicit GraphDFS(const Graph &graph) {
        build_all(graph);
    }

    GraphDFS(const Graph &graph, const int s) {
        build(graph, s);
    }

    void build(const Graph &graph, int s) {
        s = graph.to_internal(s);
        init(graph);
        run_dfs(V<int>{s});
    }

    void build_multi(const Graph &graph, const V<int> &starts) {
        V<int> internal_starts = starts;
        for (auto &s : internal_starts) {
            s = graph.to_internal(s);
        }

        init(graph);
        run_dfs(internal_starts);
    }

    void build_all(const Graph &graph) {
        const int n = graph.size();
        V<int> starts(n);
        iota(all(starts), 0);

        init(graph);
        run_dfs(starts);
    }

    void build_all(const Graph &graph, const V<int> &starts) {
        const int n = graph.size();
        V<int> internal_starts = starts;
        for (auto &s : internal_starts) {
            s = graph.to_internal(s);
        }
        rep(v, n) {
            internal_starts.push_back(v);
        }

        init(graph);
        run_dfs(internal_starts);
    }

  private:
    void init(const Graph &graph) {
        graph_ref = &graph;
        const int n = graph.size();

        used.assign(n, 0);
        parent.assign(n, -1);
        tin.assign(n, -1);
        tout.assign(n, -1);
        comp_id.assign(n, -1);
        order.clear();
        order.reserve(n);
        post_order.clear();
        post_order.reserve(n);
        comp_cnt = 0;
        timer = 0;
    }

    void run_dfs(const V<int> &starts) {
        const auto &g = graph_ref->graph;

        const auto dfs = yc([&](auto self, int v, const int p) -> void {
            used[v] = 1;
            parent[v] = p;
            tin[v] = timer++;
            comp_id[v] = comp_cnt;
            order.push_back(v);

            for (const auto &e : g[v]) {
                const int to = e.to;
                if (used[to]) continue;
                self(to, v);
            }

            tout[v] = timer;
            post_order.push_back(v);
        });

        for (const int v : starts) {
            if (used[v]) continue;
            dfs(v, -1);
            comp_cnt++;
        }
    }
};

// ============== BFS ==============
struct GraphBFS {
    const Graph *graph_ref = nullptr;
    V<int> dist, parent;
    V<int> order, source;

    GraphBFS() = default;

    GraphBFS(const Graph &graph, const int s) {
        build(graph, s);
    }

    void build(const Graph &graph, int s) {
        graph_ref = &graph;
        const auto &g = graph.graph;
        const int n = graph.size();

        s = graph.to_internal(s);

        dist.assign(n, -1);
        parent.assign(n, -1);
        source.assign(n, -1);
        order.clear();
        order.reserve(n);

        queue<int> q;

        dist[s] = 0;
        source[s] = s;
        q.push(s);

        run_bfs(q, g);
    }

    void build_multi(const Graph &graph, const V<int> &starts) {
        graph_ref = &graph;
        const auto &g = graph.graph;
        const int n = graph.size();

        dist.assign(n, -1);
        parent.assign(n, -1);
        source.assign(n, -1);
        order.clear();
        order.reserve(n);

        queue<int> q;

        for (int s : starts) {
            s = graph.to_internal(s);

            if (dist[s] != -1) continue;

            dist[s] = 0;
            source[s] = s;
            q.push(s);
        }

        run_bfs(q, g);
    }

    [[nodiscard]] V<int> path(int t) const {
        const Graph &graph = *graph_ref;
        t = graph.to_internal(t);

        if (source[t] == -1) return {};

        V<int> res;
        const int s = source[t];

        for (int v = t; v != -1; v = parent[v]) {
            res.push_back(v);
            if (v == s) break;
        }

        if (res.back() != s) return {};

        reverse(all(res));
        for (auto &v : res) {
            v = graph.to_external(v);
        }
        return res;
    }

private:
    void run_bfs(queue<int> &q, const V<V<Edge>> &g) {
        while (!q.empty()) {
            const int v = q.front();
            q.pop();

            order.push_back(v);

            for (const auto &e : g[v]) {
                const int to = e.to;
                if (dist[to] != -1) continue;

                dist[to] = dist[v] + 1;
                parent[to] = v;
                source[to] = source[v];

                q.push(to);
            }
        }
    }
};

// ============== 連結成分 ==============
struct ConnectedComponents {
    const Graph *graph_ref = nullptr;
    V<int> comp_id;
    V<int> comp_size;
    int comp_cnt = 0;

    ConnectedComponents() = default;

    explicit ConnectedComponents(const Graph &graph) {
        build(graph);
    }

    void build(const Graph &graph) {
        graph_ref = &graph;
        const auto &g = graph.graph;
        const int n = graph.size();

        comp_id.assign(n, -1);
        comp_size.clear();
        comp_cnt = 0;

        rep(s, n) {
            if (comp_id[s] != -1) continue;

            queue<int> q;
            q.push(s);
            comp_id[s] = comp_cnt;

            int sz = 0;

            while (!q.empty()) {
                const int v = q.front();
                q.pop();

                sz++;

                for (const auto &e : g[v]) {
                    const int to = e.to;

                    if (comp_id[to] != -1) continue;

                    comp_id[to] = comp_cnt;
                    q.push(to);
                }
            }

            comp_size.push_back(sz);
            comp_cnt++;
        }
    }

    [[nodiscard]] bool same(int a, int b) const {
        const Graph &graph = *graph_ref;
        a = graph.to_internal(a);
        b = graph.to_internal(b);
        return comp_id[a] == comp_id[b];
    }

    [[nodiscard]] int size(int v) const {
        const Graph &graph = *graph_ref;
        v = graph.to_internal(v);
        return comp_size[comp_id[v]];
    }

    [[nodiscard]] int count() const {
        return comp_cnt;
    }
};

// ===== bundled from library/shortest_path.hpp =====
// Shortest path algorithms for Graph.


// ============== Dijkstra ==============
struct Dijkstra {
    const Graph *graph_ref = nullptr;
    int source = -1;
    V<ll> dist;
    V<int> parent;
    V<int> order;

    Dijkstra() = default;

    Dijkstra(const Graph &graph, const int s) {
        build(graph, s);
    }

    void build(const Graph &graph, int s) {
        graph_ref = &graph;
        const auto &g = graph.graph;
        const int n = graph.size();

        s = graph.to_internal(s);
        source = s;

        dist.assign(n, INF_L);
        parent.assign(n, -1);
        order.clear();
        order.reserve(n);

        minpq<pair<ll, int>> pq;

        dist[s] = 0;
        pq.emplace(0, s);

        while (!pq.empty()) {
            const auto [d, v] = pq.top();
            pq.pop();

            if (d != dist[v]) continue;

            order.push_back(v);

            for (const auto &e : g[v]) {
                const int to = e.to;
                const ll nd = dist[v] + e.w;

                if (dist[to] <= nd) continue;

                dist[to] = nd;
                parent[to] = v;

                pq.emplace(nd, to);
            }
        }
    }

    [[nodiscard]] ll distance(int t) const {
        const Graph &graph = *graph_ref;
        t = graph.to_internal(t);
        return dist[t];
    }

    [[nodiscard]] bool reachable(int t) const {
        return distance(t) != INF_L;
    }

    [[nodiscard]] V<int> path(int t) const {
        const Graph &graph = *graph_ref;
        t = graph.to_internal(t);

        if (t == source) return V<int>{graph.to_external(source)};
        if (parent[t] == -1) return {};

        V<int> res;

        for (int v = t; v != -1; v = parent[v]) {
            res.push_back(v);
            if (v == source) break;
        }

        if (res.back() != source) return {};

        reverse(all(res));

        for (auto &v : res) {
            v = graph.to_external(v);
        }

        return res;
    }
};

// ===== bundled from library/dag.h =====
struct TopologicalSort {
    const Graph* graph_ref = nullptr;
    V<int> order;
    V<int> indeg;
    bool is_dag = false;

    TopologicalSort() = default;
    explicit TopologicalSort(const Graph& g) {
        build(g);
    }

    void build(const Graph& g) {
        order.clear();
        is_dag = false;

        graph_ref = &g;

        const int n = g.size();
        indeg.assign(n, 0);

        rep(i, n) {
            for (const auto& e : g.graph[i]) {
                indeg[e.to]++;
            }
        }

        queue<int> q;
        rep(i, n) {
            if (indeg[i] == 0) q.push(i);
        }

        V<int> cur_indeg = indeg;

        while (!q.empty()) {
            const int v = q.front();
            order.push_back(v);
            q.pop();

            for (auto e : g.graph[v]) {
                const int to = e.to;

                cur_indeg[to]--;
                if (cur_indeg[to] == 0) q.push(to);
            }
        }

        is_dag = static_cast<int>(order.size()) == n;
    }

    V<int> order_external() const {
        V<int> res = order;
        if (graph_ref && graph_ref->one_indexed) {
            for (auto& v : res) v++;
        }
        return res;
    }
};

struct DirectedCycle {
    const Graph* graph_ref = nullptr;
    V<int> cycle;
    bool has_cycle = false;

    DirectedCycle() = default;

    explicit DirectedCycle(const Graph& g) {
        build(g);
    }

    void build(const Graph& g) {
        graph_ref = &g;
        cycle.clear();
        has_cycle = false;

        const int n = g.size();
        V<int> color(n, 0), parent(n, -1);

        const auto dfs = yc([&](auto self, int v) -> bool {
            color[v] = 1;

            for (const auto &e : g.graph[v]) {
                const int to = e.to;

                if (color[to] == 0) {
                    parent[to] = v;
                    if (self(to)) return true;
                } else if (color[to] == 1) {
                    cycle.push_back(to);
                    for (int x = v; x != to; x = parent[x]) {
                        cycle.push_back(x);
                    }
                    reverse(all(cycle));
                    has_cycle = true;
                    return true;
                }
            }

            color[v] = 2;
            return false;
        });

        rep(v, n) {
            if (color[v] != 0) continue;
            if (dfs(v)) return;
        }
    }

    V<int> cycle_external() const {
        V<int> res = cycle;
        if (graph_ref && graph_ref->one_indexed) {
            for (auto &v : res) v++;
        }
        return res;
    }
};
struct SCC {
    const Graph* graph_ref = nullptr;
    int comp_cnt = 0;
    V<int> comp_id;
    V<V<int>> groups;

    SCC() = default;

    explicit SCC(const Graph& g) {
        build(g);
    }

    void build(const Graph& g) {
        graph_ref = &g;

        const int n = g.size();

        Graph rg(n, false, g.weighted, false);
        rep(v, n) {
            for (const auto &e : g.graph[v]) {
                rg.add_edge_internal(e.to, v, e.w);
            }
        }

        GraphDFS dfs(g);
        V<int> order = dfs.post_order;
        reverse(all(order));

        comp_id.assign(n, -1);
        groups.clear();

        GraphDFS rdfs;
        rdfs.build_all(rg, order);

        comp_cnt = rdfs.comp_cnt;
        comp_id = rdfs.comp_id;

        groups.assign(comp_cnt, {});
        rep(v, n) {
            groups[comp_id[v]].push_back(v);
        }
    }

    bool same(int a, int b) const {
        a = graph_ref->to_internal(a);
        b = graph_ref->to_internal(b);
        return comp_id[a] == comp_id[b];
    }

    int id(int v) const {
        v = graph_ref->to_internal(v);
        return comp_id[v];
    }

    int size(int v) const {
        v = graph_ref->to_internal(v);
        return static_cast<int>(groups[comp_id[v]].size());
    }
};

template <class T = ll>
struct DAGLongestPath {
    const Graph* graph_ref = nullptr;
    V<T> dist;
    V<int> parent;
    V<int> order;
    bool is_dag = false;

    DAGLongestPath() = default;

    DAGLongestPath(const Graph& g, int s) {
        build(g, s);
    }

    explicit DAGLongestPath(const Graph& g) {
        build_all(g);
    }

    void build(const Graph& g, int s) {
        graph_ref = &g;
        s = g.to_internal(s);

        init(g);
        if (!is_dag) return;

        dist[s] = T(0);
        relax(g);
    }

    void build_all(const Graph& g) {
        graph_ref = &g;
        const int n = g.size();

        init(g);
        if (!is_dag) return;

        rep(v, n) {
            dist[v] = T(0);
        }
        relax(g);
    }

    T distance(int t) const {
        t = graph_ref->to_internal(t);
        return dist[t];
    }

    bool reachable(int t) const {
        return distance(t) != neg_inf();
    }

    V<int> path(int t) const {
        t = graph_ref->to_internal(t);
        if (dist[t] == neg_inf()) return {};

        V<int> res;
        for (int v = t; v != -1; v = parent[v]) {
            res.push_back(v);
        }
        reverse(all(res));

        for (auto &v : res) {
            v = graph_ref->to_external(v);
        }
        return res;
    }

  private:
    static T neg_inf() {
        return numeric_limits<T>::lowest() / T(4);
    }

    void init(const Graph& g) {
        const int n = g.size();
        TopologicalSort topo(g);

        is_dag = topo.is_dag;
        order = topo.order;
        dist.assign(n, neg_inf());
        parent.assign(n, -1);
    }

    void relax(const Graph& g) {
        for (const int v : order) {
            if (dist[v] == neg_inf()) continue;

            for (const auto &e : g.graph[v]) {
                const int to = e.to;
                const T nd = dist[v] + static_cast<T>(e.w);

                if (dist[to] >= nd) continue;

                dist[to] = nd;
                parent[to] = v;
            }
        }
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
