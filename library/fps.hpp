#pragma once

#include "convolution.hpp"

template <class Mint>
struct FormalPowerSeries : V<Mint> {
    using V<Mint>::V;
    using FPS = FormalPowerSeries;

    [[nodiscard]] FPS pre(const int n) const {
        return FPS(this->begin(), this->begin() + min(n, static_cast<int>(this->size())));
    }

    FPS& normalize() {
        while (!this->empty() && this->back() == Mint(0)) this->pop_back();
        return *this;
    }

    [[nodiscard]] FPS diff() const {
        const int n = static_cast<int>(this->size());
        if (n == 0) return {};
        FPS res(max(0, n - 1));
        for (int i = 1; i < n; i++) res[i - 1] = (*this)[i] * i;
        return res;
    }

    [[nodiscard]] FPS integral() const {
        const int n = static_cast<int>(this->size());
        FPS res(n + 1);
        rep(i, n) res[i + 1] = (*this)[i] / Mint(i + 1);
        return res;
    }

    [[nodiscard]] FPS inv(const int deg) const {
        FPS res{(*this)[0].inv()};
        int n = 1;
        while (n < deg) {
            n <<= 1;
            FPS f = pre(n);
            FPS g = res;
            f.resize(n);
            g.resize(n);
            auto fg = convolution_ntt(f, g);
            fg.resize(n);
            rep(i, n) fg[i] = -fg[i];
            fg[0] += 2;
            auto next = convolution_ntt(g, fg);
            res = FPS(next.begin(), next.end());
            res.resize(n);
        }
        res.resize(deg);
        return res;
    }

    [[nodiscard]] friend FPS operator+(FPS a, const FPS& b) {
        if (a.size() < b.size()) a.resize(b.size());
        rep(i, b.size()) a[i] += b[i];
        return a;
    }
    [[nodiscard]] friend FPS operator-(FPS a, const FPS& b) {
        if (a.size() < b.size()) a.resize(b.size());
        rep(i, b.size()) a[i] -= b[i];
        return a;
    }
    [[nodiscard]] friend FPS operator*(const FPS& a, const FPS& b) {
        auto c = convolution_ntt(V<Mint>(a.begin(), a.end()), V<Mint>(b.begin(), b.end()));
        return FPS(c.begin(), c.end());
    }
};
