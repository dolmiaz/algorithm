#pragma once

#include "number_theory.hpp"

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
