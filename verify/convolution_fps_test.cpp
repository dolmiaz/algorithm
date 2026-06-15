#include "../library/berlekamp_massey.hpp"
#include "../library/convolution.hpp"
#include "../library/fps.hpp"
#include "../library/linear_recurrence.hpp"

#include <cassert>

int main() {
    using mint = modint998244353;

    V<mint> a{1, 2, 3};
    V<mint> b{4, 5};
    auto c = convolution_ntt(a, b);
    assert(c.size() == 4);
    assert(c[0].val() == 4);
    assert(c[1].val() == 13);
    assert(c[2].val() == 22);
    assert(c[3].val() == 15);

    auto single = convolution_ntt(V<mint>{7}, V<mint>{6});
    assert(single.size() == 1);
    assert(single[0].val() == 42);

    auto cf = convolution_fft(V<ll>{1, 2, 3}, V<ll>{4, 5});
    assert((cf == V<ll>{4, 13, 22, 15}));

    FormalPowerSeries<mint> f{1, 2, 3};
    auto df = f.diff();
    assert(df[0].val() == 2);
    assert(df[1].val() == 6);
    auto intf = df.integral();
    assert(intf[0].val() == 0);
    assert(intf[1].val() == 2);
    assert(intf[2].val() == 3);

    FormalPowerSeries<mint> g{1, 1};
    auto inv = g.inv(5);
    assert(inv.size() == 5);
    assert(inv[0].val() == 1);
    assert(inv[1].val() == mint(-1).val());
    assert(inv[2].val() == 1);
    assert(inv[3].val() == mint(-1).val());
    assert(inv[4].val() == 1);

    V<mint> init{0, 1};
    V<mint> coef{1, 1};
    assert(linear_recurrence_nth(init, coef, 10).val() == 55);

    V<mint> fib_seq{0, 1, 1, 2, 3, 5, 8, 13};
    auto rec = berlekamp_massey(fib_seq);
    assert(rec.size() == 2);
    assert(rec[0].val() == 1);
    assert(rec[1].val() == 1);

    return 0;
}
