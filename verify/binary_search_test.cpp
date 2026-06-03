#include "../library/binary_search.hpp"

#include <cassert>

int main() {
    V<int> empty;
    assert(binary_search_index(empty, 1) == -1);
    assert(first_ge(empty, 1) == 0);
    assert(first_gt(empty, 1) == 0);
    assert(last_lt(empty, 1) == -1);
    assert(last_le(empty, 1) == -1);

    V<int> single = {5};
    assert(binary_search_index(single, 5) == 0);
    assert(binary_search_index(single, 4) == -1);
    assert(first_ge(single, 4) == 0);
    assert(first_ge(single, 6) == 1);
    assert(first_gt(single, 5) == 1);
    assert(last_lt(single, 5) == -1);
    assert(last_le(single, 5) == 0);

    V<int> a = {1, 2, 2, 4, 7};

    assert(binary_search_index(a, 1) == 0);
    assert(binary_search_index(a, 2) == 1);
    assert(binary_search_index(a, 3) == -1);
    assert(binary_search_index(a, 7) == 4);

    assert(first_ge(a, 0) == 0);
    assert(first_ge(a, 2) == 1);
    assert(first_ge(a, 3) == 3);
    assert(first_ge(a, 8) == 5);

    assert(first_gt(a, 1) == 1);
    assert(first_gt(a, 2) == 3);
    assert(first_gt(a, 7) == 5);

    assert(last_lt(a, 1) == -1);
    assert(last_lt(a, 2) == 0);
    assert(last_lt(a, 7) == 3);

    assert(last_le(a, 1) == 0);
    assert(last_le(a, 2) == 2);
    assert(last_le(a, 6) == 3);
    assert(last_le(a, 7) == 4);
    assert(last_le(a, 0) == -1);
    assert(last_le(a, 8) == 4);

    V<int> same = {4, 4, 4, 4};
    assert(binary_search_index(same, 4) == 0);
    assert(binary_search_index(same, 5) == -1);
    assert(first_ge(same, 4) == 0);
    assert(first_gt(same, 4) == 4);
    assert(last_lt(same, 4) == -1);
    assert(last_le(same, 4) == 3);

    V<int> negatives = {-10, -3, -3, 0, 8};
    assert(binary_search_index(negatives, -3) == 1);
    assert(first_ge(negatives, -4) == 1);
    assert(first_gt(negatives, -3) == 3);
    assert(last_lt(negatives, 0) == 2);
    assert(last_le(negatives, -10) == 0);

    V<string> words = {"aa", "ab", "ab", "b"};
    assert(binary_search_index(words, string("aa")) == 0);
    assert(binary_search_index(words, string("ab")) == 1);
    assert(binary_search_index(words, string("ac")) == -1);
    assert(first_ge(words, string("ab")) == 1);
    assert(first_gt(words, string("ab")) == 3);
    assert(last_lt(words, string("b")) == 2);
    assert(last_le(words, string("b")) == 3);

    auto ge_30 = [](int x) { return x * x >= 30; };
    assert(binary_search_min(6, 0, ge_30) == 6);
    assert(binary_search_min(5, 4, ge_30) == 5);

    auto ge_minus_3 = [](int x) { return x >= -3; };
    assert(binary_search_min(-3, -10, ge_minus_3) == -3);

    auto le_30 = [](int x) { return x * x <= 30; };
    assert(binary_search_max(5, 10, le_30) == 5);
    assert(binary_search_max(5, 6, le_30) == 5);

    auto le_minus_3 = [](int x) { return x <= -3; };
    assert(binary_search_max(-3, 2, le_minus_3) == -3);

    auto ge_big = [](ll x) { return x >= 1000000000000LL; };
    assert(binary_search_min(1000000000000LL, 0LL, ge_big) == 1000000000000LL);

    auto le_big_neg = [](ll x) { return x <= -1000000000000LL; };
    assert(binary_search_max(-1000000000000LL, 0LL, le_big_neg) == -1000000000000LL);

    return 0;
}
