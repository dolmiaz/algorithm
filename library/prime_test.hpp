#pragma once

#include "math.hpp"

[[nodiscard]] inline ull mod_mul64(const ull a, const ull b, const ull mod) {
    return static_cast<ull>(static_cast<__uint128_t>(a) * b % mod);
}

[[nodiscard]] inline ull mod_pow64(ull a, ull n, const ull mod) {
    ull res = 1 % mod;
    while (n > 0) {
        if (n & 1) res = mod_mul64(res, a, mod);
        a = mod_mul64(a, a, mod);
        n >>= 1;
    }
    return res;
}

[[nodiscard]] inline bool is_prime64(const ull n) {
    if (n < 2) return false;
    for (const ull p : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL}) {
        if (n % p == 0) return n == p;
    }

    ull d = n - 1, s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }

    for (const ull a : {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL}) {
        if (a % n == 0) continue;
        ull x = mod_pow64(a % n, d, n);
        if (x == 1 || x == n - 1) continue;

        bool composite = true;
        for (ull r = 1; r < s; r++) {
            x = mod_mul64(x, x, n);
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}
