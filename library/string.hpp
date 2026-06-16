#pragma once

#include "basic.hpp"

template <class T>
bool is_palindrome(const T& s) {
    int n = static_cast<int>(s.size());
    rep(i, n / 2) {
        if (s[i] != s[n - 1 - i]) return false;
    }
    return true;
}
