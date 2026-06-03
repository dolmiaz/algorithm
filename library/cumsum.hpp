// One-dimensional and two-dimensional prefix sum helpers.
#pragma once

#include "basic.hpp"

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
