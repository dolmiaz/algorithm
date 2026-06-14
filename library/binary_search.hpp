// Binary search helpers for sorted containers and monotone predicates.
#pragma once

#include "basic.hpp"

// ============== 二分探索 ==============
template <class T>
struct BinarySearch {
    V<T> a;

    BinarySearch() = default;

    explicit BinarySearch(const V<T> &sorted_vec) {
        build(sorted_vec);
    }

    void build(const V<T> &sorted_vec) {
        a = sorted_vec;
    }

    int index(const T &x) const {
        const int pos = lower_bound(all(a), x) - a.begin();
        if (pos < static_cast<int>(a.size()) && a[pos] == x) return pos;
        return -1;
    }

    int first_ge(const T &x) const {
        return lower_bound(all(a), x) - a.begin();
    }

    int first_gt(const T &x) const {
        return upper_bound(all(a), x) - a.begin();
    }

    int last_lt(const T &x) const {
        return first_ge(x) - 1;
    }

    int last_le(const T &x) const {
        return first_gt(x) - 1;
    }

    template <class U, class F>
    static U min_true(U ok, U ng, F pred) {
        while (abs(ok - ng) > 1) {
            U mid = ng + (ok - ng) / 2;
            if (pred(mid)) ok = mid;
            else ng = mid;
        }
        return ok;
    }

    template <class U, class F>
    static U max_true(U ok, U ng, F pred) {
        while (abs(ng - ok) > 1) {
            U mid = ok + (ng - ok) / 2;
            if (pred(mid)) ok = mid;
            else ng = mid;
        }
        return ok;
    }
};
