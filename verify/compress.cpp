#include "../library/compress.hpp"

#include <cassert>

int main() {
    Compress<int> empty;
    assert(empty.size() == 0);
    assert(empty.get(10) == 0);

    Compress<int> c({5, -1, 5, 3, -1, 10});
    assert((c.xs == V<int>{-1, 3, 5, 10}));
    assert(c.size() == 4);
    assert(c.get(-1) == 0);
    assert(c.get(3) == 1);
    assert(c.get(5) == 2);
    assert(c.get(10) == 3);
    assert(c.val(0) == -1);
    assert(c.val(1) == 3);
    assert(c.val(2) == 5);
    assert(c.val(3) == 10);

    assert(c.get(-100) == 0);
    assert(c.get(0) == 1);
    assert(c.get(4) == 2);
    assert(c.get(6) == 3);
    assert(c.get(100) == 4);

    Compress<int> added;
    added.add(4);
    added.add(V<int>{2, 4, 1, 2});
    added.build();
    assert((added.xs == V<int>{1, 2, 4}));
    assert(added.size() == 3);
    assert(added.get(1) == 0);
    assert(added.get(2) == 1);
    assert(added.get(3) == 2);
    assert(added.get(4) == 2);
    assert(added.val(2) == 4);

    added.add(-5);
    added.add(100);
    added.build();
    assert((added.xs == V<int>{-5, 1, 2, 4, 100}));
    assert(added.get(-5) == 0);
    assert(added.get(100) == 4);

    Compress<ll> big({1000000000000LL, -1000000000000LL, 0LL, 1000000000000LL});
    assert((big.xs == V<ll>{-1000000000000LL, 0LL, 1000000000000LL}));
    assert(big.get(-1LL) == 1);
    assert(big.get(1000000000000LL) == 2);
    assert(big.val(2) == 1000000000000LL);

    Compress<string> words({"beta", "alpha", "beta", "gamma"});
    assert((words.xs == V<string>{"alpha", "beta", "gamma"}));
    assert(words.get(string("alpha")) == 0);
    assert(words.get(string("beta")) == 1);
    assert(words.get(string("delta")) == 2);
    assert(words.val(2) == "gamma");

    return 0;
}
