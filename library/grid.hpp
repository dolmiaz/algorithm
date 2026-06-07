// Grid direction constants and small helpers for grid traversal.
#pragma once

#include "basic.hpp"

// ============== グリッド方向 ==============
inline constexpr array<int, 4> DR4 = {-1, 0, 1, 0};
inline constexpr array<int, 4> DC4 = {0, 1, 0, -1};
inline constexpr array<char, 4> DIR4 = {'U', 'R', 'D', 'L'};
inline constexpr array<char, 4> dir4 = {'u', 'r', 'd', 'l'};
inline constexpr array<int, 8> DR8 = {-1, -1, 0, 1, 1,  1, 0, -1};
inline constexpr array<int, 8> DC8 = { 0,  1, 1, 1, 0, -1, -1, -1};
inline const array<string, 8> DIR8 = {"U", "UR", "R", "DR", "D", "DL", "L", "UL"};
inline const array<string, 8> dir8 = {"u", "ur", "r", "dr", "d", "dl", "l", "ul"};

inline bool in_grid(const int i, const int j, const int H, const int W) {
    return 0 <= i && i < H && 0 <= j && j < W;
}

struct Grid {
    int H{}, W{};
    V<string> cell;
    V<string> v, h;
    char block = '#';
    char wall = '1';

    Grid() = default;

    Grid(const int H_, const int W_, const char block_ = '#', const char wall_ = '1'):
    H(H_), W(W_),
    cell(H, string(W, '.')),
    v(H, string(max(0, W - 1), '0')),
    h(max(0, H - 1), string(W, '0')),
    block(block_), wall(wall_) {}

    Grid(
        const int H_,
        const int W_,
        const V<string> &v_,
        const V<string> &h_,
        const char block_ = '#',
        const char wall_ = '1'
    ):  H(H_), W(W_),
        cell(H_, string(W_, '.')),
        v(v_),
        h(h_),
        block(block_),
        wall(wall_) {}

    [[nodiscard]] bool in(const int i, const int j) const {
        return in_grid(i, j, H, W);
    }

    [[nodiscard]] int id(const int i, const int j) const {
        return i * W + j;
    }

    [[nodiscard]] pii rc(const int id) const {
        return {id / W, id % W};
    }

    [[nodiscard]] bool is_block(const int i, const int j) const {
        return cell[i][j] == block;
    }

    [[nodiscard]] bool passable(const int i, const int j) const {
        return in(i, j) && !is_block(i, j);
    }

    [[nodiscard]] bool has_wall(const int i, const int j, const int d) const {
        if (d == 0) {
            if (i == 0) return true;
            return h[i - 1][j] == wall;
        }
        if (d == 1) {
            if (j == W - 1) return true;
            return v[i][j] == wall;
        }
        if (d == 2) {
            if (i == H - 1) return true;
            return h[i][j] == wall;
        }
        if (d == 3) {
            if (j == 0) return true;
            return v[i][j - 1] == wall;
        }
        return true;
    }

    [[nodiscard]] bool can_go(const int i, const int j, const int d) const {
        if (d < 0 || 4 <= d) return false;
        if (!in(i, j)) return false;
        if (has_wall(i, j, d)) return false;

        const int ni = i + DR4[d];
        const int nj = j + DC4[d];

        return passable(ni, nj);
    }

    [[nodiscard]] V<pii> neighbors4(const int i, const int j) const {
        V<pii> res;

        rep(d, 4) {
            if (!can_go(i, j, d)) continue;

            const int ni = i + DR4[d];
            const int nj = j + DC4[d];

            res.emplace_back(ni, nj);
        }

        return res;
    }
};

inline Grid read_grid(const int H, const int W, const char block = '#') {
    Grid g(H, W, block);
    rep(i, H) cin >> g.cell[i];

    return g;
}

inline Grid read_grid_with_walls(const int H, const int W, const char wall = '1') {
    Grid g(H, W, '#', wall);

    rep(i, H) cin >> g.v[i];
    rep(i, H - 1) cin >> g.h[i];

    return g;
}
