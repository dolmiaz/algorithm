#include <cassert>

#include "../library/imos.hpp"

int main() {
    Imos1D<int> imos(6);

    assert(imos.n == 6);
    assert(imos.diff.size() == 7);
    assert(!imos.built);

    imos.add(1, 4, 3);
    imos.add(2, 6, -1);
    imos.add_closed(0, 2, 2);
    imos.add(3, 3, 100);

    const V<int> values = imos.build();
    assert((values == V<int>{2, 5, 4, 2, -1, -1}));
    assert(imos.built);

    const V<int> rebuilt = imos.build();
    assert((rebuilt == values));

    Imos1D<ll> big(4);
    big.add(0, 4, 1000000000000LL);
    big.add_closed(1, 2, -3LL);
    big.add(2, 2, 99LL);
    assert((big.build() == V<ll>{1000000000000LL, 999999999997LL, 999999999997LL, 1000000000000LL}));

    Imos1D<int> empty(0);
    assert(empty.diff.size() == 1);
    assert(empty.build().empty());
    assert(empty.built);

    return 0;
}
