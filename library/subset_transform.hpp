#pragma once

#include "basic.hpp"

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
