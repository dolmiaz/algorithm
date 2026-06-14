// Prefix sum and prefix maximum helpers.
#pragma once

#include "basic.hpp"

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
