// Small input/output and general utility helpers.
#pragma once

#include "basic.hpp"

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
