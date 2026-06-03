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

inline bool in_grid(const int r, const int c, const int h, const int w) {
    return 0 <= r && r < h && 0 <= c && c < w;
}
