#include "../library/fwht.hpp"
#include "../library/modint.hpp"
#include "../library/subset_transform.hpp"

#include <cassert>

int main() {
    V<int> f{1, 2, 3, 4};
    V<int> z = f;
    subset_zeta(z);
    assert((z == V<int>{1, 3, 4, 10}));
    subset_mobius(z);
    assert(z == f);

    V<int> sz = f;
    superset_zeta(sz);
    assert((sz == V<int>{10, 6, 7, 4}));
    superset_mobius(sz);
    assert(sz == f);

    using mint = modint998244353;
    V<mint> a{1, 2, 3, 4};
    V<mint> b{5, 6, 7, 8};

    auto xor_c = convolution_xor(a, b);
    assert((V<int>{xor_c[0].val(), xor_c[1].val(), xor_c[2].val(), xor_c[3].val()} == V<int>{70, 68, 62, 60}));

    auto or_c = convolution_or(a, b);
    assert((V<int>{or_c[0].val(), or_c[1].val(), or_c[2].val(), or_c[3].val()} == V<int>{5, 28, 43, 184}));

    auto and_c = convolution_and(a, b);
    assert((V<int>{and_c[0].val(), and_c[1].val(), and_c[2].val(), and_c[3].val()} == V<int>{103, 52, 73, 32}));

    return 0;
}
