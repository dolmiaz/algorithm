#include <algorithm>
#include <array>
#include <bits/stdc++.h>
#include <chrono>
#include <cmath>
#include <complex>
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <random>
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

// ===== Math / Number Theory =====

// ===== bundled from library/math.hpp =====
template <class T>
[[nodiscard]] T fast_pow(T a, ull n) {
    T res = T(1);
    while (n > 0) {
        if (n & 1) res *= a;
        a *= a;
        n >>= 1;
    }
    return res;
}

[[nodiscard]] inline ll mod_pow(ll a, ull n, const ll mod) {
    if (mod == 1) return 0;
    a %= mod;
    if (a < 0) a += mod;
    ll res = 1 % mod;
    while (n > 0) {
        if (n & 1) res = static_cast<ll>(static_cast<__int128>(res) * a % mod);
        a = static_cast<ll>(static_cast<__int128>(a) * a % mod);
        n >>= 1;
    }
    return res;
}

// ===== bundled from library/modint.hpp =====
template <int MOD>
struct static_modint {
    using mint = static_modint;
    int v = 0;

    [[nodiscard]] static constexpr int mod() { return MOD; }

    static_modint() = default;
    template <class T> static_modint(T x) {
        ll y = static_cast<ll>(x % static_cast<T>(MOD));
        if (y < 0) y += MOD;
        v = static_cast<int>(y);
    }

    [[nodiscard]] int val() const { return v; }

    mint& operator+=(const mint& rhs) {
        v += rhs.v;
        if (v >= MOD) v -= MOD;
        return *this;
    }
    mint& operator-=(const mint& rhs) {
        v -= rhs.v;
        if (v < 0) v += MOD;
        return *this;
    }
    mint& operator*=(const mint& rhs) {
        v = static_cast<int>(static_cast<ll>(v) * rhs.v % MOD);
        return *this;
    }
    mint& operator/=(const mint& rhs) { return *this *= rhs.inv(); }

    [[nodiscard]] mint operator+() const { return *this; }
    [[nodiscard]] mint operator-() const { return mint(0) - *this; }

    [[nodiscard]] friend mint operator+(mint lhs, const mint& rhs) { return lhs += rhs; }
    [[nodiscard]] friend mint operator-(mint lhs, const mint& rhs) { return lhs -= rhs; }
    [[nodiscard]] friend mint operator*(mint lhs, const mint& rhs) { return lhs *= rhs; }
    [[nodiscard]] friend mint operator/(mint lhs, const mint& rhs) { return lhs /= rhs; }
    [[nodiscard]] friend bool operator==(const mint& lhs, const mint& rhs) { return lhs.v == rhs.v; }
    [[nodiscard]] friend bool operator!=(const mint& lhs, const mint& rhs) { return !(lhs == rhs); }

    [[nodiscard]] mint pow(ll n) const {
        mint res = 1, x = *this;
        while (n > 0) {
            if (n & 1) res *= x;
            x *= x;
            n >>= 1;
        }
        return res;
    }

    [[nodiscard]] mint inv() const {
        ll a = v, b = MOD, x = 1, y = 0;
        while (b) {
            const ll q = a / b;
            a -= q * b;
            swap(a, b);
            x -= q * y;
            swap(x, y);
        }
        if (x < 0) x += MOD;
        return mint(x);
    }

    friend ostream& operator<<(ostream& os, const mint& x) { return os << x.v; }
    friend istream& operator>>(istream& is, mint& x) {
        ll input_value;
        is >> input_value;
        x = mint(input_value);
        return is;
    }
};

template <int ID>
struct dynamic_modint {
    using mint = dynamic_modint;
    static int& mod_ref() {
        static int m = 998244353;
        return m;
    }
    int v = 0;

    [[nodiscard]] static int mod() { return mod_ref(); }
    static void set_mod(const int m) { mod_ref() = m; }

    dynamic_modint() = default;
    template <class T> dynamic_modint(T x) {
        const int m = mod();
        ll y = static_cast<ll>(x % static_cast<T>(m));
        if (y < 0) y += m;
        v = static_cast<int>(y);
    }

    [[nodiscard]] int val() const { return v; }

