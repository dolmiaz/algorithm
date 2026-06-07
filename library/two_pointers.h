#pragma once

#include "basic.hpp"

template <class T>
long long count_subarrays_sum_at_most_nonnegative(const V<T>& a, long long K) {
    if (K < 0) return 0;

    long long ans = 0;
    long long sum = 0;
    int l = 0;

    for (int r = 0; r < (int)a.size(); r++) {
        sum += a[r];

        while (sum > K) {
            sum -= a[l];
            l++;
        }

        ans += r - l + 1;
    }

    return ans;
}

// a[i] >= 0 を前提に、和がちょうど K の連続部分列の個数を数える
template <class T>
long long count_subarrays_sum_exact_nonnegative(const V<T>& a, long long K) {
    return count_subarrays_sum_at_most_nonnegative(a, K)
         - count_subarrays_sum_at_most_nonnegative(a, K - 1);
}