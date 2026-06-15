#pragma once

#include "basic.hpp"
#include "matrix.hpp"

template <class T>
[[nodiscard]] int gaussian_elimination(V<V<T>>& a, const int variables = -1) {
    const int h = static_cast<int>(a.size());
    if (h == 0) return 0;
    const int w = static_cast<int>(a[0].size());
    const int vars = variables == -1 ? w : variables;

    int rank = 0;
    rep(col, vars) {
        int pivot = -1;
        for (int row = rank; row < h; row++) {
            if (a[row][col] != T(0)) {
                pivot = row;
                break;
            }
        }
        if (pivot == -1) continue;

        swap(a[rank], a[pivot]);
        const T inv = T(1) / a[rank][col];
        for (int col2 = col; col2 < w; col2++) a[rank][col2] *= inv;

        rep(row, h) {
            if (row == rank || a[row][col] == T(0)) continue;
            const T factor = a[row][col];
            for (int col2 = col; col2 < w; col2++) {
                a[row][col2] -= factor * a[rank][col2];
            }
        }

        rank++;
    }

    return rank;
}

template <class T>
[[nodiscard]] int matrix_rank(Matrix<T> a) {
    return gaussian_elimination(a);
}

template <class T>
[[nodiscard]] pair<bool, V<T>> solve_linear_system(Matrix<T> a, V<T> b) {
    const int n = static_cast<int>(a.size());
    const int m = n == 0 ? 0 : static_cast<int>(a[0].size());
    rep(i, n) a[i].push_back(b[i]);

    const int rank = gaussian_elimination(a, m);
    for (int row = rank; row < n; row++) {
        if (a[row][m] != T(0)) return {false, {}};
    }

    V<T> x(m, T(0));
    rep(row, rank) {
        int pivot = -1;
        rep(col, m) {
            if (a[row][col] == T(1)) {
                pivot = col;
                break;
            }
        }
        if (pivot != -1) x[pivot] = a[row][m];
    }

    return {true, x};
}
