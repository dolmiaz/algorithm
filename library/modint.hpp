#pragma once

#include "basic.hpp"

template <int MOD>
struct static_modint {
    using mint = static_modint;
    int v = 0;

    [[nodiscard]] static constexpr int mod() { return MOD; }

    static_modint() = default;
    template <class T> static_modint(T x) {
        ll y = static_cast<ll>(x % static_cast<T>(MOD));
        if (y < 0) y += MOD;
        v = static_cast<int>(y);
    }

    [[nodiscard]] int val() const { return v; }

    mint& operator+=(const mint& rhs) {
        v += rhs.v;
        if (v >= MOD) v -= MOD;
        return *this;
    }
    mint& operator-=(const mint& rhs) {
        v -= rhs.v;
        if (v < 0) v += MOD;
        return *this;
    }
    mint& operator*=(const mint& rhs) {
        v = static_cast<int>(static_cast<ll>(v) * rhs.v % MOD);
        return *this;
    }
    mint& operator/=(const mint& rhs) { return *this *= rhs.inv(); }

    [[nodiscard]] mint operator+() const { return *this; }
    [[nodiscard]] mint operator-() const { return mint(0) - *this; }

    [[nodiscard]] friend mint operator+(mint lhs, const mint& rhs) { return lhs += rhs; }
    [[nodiscard]] friend mint operator-(mint lhs, const mint& rhs) { return lhs -= rhs; }
    [[nodiscard]] friend mint operator*(mint lhs, const mint& rhs) { return lhs *= rhs; }
    [[nodiscard]] friend mint operator/(mint lhs, const mint& rhs) { return lhs /= rhs; }
    [[nodiscard]] friend bool operator==(const mint& lhs, const mint& rhs) { return lhs.v == rhs.v; }
    [[nodiscard]] friend bool operator!=(const mint& lhs, const mint& rhs) { return !(lhs == rhs); }

    [[nodiscard]] mint pow(ll n) const {
        mint res = 1, x = *this;
        while (n > 0) {
            if (n & 1) res *= x;
            x *= x;
            n >>= 1;
        }
        return res;
    }

    [[nodiscard]] mint inv() const {
        ll a = v, b = MOD, x = 1, y = 0;
        while (b) {
            const ll q = a / b;
            a -= q * b;
            swap(a, b);
            x -= q * y;
            swap(x, y);
        }
        if (x < 0) x += MOD;
        return mint(x);
    }

    friend ostream& operator<<(ostream& os, const mint& x) { return os << x.v; }
    friend istream& operator>>(istream& is, mint& x) {
        ll input_value;
        is >> input_value;
        x = mint(input_value);
        return is;
    }
};

template <int ID>
struct dynamic_modint {
    using mint = dynamic_modint;
    static int& mod_ref() {
        static int m = 998244353;
        return m;
    }
    int v = 0;

    [[nodiscard]] static int mod() { return mod_ref(); }
    static void set_mod(const int m) { mod_ref() = m; }

    dynamic_modint() = default;
    template <class T> dynamic_modint(T x) {
        const int m = mod();
        ll y = static_cast<ll>(x % static_cast<T>(m));
        if (y < 0) y += m;
        v = static_cast<int>(y);
    }

    [[nodiscard]] int val() const { return v; }

    mint& operator+=(const mint& rhs) {
        v += rhs.v;
        if (v >= mod()) v -= mod();
        return *this;
    }
    mint& operator-=(const mint& rhs) {
        v -= rhs.v;
        if (v < 0) v += mod();
        return *this;
    }
    mint& operator*=(const mint& rhs) {
        v = static_cast<int>(static_cast<ll>(v) * rhs.v % mod());
        return *this;
    }
    mint& operator/=(const mint& rhs) { return *this *= rhs.inv(); }

    [[nodiscard]] mint operator+() const { return *this; }
    [[nodiscard]] mint operator-() const { return mint(0) - *this; }

    [[nodiscard]] friend mint operator+(mint lhs, const mint& rhs) { return lhs += rhs; }
    [[nodiscard]] friend mint operator-(mint lhs, const mint& rhs) { return lhs -= rhs; }
    [[nodiscard]] friend mint operator*(mint lhs, const mint& rhs) { return lhs *= rhs; }
    [[nodiscard]] friend mint operator/(mint lhs, const mint& rhs) { return lhs /= rhs; }
    [[nodiscard]] friend bool operator==(const mint& lhs, const mint& rhs) { return lhs.v == rhs.v; }
    [[nodiscard]] friend bool operator!=(const mint& lhs, const mint& rhs) { return !(lhs == rhs); }

    [[nodiscard]] mint pow(ll n) const {
        mint res = 1, x = *this;
        while (n > 0) {
            if (n & 1) res *= x;
            x *= x;
            n >>= 1;
        }
        return res;
    }

    [[nodiscard]] mint inv() const {
        ll a = v, b = mod(), x = 1, y = 0;
        while (b) {
            const ll q = a / b;
            a -= q * b;
            swap(a, b);
            x -= q * y;
            swap(x, y);
        }
        if (x < 0) x += mod();
        return mint(x);
    }

    friend ostream& operator<<(ostream& os, const mint& x) { return os << x.v; }
    friend istream& operator>>(istream& is, mint& x) {
        ll input_value;
        is >> input_value;
        x = mint(input_value);
        return is;
    }
};

using modint998244353 = static_modint<998244353>;
using modint1000000007 = static_modint<1000000007>;