    mint& operator+=(const mint& rhs) {
        v += rhs.v;
        if (v >= mod()) v -= mod();
        return *this;
    }
    mint& operator-=(const mint& rhs) {
        v -= rhs.v;
        if (v < 0) v += mod();
        return *this;
    }
    mint& operator*=(const mint& rhs) {
        v = static_cast<int>(static_cast<ll>(v) * rhs.v % mod());
        return *this;
    }
    mint& operator/=(const mint& rhs) { return *this *= rhs.inv(); }

    [[nodiscard]] mint operator+() const { return *this; }
    [[nodiscard]] mint operator-() const { return mint(0) - *this; }

    [[nodiscard]] friend mint operator+(mint lhs, const mint& rhs) { return lhs += rhs; }
    [[nodiscard]] friend mint operator-(mint lhs, const mint& rhs) { return lhs -= rhs; }
    [[nodiscard]] friend mint operator*(mint lhs, const mint& rhs) { return lhs *= rhs; }
    [[nodiscard]] friend mint operator/(mint lhs, const mint& rhs) { return lhs /= rhs; }
    [[nodiscard]] friend bool operator==(const mint& lhs, const mint& rhs) { return lhs.v == rhs.v; }
    [[nodiscard]] friend bool operator!=(const mint& lhs, const mint& rhs) { return !(lhs == rhs); }

    [[nodiscard]] mint pow(ll n) const {
        mint res = 1, x = *this;
        while (n > 0) {
            if (n & 1) res *= x;
            x *= x;
            n >>= 1;
        }
        return res;
    }

    [[nodiscard]] mint inv() const {
        ll a = v, b = mod(), x = 1, y = 0;
        while (b) {
            const ll q = a / b;
            a -= q * b;
            swap(a, b);
            x -= q * y;
            swap(x, y);
        }
        if (x < 0) x += mod();
        return mint(x);
    }

    friend ostream& operator<<(ostream& os, const mint& x) { return os << x.v; }
    friend istream& operator>>(istream& is, mint& x) {
        ll input_value;
        is >> input_value;
        x = mint(input_value);
        return is;
    }
};

using modint998244353 = static_modint<998244353>;
using modint1000000007 = static_modint<1000000007>;

// ===== bundled from library/number_theory.hpp =====
[[nodiscard]] inline ll ext_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = (a >= 0 ? 1 : -1);
        y = 0;
        return abs(a);
    }
    ll x1, y1;
    const ll g = ext_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

[[nodiscard]] inline ll mod_inv(ll a, const ll mod) {
    ll x, y;
    const ll g = ext_gcd(a, mod, x, y);
    if (g != 1) return -1;
    x %= mod;
    if (x < 0) x += mod;
    return x;
}

[[nodiscard]] inline V<ll> divisors(ll n) {
    V<ll> res;
    for (ll d = 1; d * d <= n; d++) {
        if (n % d != 0) continue;
        res.push_back(d);
        if (d * d != n) res.push_back(n / d);
    }
    sort(all(res));
    return res;
}

[[nodiscard]] inline V<pair<ll, int>> factorize(ll n) {
    V<pair<ll, int>> res;
    for (ll p = 2; p * p <= n; p += (p == 2 ? 1 : 2)) {
        if (n % p != 0) continue;
        int e = 0;
        while (n % p == 0) {
            n /= p;
            e++;
        }
        res.emplace_back(p, e);
    }
    if (n > 1) res.emplace_back(n, 1);
    return res;
}

[[nodiscard]] inline ll euler_phi(ll n) {
    ll res = n;
    for (const auto &[p, _] : factorize(n)) {
        res = res / p * (p - 1);
    }
    return res;
}

[[nodiscard]] inline V<int> sieve_primes(const int n) {
    V<int> primes;
    V<int> is_prime(n + 1, 1);
    if (n >= 0) is_prime[0] = 0;
    if (n >= 1) is_prime[1] = 0;
    for (int i = 2; i <= n; i++) {
        if (!is_prime[i]) continue;
        primes.push_back(i);
        if (static_cast<ll>(i) * i <= n) {
            for (ll j = static_cast<ll>(i) * i; j <= n; j += i) is_prime[j] = 0;
        }
    }
    return primes;
}

