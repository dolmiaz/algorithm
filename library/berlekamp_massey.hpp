#pragma once

#include "modint.hpp"

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
