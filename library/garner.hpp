#pragma once

#include "number_theory.hpp"

[[nodiscard]] inline ll garner(const V<ll>& r, const V<ll>& m, const ll mod) {
    const int n = static_cast<int>(r.size());
    V<ll> coeff(n + 1, 1), constants(n + 1, 0), mods = m;
    mods.push_back(mod);

    rep(i, n) {
        ll t = (r[i] - constants[i]) % mods[i];
        if (t < 0) t += mods[i];
        t = static_cast<ll>(static_cast<__int128>(t) * mod_inv(coeff[i], mods[i]) % mods[i]);

        for (int j = i + 1; j <= n; j++) {
            constants[j] = (constants[j] + static_cast<__int128>(coeff[j]) * t) % mods[j];
            coeff[j] = static_cast<ll>(static_cast<__int128>(coeff[j]) * mods[i] % mods[j]);
        }
    }

    return constants[n];
}
