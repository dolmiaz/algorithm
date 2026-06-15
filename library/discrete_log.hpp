#pragma once

#include "number_theory.hpp"

[[nodiscard]] inline ll discrete_log(ll a, ll b, ll m) {
    a %= m;
    b %= m;
    if (b < 0) b += m;
    if (m == 1) return 0;

    ll add = 0, k = 1;
    for (ll g = gcd(a, m); g > 1; g = gcd(a, m)) {
        if (b == k) return add;
        if (b % g != 0) return -1;
        b /= g;
        m /= g;
        k = static_cast<ll>(static_cast<__int128>(k) * (a / g) % m);
        add++;
    }

    const ll n = static_cast<ll>(sqrt(static_cast<long double>(m)) + 1);
    unordered_map<ll, ll> baby;
    ll cur = b;
    rep(q, n) {
        if (!baby.count(cur)) baby[cur] = q;
        cur = static_cast<ll>(static_cast<__int128>(cur) * a % m);
    }

    const ll an = mod_pow(a, n, m);
    cur = k;
    for (ll p = 1; p <= n + 1; p++) {
        cur = static_cast<ll>(static_cast<__int128>(cur) * an % m);
        if (baby.count(cur)) {
            const ll ans = p * n - baby[cur] + add;
            if (ans >= 0) return ans;
        }
    }
    return -1;
}
