#pragma once

#include "basic.hpp"

struct XorBasis {
    static constexpr int LOG = 63;
    array<ull, LOG + 1> basis{};
    int rank_value = 0;

    [[nodiscard]] bool insert(ull x) {
        for (int b = LOG; b >= 0; b--) {
            if (((x >> b) & 1) == 0) continue;
            if (!basis[b]) {
                basis[b] = x;
                rank_value++;
                return true;
            }
            x ^= basis[b];
        }
        return false;
    }

    [[nodiscard]] bool can_make(ull x) const {
        for (int b = LOG; b >= 0; b--) {
            if (((x >> b) & 1) == 0) continue;
            if (!basis[b]) return false;
            x ^= basis[b];
        }
        return true;
    }

    [[nodiscard]] ull max_xor(ull x = 0) const {
        for (int b = LOG; b >= 0; b--) {
            if ((x ^ basis[b]) > x) x ^= basis[b];
        }
        return x;
    }

    [[nodiscard]] int rank() const {
        return rank_value;
    }
};
