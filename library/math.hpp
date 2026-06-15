#pragma once

#include "basic.hpp"

template <class T>
[[nodiscard]] T fast_pow(T a, ull n) {
    T res = T(1);
    while (n > 0) {
        if (n & 1) res *= a;
        a *= a;
        n >>= 1;
    }
    return res;
}

[[nodiscard]] inline ll mod_pow(ll a, ull n, const ll mod) {
    if (mod == 1) return 0;
    a %= mod;
    if (a < 0) a += mod;
    ll res = 1 % mod;
    while (n > 0) {
        if (n & 1) res = static_cast<ll>(static_cast<__int128>(res) * a % mod);
        a = static_cast<ll>(static_cast<__int128>(a) * a % mod);
        n >>= 1;
    }
    return res;
}
