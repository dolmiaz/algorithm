#pragma once

#include "convolution.hpp"

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
