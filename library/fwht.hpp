#pragma once

#include "basic.hpp"
#include "subset_transform.hpp"

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
