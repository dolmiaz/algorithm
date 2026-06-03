// Binary search helpers for sorted containers and monotone predicates.
#pragma once

#include "basic.hpp"

// ============== 二分探索 ==============
// return -> 0-indexed
template <class T, class F> int binary_search_index(const V<F> &vec, T x) {
    int pos = lower_bound(all(vec), x) - vec.begin();
    if (pos < static_cast<int>(vec.size()) && vec[pos] == x) return pos;
    return -1;
}
template <class T>
int first_ge(const V<T>& a, T x) {
    return lower_bound(all(a), x) - a.begin();
}
template <class T>
int first_gt(const V<T>& a, T x) {
    return upper_bound(all(a), x) - a.begin();
}
template <class T>
int last_lt(const V<T>& a, T x) {
    int p = lower_bound(all(a), x) - a.begin();
    return p - 1;
}
template <class T>
int last_le(const V<T>& a, T x) {
    int p = upper_bound(all(a), x) - a.begin();
    return p - 1;
}
template <class T, class F> T binary_search_min(T ok, T ng, F pred) {
    while (abs(ok - ng) > 1) {
        T mid = ng + (ok - ng) / 2;
        if (pred(mid)) ok = mid;
        else ng = mid;
    }
    return ok;
}
template <class T, class F> T binary_search_max(T ok, T ng, F pred) {
    while (abs(ng - ok) > 1) {
        T mid = ok + (ng - ok) / 2;
        if (pred(mid)) ok = mid;
        else ng = mid;
    }
    return ok;
}
