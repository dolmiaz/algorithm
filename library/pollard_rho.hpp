#pragma once

#include "prime_test.hpp"

#include <chrono>
#include <random>

[[nodiscard]] inline ull pollard_rho(ull n) {
    if (n % 2 == 0) return 2;
    static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

    while (true) {
        const ull c = uniform_int_distribution<ull>(1, n - 1)(rng);
        ull x = uniform_int_distribution<ull>(0, n - 1)(rng);
        ull y = x;
        ull d = 1;

        const auto f = [&](ull v) {
            return (mod_mul64(v, v, n) + c) % n;
        };

        while (d == 1) {
            x = f(x);
            y = f(f(y));
            const ull diff = x > y ? x - y : y - x;
            d = gcd(diff, n);
        }

        if (d != n) return d;
    }
}

inline void factorize_pollard_dfs(ull n, V<ull>& res) {
    if (n == 1) return;
    if (is_prime64(n)) {
        res.push_back(n);
        return;
    }
    const ull d = pollard_rho(n);
    factorize_pollard_dfs(d, res);
    factorize_pollard_dfs(n / d, res);
}

[[nodiscard]] inline V<ull> factorize_pollard(ull n) {
    V<ull> res;
    factorize_pollard_dfs(n, res);
    sort(all(res));
    return res;
}
