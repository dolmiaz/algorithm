#pragma once

#include "number_theory.hpp"

[[nodiscard]] inline pair<ll, ll> crt_pair(ll r1, ll m1, ll r2, ll m2) {
    if (m1 < 0) m1 = -m1;
    if (m2 < 0) m2 = -m2;
    r1 %= m1;
    if (r1 < 0) r1 += m1;
    r2 %= m2;
    if (r2 < 0) r2 += m2;

    ll x, y;
    const ll g = ext_gcd(m1, m2, x, y);
    if ((r2 - r1) % g != 0) return {0, 0};

    const ll u = m2 / g;
    ll t = static_cast<ll>(static_cast<__int128>((r2 - r1) / g) * x % u);
    if (t < 0) t += u;

    const ll lcm = m1 * u;
    ll r = static_cast<ll>((r1 + static_cast<__int128>(m1) * t) % lcm);
    if (r < 0) r += lcm;
    return {r, lcm};
}

[[nodiscard]] inline pair<ll, ll> crt(const V<ll>& r, const V<ll>& m) {
    ll r0 = 0, m0 = 1;
    rep(i, r.size()) {
        auto merged = crt_pair(r0, m0, r[i], m[i]);
        if (merged.second == 0) return {0, 0};
        r0 = merged.first;
        m0 = merged.second;
    }
    return {r0, m0};
}
