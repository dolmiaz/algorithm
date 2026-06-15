#pragma once

#include "basic.hpp"

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
