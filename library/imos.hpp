#pragma once

#include "basic.hpp"

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
