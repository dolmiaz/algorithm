#pragma once

#include "basic.hpp"

// 外部 index: 0-indexed
// 内部 index: 1-indexed
// bit[i] は a[i - low_bit(i), i) の和を持つ
// sum(r) は a[0] + ... + a[r - 1] を返す
template <class T>
struct Fenwick {
    V<T> bit;
    int size;

    Fenwick() : size(0) {
    }

    explicit Fenwick(const int size_) {
        init(size_);
    }

    void init(const int size_) {
        size = size_;
        bit.assign(size + 1, T(0));
    }

private:
    static int to_internal(const int idx) {
        return idx + 1;
    }

    static int low_bit(const int idx) {
        return idx & -idx;
    }

public:
    void add(int idx, const T x) {
        idx++;
        while (idx <= size) {
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

    void set(const int i, const T x) {
        add(i, x - get(i));
    }

    void push(const T x) {
        const int old_size = size;

        if (bit.empty()) bit.push_back(T(0));

        ++size;
        bit.push_back(T(0));

        const int i = size;
        bit[i] = x + sum(i - low_bit(i), old_size);
    }

    int lower_bound(T w) const {
        if (w <= T(0)) return 0;

        int idx = 0;

        int k = 1;
        while ((k << 1) <= size) k <<= 1;

        for (; k > 0; k >>= 1) {
            const int next = idx + k;

            if (next <= size && bit[next] < w) {
                idx = next;
                w -= bit[next];
            }
        }

        return idx;
    }
};

template <class T>
struct RangeFenwick {
    int size{};
    Fenwick<T> bit0;
    Fenwick<T> bit1;

    RangeFenwick() : size(0) {
    }

    explicit RangeFenwick(const int size_) {
        init(size_);
    }

    void init(const int size_) {
        size = size_;
        bit0.init(size);
        bit1.init(size);
    }

private:
    void add_bit(Fenwick<T>& bit, const int idx, const T x) {
        if (idx < size) bit.add(idx, x);
    }

public:
    void add(const int l, const int r, const T x) {
        if (l >= r) return;

        add_bit(bit0, l, x);
        add_bit(bit0, r, -x);

        add_bit(bit1, l, x * T(l));
        add_bit(bit1, r, -x * T(r));
    }

    T sum(const int r) const {
        return bit0.sum(r) * T(r) - bit1.sum(r);
    }

    T sum(const int l, const int r) const {
        return sum(r) - sum(l);
    }

    T get(const int idx) const {
        return sum(idx, idx + 1);
    }

    void set(const int idx, const T x) {
        add(idx, idx + 1, x - get(idx));
    }
};
