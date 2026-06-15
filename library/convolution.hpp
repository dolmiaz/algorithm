#pragma once

#include "modint.hpp"
#include "primitive_root.hpp"

#include <complex>

template <class Mint>
void ntt(V<Mint>& a, const bool invert) {
    const int n = static_cast<int>(a.size());
    if (n <= 1) return;
    static V<int> rev;
    static V<Mint> roots{0, 1};

    if (static_cast<int>(rev.size()) != n) {
        const int k = __builtin_ctz(n);
        rev.assign(n, 0);
        rep(i, n) {
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
        }
    }

    if (static_cast<int>(roots.size()) < n) {
        int k = __builtin_ctz(static_cast<int>(roots.size()));
        roots.resize(n);
        while ((1 << k) < n) {
            Mint e = Mint(primitive_root(Mint::mod())).pow((Mint::mod() - 1) >> (k + 1));
            for (int i = 1 << (k - 1); i < (1 << k); i++) {
                roots[2 * i] = roots[i];
                roots[2 * i + 1] = roots[i] * e;
            }
            k++;
        }
    }

    rep(i, n) {
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    }

    for (int len = 1; len < n; len <<= 1) {
        for (int i = 0; i < n; i += 2 * len) {
            rep(j, len) {
                Mint u = a[i + j];
                Mint v = a[i + j + len] * roots[len + j];
                a[i + j] = u + v;
                a[i + j + len] = u - v;
            }
        }
    }

    if (invert) {
        reverse(a.begin() + 1, a.end());
        const Mint inv_n = Mint(n).inv();
        for (auto& x : a) x *= inv_n;
    }
}

template <class Mint>
[[nodiscard]] V<Mint> convolution_ntt(V<Mint> a, V<Mint> b) {
    if (a.empty() || b.empty()) return {};
    const int need = static_cast<int>(a.size() + b.size() - 1);
    int n = 1;
    while (n < need) n <<= 1;
    a.resize(n);
    b.resize(n);
    ntt(a, false);
    ntt(b, false);
    rep(i, n) a[i] *= b[i];
    ntt(a, true);
    a.resize(need);
    return a;
}

[[nodiscard]] inline V<ll> convolution_fft(const V<ll>& a, const V<ll>& b) {
    if (a.empty() || b.empty()) return {};
    using cd = complex<double>;
    const double PI_D = acos(-1.0);
    const int need = static_cast<int>(a.size() + b.size() - 1);
    int n = 1;
    while (n < need) n <<= 1;

    V<cd> fa(n), fb(n);
    rep(i, a.size()) fa[i] = static_cast<double>(a[i]);
    rep(i, b.size()) fb[i] = static_cast<double>(b[i]);

    const auto fft = [&](V<cd>& f, const bool invert) {
        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            for (; j & bit; bit >>= 1) j ^= bit;
            j ^= bit;
            if (i < j) swap(f[i], f[j]);
        }
        for (int len = 2; len <= n; len <<= 1) {
            const double ang = 2 * PI_D / len * (invert ? -1 : 1);
            const cd wlen(cos(ang), sin(ang));
            for (int i = 0; i < n; i += len) {
                cd w = 1;
                for (int j = 0; j < len / 2; j++) {
                    cd u = f[i + j], v = f[i + j + len / 2] * w;
                    f[i + j] = u + v;
                    f[i + j + len / 2] = u - v;
                    w *= wlen;
                }
            }
        }
        if (invert) {
            for (auto& x : f) x /= n;
        }
    };

    fft(fa, false);
    fft(fb, false);
    rep(i, n) fa[i] *= fb[i];
    fft(fa, true);

    V<ll> res(need);
    rep(i, need) res[i] = llround(fa[i].real());
    return res;
}