// ===== bundled from library/crt.hpp =====
[[nodiscard]] inline pair<ll, ll> crt_pair(ll r1, ll m1, ll r2, ll m2) {
    if (m1 < 0) m1 = -m1;
    if (m2 < 0) m2 = -m2;
    r1 %= m1;
    if (r1 < 0) r1 += m1;
    r2 %= m2;
    if (r2 < 0) r2 += m2;

    ll x, y;
    const ll g = ext_gcd(m1, m2, x, y);
    if ((r2 - r1) % g != 0) return {0, 0};

    const ll u = m2 / g;
    ll t = static_cast<ll>(static_cast<__int128>((r2 - r1) / g) * x % u);
    if (t < 0) t += u;

    const ll lcm = m1 * u;
    ll r = static_cast<ll>((r1 + static_cast<__int128>(m1) * t) % lcm);
    if (r < 0) r += lcm;
    return {r, lcm};
}

[[nodiscard]] inline pair<ll, ll> crt(const V<ll>& r, const V<ll>& m) {
    ll r0 = 0, m0 = 1;
    rep(i, r.size()) {
        auto merged = crt_pair(r0, m0, r[i], m[i]);
        if (merged.second == 0) return {0, 0};
        r0 = merged.first;
        m0 = merged.second;
    }
    return {r0, m0};
}

// ===== bundled from library/floor_sum.hpp =====
[[nodiscard]] inline ll floor_sum(ll n, ll m, ll a, ll b) {
    ll ans = 0;
    while (true) {
        if (a >= m) {
            ans += (n - 1) * n * (a / m) / 2;
            a %= m;
        }
        if (b >= m) {
            ans += n * (b / m);
            b %= m;
        }

        const ll y_max = a * n + b;
        if (y_max < m) break;
        n = y_max / m;
        b = y_max % m;
        swap(m, a);
    }
    return ans;
}

// ===== bundled from library/mobius.hpp =====
[[nodiscard]] inline V<int> mobius_table(const int n) {
    V<int> mu(n + 1), primes;
    V<int> is_comp(n + 1, 0);
    mu[0] = 0;
    if (n >= 1) mu[1] = 1;

    for (int i = 2; i <= n; i++) {
        if (!is_comp[i]) {
            primes.push_back(i);
            mu[i] = -1;
        }

        for (const int p : primes) {
            if (static_cast<ll>(i) * p > n) break;
            is_comp[i * p] = 1;
            if (i % p == 0) {
                mu[i * p] = 0;
                break;
            }
            mu[i * p] = -mu[i];
        }
    }

    return mu;
}

// ===== bundled from library/prime_test.hpp =====
[[nodiscard]] inline ull mod_mul64(const ull a, const ull b, const ull mod) {
    return static_cast<ull>(static_cast<__uint128_t>(a) * b % mod);
}

[[nodiscard]] inline ull mod_pow64(ull a, ull n, const ull mod) {
    ull res = 1 % mod;
    while (n > 0) {
        if (n & 1) res = mod_mul64(res, a, mod);
        a = mod_mul64(a, a, mod);
        n >>= 1;
    }
    return res;
}

