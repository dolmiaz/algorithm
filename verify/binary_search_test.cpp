#include "../library/binary_search.hpp"

#include <cassert>

int main() {
    BinarySearch<int> empty(V<int>{});
    assert(empty.index(1) == -1);
    assert(empty.first_ge(1) == 0);
    assert(empty.first_gt(1) == 0);
    assert(empty.last_lt(1) == -1);
    assert(empty.last_le(1) == -1);

    BinarySearch<int> single(V<int>{5});
    assert(single.index(5) == 0);
    assert(single.index(4) == -1);
    assert(single.first_ge(4) == 0);
    assert(single.first_ge(6) == 1);
    assert(single.first_gt(5) == 1);
    assert(single.last_lt(5) == -1);
    assert(single.last_le(5) == 0);

    BinarySearch<int> bs(V<int>{1, 2, 2, 4, 7});
    assert(bs.index(1) == 0);
    assert(bs.index(2) == 1);
    assert(bs.index(3) == -1);
    assert(bs.index(7) == 4);
    assert(bs.first_ge(0) == 0);
    assert(bs.first_ge(2) == 1);
    assert(bs.first_ge(3) == 3);
    assert(bs.first_ge(8) == 5);
    assert(bs.first_gt(1) == 1);
    assert(bs.first_gt(2) == 3);
    assert(bs.first_gt(7) == 5);
    assert(bs.last_lt(1) == -1);
    assert(bs.last_lt(2) == 0);
    assert(bs.last_lt(7) == 3);
    assert(bs.last_le(1) == 0);
    assert(bs.last_le(2) == 2);
    assert(bs.last_le(6) == 3);
    assert(bs.last_le(7) == 4);
    assert(bs.last_le(0) == -1);
    assert(bs.last_le(8) == 4);

    BinarySearch<int> same(V<int>{4, 4, 4, 4});
    assert(same.index(4) == 0);
    assert(same.index(5) == -1);
    assert(same.first_ge(4) == 0);
    assert(same.first_gt(4) == 4);
    assert(same.last_lt(4) == -1);
    assert(same.last_le(4) == 3);

    BinarySearch<int> negatives(V<int>{-10, -3, -3, 0, 8});
    assert(negatives.index(-3) == 1);
    assert(negatives.first_ge(-4) == 1);
    assert(negatives.first_gt(-3) == 3);
    assert(negatives.last_lt(0) == 2);
    assert(negatives.last_le(-10) == 0);

    BinarySearch<string> words(V<string>{"aa", "ab", "ab", "b"});
    assert(words.index("aa") == 0);
    assert(words.index("ab") == 1);
    assert(words.index("ac") == -1);
    assert(words.first_ge("ab") == 1);
    assert(words.first_gt("ab") == 3);
    assert(words.last_lt("b") == 2);
    assert(words.last_le("b") == 3);

    BinarySearch<int> rebuild;
    rebuild.build(V<int>{2, 5});
    assert(rebuild.index(5) == 1);

    auto ge_30 = [](int x) { return x * x >= 30; };
    assert(BinarySearch<int>::min_true(6, 0, ge_30) == 6);
    assert(BinarySearch<int>::min_true(5, 4, ge_30) == 5);

    auto ge_minus_3 = [](int x) { return x >= -3; };
    assert(BinarySearch<int>::min_true(-3, -10, ge_minus_3) == -3);

    auto le_30 = [](int x) { return x * x <= 30; };
    assert(BinarySearch<int>::max_true(5, 10, le_30) == 5);
    assert(BinarySearch<int>::max_true(5, 6, le_30) == 5);

    auto le_minus_3 = [](int x) { return x <= -3; };
    assert(BinarySearch<int>::max_true(-3, 2, le_minus_3) == -3);

    auto ge_big = [](ll x) { return x >= 1000000000000LL; };
    assert(BinarySearch<ll>::min_true(1000000000000LL, 0LL, ge_big) == 1000000000000LL);

    auto le_big_neg = [](ll x) { return x <= -1000000000000LL; };
    assert(BinarySearch<ll>::max_true(-1000000000000LL, 0LL, le_big_neg) == -1000000000000LL);

    return 0;
}
