#include "../library/cumsum.hpp"

#include <cassert>

int main() {
    PrefixSum1D<int> empty_1d(V<int>{});
    assert(empty_1d.size == 0);
    assert((empty_1d.ps == V<int>{0}));
    assert(empty_1d.sum(0) == 0);
    assert(empty_1d.sum(0, 0) == 0);

    PrefixSum1D<int> one(V<int>{5});
    assert((one.ps == V<int>{0, 5}));
    assert(one.sum(1) == 5);
    assert(one.sum(0, 1) == 5);
    assert(one.sum(1, 1) == 0);

    PrefixSum1D<int> ps(V<int>{1, -2, 3, 4});
    assert((ps.ps == V<int>{0, 1, -1, 2, 6}));
    assert(ps.sum(4) == 6);
    assert(ps.sum(0, 4) == 6);
    assert(ps.sum(1, 3) == 1);
    assert(ps.sum(2, 2) == 0);

    PrefixSum1D<ll> big(V<ll>{1000000000000LL, -3, 5});
    assert((big.ps == V<ll>{0, 1000000000000LL, 999999999997LL, 1000000000002LL}));
    assert(big.sum(1, 3) == 2);

    PrefixSum1D<int> rebuild;
    rebuild.build(V<int>{2, 4});
    assert(rebuild.size == 2);
    assert(rebuild.sum(0, 2) == 6);

    V<V<int>> grid = {
        {1, 2, 3},
        {4, 5, 6},
    };
    PrefixSum2D<int> ps2(grid);
    assert(ps2.H == 2);
    assert(ps2.W == 3);
    assert(ps2.ps.size() == 3);
    assert(ps2.ps[0].size() == 4);
    assert(ps2.sum(0, 0, 2, 3) == 21);
    assert(ps2.sum(0, 1, 2, 3) == 16);
    assert(ps2.sum(1, 1, 2, 3) == 11);
    assert(ps2.sum(0, 0, 1, 3) == 6);
    assert(ps2.sum(0, 2, 2, 3) == 9);
    assert(ps2.sum(0, 1, 1, 2) == 2);
    assert(ps2.sum(1, 2, 1, 2) == 0);

    PrefixSum2D<int> empty_2d(V<V<int>>{});
    assert(empty_2d.H == 0);
    assert(empty_2d.W == 0);
    assert(empty_2d.ps.size() == 1);
    assert(empty_2d.ps[0].size() == 1);
    assert(empty_2d.ps[0][0] == 0);

    PrefixSum2D<int> one_cell(V<V<int>>{{9}});
    assert(one_cell.sum(0, 0, 1, 1) == 9);
    assert(one_cell.sum(0, 0, 0, 1) == 0);
    assert(one_cell.sum(0, 0, 1, 0) == 0);

    PrefixSum2D<int> one_row(V<V<int>>{{1, -1, 2}});
    assert(one_row.sum(0, 0, 1, 3) == 2);
    assert(one_row.sum(0, 1, 1, 2) == -1);

    PrefixSum2D<int> one_col(V<V<int>>{{2}, {-3}, {4}});
    assert(one_col.sum(0, 0, 3, 1) == 3);
    assert(one_col.sum(1, 0, 2, 1) == -3);

    PrefixSum2D<ll> big_grid(V<V<ll>>{
        {1000000000000LL, 2},
        {-5, 7},
    });
    assert(big_grid.sum(0, 0, 2, 2) == 1000000000004LL);
    assert(big_grid.sum(0, 1, 2, 2) == 9);

    PrefixMax1D<int> empty_pm(V<int>{});
    assert(empty_pm.size == 0);
    assert(empty_pm.pref.size() == 1);
    assert(empty_pm.suff.size() == 1);
    assert(empty_pm.prefix_max(0) == numeric_limits<int>::lowest());
    assert(empty_pm.suffix_max(0) == numeric_limits<int>::lowest());

    PrefixMax1D<int> single_pm(V<int>{7});
    assert(single_pm.prefix_max(1) == 7);
    assert(single_pm.suffix_max(0) == 7);
    assert(single_pm.suffix_max(1) == numeric_limits<int>::lowest());

    PrefixMax1D<int> inc_pm(V<int>{1, 2, 3});
    assert((inc_pm.pref == V<int>{numeric_limits<int>::lowest(), 1, 2, 3}));
    assert(inc_pm.suffix_max(0) == 3);
    assert(inc_pm.suffix_max(1) == 3);
    assert(inc_pm.suffix_max(2) == 3);

    PrefixMax1D<int> dec_pm(V<int>{3, 2, 1});
    assert(dec_pm.prefix_max(1) == 3);
    assert(dec_pm.prefix_max(2) == 3);
    assert(dec_pm.prefix_max(3) == 3);
    assert(dec_pm.suffix_max(0) == 3);
    assert(dec_pm.suffix_max(1) == 2);
    assert(dec_pm.suffix_max(2) == 1);

    PrefixMax1D<int> dup_pm(V<int>{2, 2, 2});
    assert(dup_pm.prefix_max(1) == 2);
    assert(dup_pm.prefix_max(2) == 2);
    assert(dup_pm.prefix_max(3) == 2);
    assert(dup_pm.suffix_max(0) == 2);
    assert(dup_pm.suffix_max(1) == 2);
    assert(dup_pm.suffix_max(2) == 2);

    PrefixMax1D<int> neg_pm(V<int>{-5, -1, -3});
    assert(neg_pm.prefix_max(1) == -5);
    assert(neg_pm.prefix_max(2) == -1);
    assert(neg_pm.prefix_max(3) == -1);
    assert(neg_pm.suffix_max(0) == -1);
    assert(neg_pm.suffix_max(1) == -1);
    assert(neg_pm.suffix_max(2) == -3);

    PrefixMax1D<int> pm(V<int>{3, 1, 4, 2});
    assert(pm.pref.size() == 5);
    assert(pm.suff.size() == 5);
    assert(pm.prefix_max(0) == numeric_limits<int>::lowest());
    assert(pm.prefix_max(1) == 3);
    assert(pm.prefix_max(2) == 3);
    assert(pm.prefix_max(3) == 4);
    assert(pm.prefix_max(4) == 4);
    assert(pm.suffix_max(0) == 4);
    assert(pm.suffix_max(1) == 4);
    assert(pm.suffix_max(2) == 4);
    assert(pm.suffix_max(3) == 2);
    assert(pm.suffix_max(4) == numeric_limits<int>::lowest());

    return 0;
}