[[nodiscard]] inline bool is_prime64(const ull n) {
    if (n < 2) return false;
    for (const ull p : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL}) {
        if (n % p == 0) return n == p;
    }

    ull d = n - 1, s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }

    for (const ull a : {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL}) {
        if (a % n == 0) continue;
        ull x = mod_pow64(a % n, d, n);
        if (x == 1 || x == n - 1) continue;

        bool composite = true;
        for (ull r = 1; r < s; r++) {
            x = mod_mul64(x, x, n);
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

// ===== bundled from library/pollard_rho.hpp =====
[[nodiscard]] inline ull pollard_rho(ull n) {
    if (n % 2 == 0) return 2;
    static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

    while (true) {
        const ull c = uniform_int_distribution<ull>(1, n - 1)(rng);
        ull x = uniform_int_distribution<ull>(0, n - 1)(rng);
        ull y = x;
        ull d = 1;

        const auto f = [&](ull v) {
            return (mod_mul64(v, v, n) + c) % n;
        };

        while (d == 1) {
            x = f(x);
            y = f(f(y));
            const ull diff = x > y ? x - y : y - x;
            d = gcd(diff, n);
        }

        if (d != n) return d;
    }
}

inline void factorize_pollard_dfs(ull n, V<ull>& res) {
    if (n == 1) return;
    if (is_prime64(n)) {
        res.push_back(n);
        return;
    }
    const ull d = pollard_rho(n);
    factorize_pollard_dfs(d, res);
    factorize_pollard_dfs(n / d, res);
}

[[nodiscard]] inline V<ull> factorize_pollard(ull n) {
    V<ull> res;
    factorize_pollard_dfs(n, res);
    sort(all(res));
    return res;
}

// ===== bundled from library/discrete_log.hpp =====
[[nodiscard]] inline ll discrete_log(ll a, ll b, ll m) {
    a %= m;
    if (a < 0) a += m;
    b %= m;
    if (b < 0) b += m;
    if (m == 1) return 0;
    if (b == 1) return 0;
    if (a == 0) return b == 0 ? 1 : -1;

    ll add = 0, k = 1;
    for (ll g = gcd(a, m); g > 1; g = gcd(a, m)) {
        if (b == k) return add;
        if (b % g != 0) return -1;
        b /= g;
        m /= g;
        k = static_cast<ll>(static_cast<__int128>(k) * (a / g) % m);
        add++;
    }

    const ll n = static_cast<ll>(sqrt(static_cast<long double>(m)) + 1);
    unordered_map<ll, ll> baby;
    ll cur = b;
    rep(q, n) {
        if (!baby.count(cur)) baby[cur] = q;
        cur = static_cast<ll>(static_cast<__int128>(cur) * a % m);
    }

    const ll an = mod_pow(a, n, m);
    cur = k;
    for (ll p = 1; p <= n + 1; p++) {
        cur = static_cast<ll>(static_cast<__int128>(cur) * an % m);
        if (baby.count(cur)) {
            const ll ans = p * n - baby[cur] + add;
            if (ans >= 0) return ans;
        }
    }
    return -1;
}

// ===== bundled from library/primitive_root.hpp =====
[[nodiscard]] inline int primitive_root(const int mod) {
    if (mod == 2) return 1;
    V<int> factors;
    int x = mod - 1;
    for (int p = 2; static_cast<ll>(p) * p <= x; p++) {
        if (x % p != 0) continue;
        factors.push_back(p);
        while (x % p == 0) x /= p;
    }
    if (x > 1) factors.push_back(x);

    for (int g = 2;; g++) {
        bool ok = true;
        for (const int p : factors) {
            if (mod_pow(g, (mod - 1) / p, mod) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) return g;
    }
}

// ===== bundled from library/garner.hpp =====
[[nodiscard]] inline ll garner(const V<ll>& r, const V<ll>& m, const ll mod) {
    const int n = static_cast<int>(r.size());
    V<ll> coeff(n + 1, 1), constants(n + 1, 0), mods = m;
    mods.push_back(mod);

    rep(i, n) {
        ll t = (r[i] - constants[i]) % mods[i];
        if (t < 0) t += mods[i];
        t = static_cast<ll>(static_cast<__int128>(t) * mod_inv(coeff[i], mods[i]) % mods[i]);

        for (int j = i + 1; j <= n; j++) {
            constants[j] = (constants[j] + static_cast<__int128>(coeff[j]) * t) % mods[j];
            coeff[j] = static_cast<ll>(static_cast<__int128>(coeff[j]) * mods[i] % mods[j]);
        }
    }

    return constants[n];
}

// ===== Linear Algebra / Polynomial =====

// ===== bundled from library/matrix.hpp =====
template <class T>
using Matrix = V<V<T>>;

template <class T>
[[nodiscard]] Matrix<T> identity_matrix(const int n) {
    Matrix<T> res(n, V<T>(n, T(0)));
    rep(i, n) res[i][i] = T(1);
    return res;
}

template <class T>
[[nodiscard]] Matrix<T> matrix_mul(const Matrix<T>& a, const Matrix<T>& b) {
    const int n = static_cast<int>(a.size());
    const int m = static_cast<int>(b[0].size());
    const int p = static_cast<int>(b.size());
    Matrix<T> res(n, V<T>(m, T(0)));

    rep(i, n) {
        rep(k, p) {
            if (a[i][k] == T(0)) continue;
            rep(j, m) {
                res[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    return res;
}

template <class T>
[[nodiscard]] Matrix<T> matrix_pow(Matrix<T> a, ull e) {
    Matrix<T> res = identity_matrix<T>(static_cast<int>(a.size()));
    while (e > 0) {
        if (e & 1) res = matrix_mul(res, a);
        a = matrix_mul(a, a);
        e >>= 1;
    }
    return res;
}

// ===== bundled from library/linear_algebra.hpp =====
template <class T>
[[nodiscard]] int gaussian_elimination(V<V<T>>& a, const int variables = -1) {
    const int h = static_cast<int>(a.size());
    if (h == 0) return 0;
    const int w = static_cast<int>(a[0].size());
    const int vars = variables == -1 ? w : variables;

    int rank = 0;
    rep(col, vars) {
        int pivot = -1;
        for (int row = rank; row < h; row++) {
            if (a[row][col] != T(0)) {
                pivot = row;
                break;
            }
        }
        if (pivot == -1) continue;

        swap(a[rank], a[pivot]);
        const T inv = T(1) / a[rank][col];
        for (int col2 = col; col2 < w; col2++) a[rank][col2] *= inv;

        rep(row, h) {
            if (row == rank || a[row][col] == T(0)) continue;
            const T factor = a[row][col];
            for (int col2 = col; col2 < w; col2++) {
                a[row][col2] -= factor * a[rank][col2];
            }
        }

        rank++;
    }

    return rank;
}

template <class T>
[[nodiscard]] int matrix_rank(Matrix<T> a) {
    return gaussian_elimination(a);
}

template <class T>
[[nodiscard]] pair<bool, V<T>> solve_linear_system(Matrix<T> a, V<T> b) {
    const int n = static_cast<int>(a.size());
    const int m = n == 0 ? 0 : static_cast<int>(a[0].size());
    rep(i, n) a[i].push_back(b[i]);

    const int rank = gaussian_elimination(a, m);
    for (int row = rank; row < n; row++) {
        if (a[row][m] != T(0)) return {false, {}};
    }

    V<T> x(m, T(0));
    rep(row, rank) {
        int pivot = -1;
        rep(col, m) {
            if (a[row][col] == T(1)) {
                pivot = col;
                break;
            }
        }
        if (pivot != -1) x[pivot] = a[row][m];
    }

    return {true, x};
}

// ===== bundled from library/xor_basis.hpp =====
struct XorBasis {
    static constexpr int LOG = 63;
    array<ull, LOG + 1> basis{};
    int rank_value = 0;

    [[nodiscard]] bool insert(ull x) {
        for (int b = LOG; b >= 0; b--) {
            if (((x >> b) & 1) == 0) continue;
            if (!basis[b]) {
                basis[b] = x;
                rank_value++;
                return true;
            }
            x ^= basis[b];
        }
        return false;
    }

    [[nodiscard]] bool can_make(ull x) const {
        for (int b = LOG; b >= 0; b--) {
            if (((x >> b) & 1) == 0) continue;
            if (!basis[b]) return false;
            x ^= basis[b];
        }
        return true;
    }

    [[nodiscard]] ull max_xor(ull x = 0) const {
        for (int b = LOG; b >= 0; b--) {
            if ((x ^ basis[b]) > x) x ^= basis[b];
        }
        return x;
    }

    [[nodiscard]] int rank() const {
        return rank_value;
    }
};

// ===== bundled from library/convolution.hpp =====
template <class Mint>
void ntt(V<Mint>& a, const bool invert) {
    const int n = static_cast<int>(a.size());
    if (n <= 1) return;
    static V<int> rev;
    static V<Mint> roots{0, 1};

    if (static_cast<int>(rev.size()) != n) {
        const int k = __builtin_ctz(n);
        rev.assign(n, 0);
        rep(i, n) {
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
        }
    }

    if (static_cast<int>(roots.size()) < n) {
        int k = __builtin_ctz(static_cast<int>(roots.size()));
        roots.resize(n);
        while ((1 << k) < n) {
            Mint e = Mint(primitive_root(Mint::mod())).pow((Mint::mod() - 1) >> (k + 1));
            for (int i = 1 << (k - 1); i < (1 << k); i++) {
                roots[2 * i] = roots[i];
                roots[2 * i + 1] = roots[i] * e;
            }
            k++;
        }
    }

    rep(i, n) {
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    }

    for (int len = 1; len < n; len <<= 1) {
        for (int i = 0; i < n; i += 2 * len) {
            rep(j, len) {
                Mint u = a[i + j];
                Mint v = a[i + j + len] * roots[len + j];
                a[i + j] = u + v;
                a[i + j + len] = u - v;
            }
        }
    }

    if (invert) {
        reverse(a.begin() + 1, a.end());
        const Mint inv_n = Mint(n).inv();
        for (auto& x : a) x *= inv_n;
    }
}

template <class Mint>
[[nodiscard]] V<Mint> convolution_ntt(V<Mint> a, V<Mint> b) {
    if (a.empty() || b.empty()) return {};
    const int need = static_cast<int>(a.size() + b.size() - 1);
    int n = 1;
    while (n < need) n <<= 1;
    a.resize(n);
    b.resize(n);
    ntt(a, false);
    ntt(b, false);
    rep(i, n) a[i] *= b[i];
    ntt(a, true);
    a.resize(need);
    return a;
}

[[nodiscard]] inline V<ll> convolution_fft(const V<ll>& a, const V<ll>& b) {
    if (a.empty() || b.empty()) return {};
    using cd = complex<double>;
    const double PI_D = acos(-1.0);
    const int need = static_cast<int>(a.size() + b.size() - 1);
    int n = 1;
    while (n < need) n <<= 1;

    V<cd> fa(n), fb(n);
    rep(i, a.size()) fa[i] = static_cast<double>(a[i]);
    rep(i, b.size()) fb[i] = static_cast<double>(b[i]);

    const auto fft = [&](V<cd>& f, const bool invert) {
        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            for (; j & bit; bit >>= 1) j ^= bit;
            j ^= bit;
            if (i < j) swap(f[i], f[j]);
        }
        for (int len = 2; len <= n; len <<= 1) {
            const double ang = 2 * PI_D / len * (invert ? -1 : 1);
            const cd wlen(cos(ang), sin(ang));
            for (int i = 0; i < n; i += len) {
                cd w = 1;
                for (int j = 0; j < len / 2; j++) {
                    cd u = f[i + j], v = f[i + j + len / 2] * w;
                    f[i + j] = u + v;
                    f[i + j + len / 2] = u - v;
                    w *= wlen;
                }
            }
        }
        if (invert) {
            for (auto& x : f) x /= n;
        }
    };

    fft(fa, false);
    fft(fb, false);
    rep(i, n) fa[i] *= fb[i];
    fft(fa, true);

    V<ll> res(need);
    rep(i, need) res[i] = llround(fa[i].real());
    return res;
}

// ===== bundled from library/fps.hpp =====
template <class Mint>
struct FormalPowerSeries : V<Mint> {
    using V<Mint>::V;
    using FPS = FormalPowerSeries;

    [[nodiscard]] FPS pre(const int n) const {
        return FPS(this->begin(), this->begin() + min(n, static_cast<int>(this->size())));
    }

    FPS& normalize() {
        while (!this->empty() && this->back() == Mint(0)) this->pop_back();
        return *this;
    }

    [[nodiscard]] FPS diff() const {
        const int n = static_cast<int>(this->size());
        if (n == 0) return {};
        FPS res(max(0, n - 1));
        for (int i = 1; i < n; i++) res[i - 1] = (*this)[i] * i;
        return res;
    }

    [[nodiscard]] FPS integral() const {
        const int n = static_cast<int>(this->size());
        FPS res(n + 1);
        rep(i, n) res[i + 1] = (*this)[i] / Mint(i + 1);
        return res;
    }

    [[nodiscard]] FPS inv(const int deg) const {
        FPS res{(*this)[0].inv()};
        int n = 1;
        while (n < deg) {
            n <<= 1;
            FPS f = pre(n);
            FPS g = res;
            f.resize(n);
            g.resize(n);
            auto fg = convolution_ntt(f, g);
            fg.resize(n);
            rep(i, n) fg[i] = -fg[i];
            fg[0] += 2;
            auto next = convolution_ntt(g, fg);
            res = FPS(next.begin(), next.end());
            res.resize(n);
        }
        res.resize(deg);
        return res;
    }

    [[nodiscard]] friend FPS operator+(FPS a, const FPS& b) {
        if (a.size() < b.size()) a.resize(b.size());
        rep(i, b.size()) a[i] += b[i];
        return a;
    }
    [[nodiscard]] friend FPS operator-(FPS a, const FPS& b) {
        if (a.size() < b.size()) a.resize(b.size());
        rep(i, b.size()) a[i] -= b[i];
        return a;
    }
    [[nodiscard]] friend FPS operator*(const FPS& a, const FPS& b) {
        auto c = convolution_ntt(V<Mint>(a.begin(), a.end()), V<Mint>(b.begin(), b.end()));
        return FPS(c.begin(), c.end());
    }
};

// ===== bundled from library/linear_recurrence.hpp =====
template <class T>
[[nodiscard]] V<T> kitamasa_combine(const V<T>& a, const V<T>& b, const V<T>& coef) {
    const int d = static_cast<int>(coef.size());
    V<T> tmp(2 * d - 1, T(0));
    rep(i, d) rep(j, d) tmp[i + j] += a[i] * b[j];
    for (int i = 2 * d - 2; i >= d; i--) {
        rep(j, d) tmp[i - d + j] += tmp[i] * coef[j];
    }
    tmp.resize(d);
    return tmp;
}

template <class T>
[[nodiscard]] T linear_recurrence_nth(const V<T>& init, const V<T>& coef, ull n) {
    const int d = static_cast<int>(coef.size());
    if (n < init.size()) return init[n];

    V<T> pol(d, T(0)), e(d, T(0));
    pol[0] = T(1);
    if (d == 1) e[0] = coef[0];
    else e[1] = T(1);

    while (n > 0) {
        if (n & 1) pol = kitamasa_combine(pol, e, coef);
        e = kitamasa_combine(e, e, coef);
        n >>= 1;
    }

    T res = T(0);
    rep(i, d) res += pol[i] * init[i];
    return res;
}

// ===== bundled from library/berlekamp_massey.hpp =====
template <class Mint>
[[nodiscard]] V<Mint> berlekamp_massey(const V<Mint>& s) {
    V<Mint> c{1}, b{1};
    int l = 0, m = 1;
    Mint bb = 1;

    rep(n, s.size()) {
        Mint d = s[n];
        for (int i = 1; i <= l; i++) d += c[i] * s[n - i];
        if (d == Mint(0)) {
            m++;
            continue;
        }

        V<Mint> t = c;
        const Mint coef = d / bb;
        if (static_cast<int>(c.size()) < static_cast<int>(b.size()) + m) {
            c.resize(b.size() + m, Mint(0));
        }
        rep(i, b.size()) c[i + m] -= coef * b[i];

        if (2 * l <= n) {
            l = n + 1 - l;
            b = t;
            bb = d;
            m = 1;
        } else {
            m++;
        }
    }

    c.erase(c.begin());
    for (auto& x : c) x = -x;
    return c;
}

// ===== bundled from library/subset_transform.hpp =====
template <class T>
void subset_zeta(V<T>& f) {
    const int n = static_cast<int>(f.size());
    for (int bit = 1; bit < n; bit <<= 1) {
        rep(mask, n) if (mask & bit) f[mask] += f[mask ^ bit];
    }
}

template <class T>
void subset_mobius(V<T>& f) {
    const int n = static_cast<int>(f.size());
    for (int bit = 1; bit < n; bit <<= 1) {
        rep(mask, n) if (mask & bit) f[mask] -= f[mask ^ bit];
    }
}

template <class T>
void superset_zeta(V<T>& f) {
    const int n = static_cast<int>(f.size());
    for (int bit = 1; bit < n; bit <<= 1) {
        rep(mask, n) if ((mask & bit) == 0) f[mask] += f[mask ^ bit];
    }
}

template <class T>
void superset_mobius(V<T>& f) {
    const int n = static_cast<int>(f.size());
    for (int bit = 1; bit < n; bit <<= 1) {
        rep(mask, n) if ((mask & bit) == 0) f[mask] -= f[mask ^ bit];
    }
}

// ===== bundled from library/fwht.hpp =====
template <class T>
void fwht_xor(V<T>& f, const bool inverse = false) {
    const int n = static_cast<int>(f.size());
    for (int len = 1; len < n; len <<= 1) {
        for (int i = 0; i < n; i += 2 * len) {
            rep(j, len) {
                T x = f[i + j], y = f[i + j + len];
                f[i + j] = x + y;
                f[i + j + len] = x - y;
            }
        }
    }
    if (inverse) {
        const T inv_n = T(1) / T(n);
        for (auto& x : f) x *= inv_n;
    }
}

template <class T>
[[nodiscard]] V<T> convolution_xor(V<T> a, V<T> b) {
    fwht_xor(a, false);
    fwht_xor(b, false);
    rep(i, a.size()) a[i] *= b[i];
    fwht_xor(a, true);
    return a;
}

template <class T>
[[nodiscard]] V<T> convolution_or(V<T> a, V<T> b) {
    subset_zeta(a);
    subset_zeta(b);
    rep(i, a.size()) a[i] *= b[i];
    subset_mobius(a);
    return a;
}

template <class T>
[[nodiscard]] V<T> convolution_and(V<T> a, V<T> b) {
    superset_zeta(a);
    superset_zeta(b);
    rep(i, a.size()) a[i] *= b[i];
    superset_mobius(a);
    return a;
}

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

// ===== String =====

// ===== bundled from library/string.hpp =====
template <class T>
bool is_palindrome(const T& s) {
    int n = static_cast<int>(s.size());
    rep(i, n / 2) {
        if (s[i] != s[n - 1 - i]) return false;
    }
    return true;
}

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

// ===== bundled from library/dag.hpp =====
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

// ===== bundled from library/coloring.hpp =====
struct KColoring {
    const Graph *graph_ref = nullptr;
    int k = 0;
    V<int> color;
    bool found = false;

    KColoring() = default;

    KColoring(const Graph& g, const int k_) {
        build(g, k_);
    }

    bool build(const Graph& g, const int k_) {
        graph_ref = &g;
        k = k_;
        color.assign(g.size(), -1);

        found = solve_by_dsat(g);
        return found;
    }

    int min_colors(const Graph& g) {
        const int n = g.size();
        rep(colors, n + 1) {
            if (build(g, colors)) return colors;
        }
        return -1;
    }

    bool valid() const {
        if (!graph_ref) return false;
        if (static_cast<int>(color.size()) != graph_ref->size()) return false;

        rep(v, graph_ref->size()) {
            if (color[v] < 0 || color[v] >= k) return false;

            for (const auto& e : graph_ref->graph[v]) {
                if (color[v] == color[e.to]) return false;
            }
        }

        return true;
    }

  private:
    V<V<int>> build_undirected_adjacency(const Graph& g) const {
        const int n = g.size();
        V<V<int>> adj(n);

        rep(v, n) {
            for (const auto& e : g.graph[v]) {
                const int to = e.to;
                adj[v].push_back(to);
                if (v != to) adj[to].push_back(v);
            }
        }

        rep(v, n) {
            sort(all(adj[v]));
            adj[v].erase(unique(all(adj[v])), adj[v].end());
        }

        return adj;
    }

    bool solve_by_dsat(const Graph& g) {
        const int n = g.size();
        if (n == 0) return k >= 0;
        if (k <= 0) return false;

        const V<V<int>> adj = build_undirected_adjacency(g);
        rep(v, n) {
            if (binary_search(all(adj[v]), v)) return false;
        }

        const auto dfs = yc([&](auto self, const int colored_count) -> bool {
            if (colored_count == n) return true;

            int best = -1;
            int best_saturation = -1;
            int best_degree = -1;

            rep(v, n) {
                if (color[v] != -1) continue;

                V<int> seen(k, 0);
                int saturation = 0;

                for (const int to : adj[v]) {
                    if (color[to] == -1) continue;
                    if (seen[color[to]]) continue;
                    seen[color[to]] = 1;
                    saturation++;
                }

                const int degree = static_cast<int>(adj[v].size());
                if (
                    saturation > best_saturation ||
                    (saturation == best_saturation && degree > best_degree)
                ) {
                    best = v;
                    best_saturation = saturation;
                    best_degree = degree;
                }
            }

            V<int> forbidden(k, 0);
            for (const int to : adj[best]) {
                if (color[to] != -1) forbidden[color[to]] = 1;
            }

            rep(c, k) {
                if (forbidden[c]) continue;

                color[best] = c;
                if (self(colored_count + 1)) return true;
                color[best] = -1;
            }

            return false;
        });

        return dfs(0);
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
