#pragma once

#include "basic.hpp"

template <class T>
struct Fenwick {
    V<T> bit;
    int n;

    Fenwick() : n(0) {}

    explicit Fenwick(const int n_) {
        init(n_);
    }

    void init(const int n_) {
        n = n_;
        bit.assign(n + 1, T(0));
    }

private:
    static int low_bit(const int idx) {
        return idx & -idx;
    }

public:
    void add(int idx, const T x) {
        idx++;
        while (idx <= n) {
            bit[idx] += x;
            idx += low_bit(idx);
        }
    }

    T sum(int r) const {
        T res = T(0);
        while (r > 0) {
            res += bit[r];
            r -= low_bit(r);
        }
        return res;
    }

    T sum(const int l, const int r) const {
        return sum(r) - sum(l);
    }

    T get(const int idx) const {
        return sum(idx, idx + 1);
    }

    void set(int idx, const T x) {
        add(idx, x - get(idx));
    }

    int lower_bound(T w) const {
        if (w <= T(0)) return 0;

        int idx = 0;

        int k = 1;
        while ((k << 1) <= n) k <<= 1;

        for (; k > 0; k >>= 1) {
            const int next = idx + k;

            if (next <= n && bit[next] < w) {
                idx = next;
                w -= bit[next];
            }
        }

        return idx;
    }
};
