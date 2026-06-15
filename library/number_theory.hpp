#pragma once

#include "basic.hpp"
#include "math.hpp"

[[nodiscard]] inline ll ext_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = (a >= 0 ? 1 : -1);
        y = 0;
        return abs(a);
    }
    ll x1, y1;
    const ll g = ext_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

[[nodiscard]] inline ll mod_inv(ll a, const ll mod) {
    ll x, y;
    const ll g = ext_gcd(a, mod, x, y);
    if (g != 1) return -1;
    x %= mod;
    if (x < 0) x += mod;
    return x;
}

[[nodiscard]] inline V<ll> divisors(ll n) {
    V<ll> res;
    for (ll d = 1; d * d <= n; d++) {
        if (n % d != 0) continue;
        res.push_back(d);
        if (d * d != n) res.push_back(n / d);
    }
    sort(all(res));
    return res;
}

[[nodiscard]] inline V<pair<ll, int>> factorize(ll n) {
    V<pair<ll, int>> res;
    for (ll p = 2; p * p <= n; p += (p == 2 ? 1 : 2)) {
        if (n % p != 0) continue;
        int e = 0;
        while (n % p == 0) {
            n /= p;
            e++;
        }
        res.emplace_back(p, e);
    }
    if (n > 1) res.emplace_back(n, 1);
    return res;
}

[[nodiscard]] inline ll euler_phi(ll n) {
    ll res = n;
    for (const auto &[p, _] : factorize(n)) {
        res = res / p * (p - 1);
    }
    return res;
}

[[nodiscard]] inline V<int> sieve_primes(const int n) {
    V<int> primes;
    V<int> is_prime(n + 1, 1);
    if (n >= 0) is_prime[0] = 0;
    if (n >= 1) is_prime[1] = 0;
    for (int i = 2; i <= n; i++) {
        if (!is_prime[i]) continue;
        primes.push_back(i);
        if (static_cast<ll>(i) * i <= n) {
            for (ll j = static_cast<ll>(i) * i; j <= n; j += i) is_prime[j] = 0;
        }
    }
    return primes;
}
