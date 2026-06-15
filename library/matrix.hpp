#pragma once

#include "basic.hpp"

template <class T>
using Matrix = V<V<T>>;

template <class T>
[[nodiscard]] Matrix<T> identity_matrix(const int n) {
    Matrix<T> res(n, V<T>(n, T(0)));
    rep(i, n) res[i][i] = T(1);
    return res;
}

template <class T>
[[nodiscard]] Matrix<T> matrix_mul(const Matrix<T>& a, const Matrix<T>& b) {
    const int n = static_cast<int>(a.size());
    const int m = static_cast<int>(b[0].size());
    const int p = static_cast<int>(b.size());
    Matrix<T> res(n, V<T>(m, T(0)));

    rep(i, n) {
        rep(k, p) {
            if (a[i][k] == T(0)) continue;
            rep(j, m) {
                res[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    return res;
}

template <class T>
[[nodiscard]] Matrix<T> matrix_pow(Matrix<T> a, ull e) {
    Matrix<T> res = identity_matrix<T>(static_cast<int>(a.size()));
    while (e > 0) {
        if (e & 1) res = matrix_mul(res, a);
        a = matrix_mul(a, a);
        e >>= 1;
    }
    return res;
}
