#include "../library/cumsum.hpp"

#include <cassert>

int main() {
    V<int> empty_1d;
    auto empty_ps1 = prefix_sum_1d(empty_1d);
    assert((empty_ps1 == V<int>{0}));
    assert(range_sum_1d(empty_ps1, 0, 0) == 0);

    V<int> one = {5};
    auto one_ps = prefix_sum_1d(one);
    assert((one_ps == V<int>{0, 5}));
    assert(range_sum_1d(one_ps, 0, 1) == 5);
    assert(range_sum_1d(one_ps, 1, 1) == 0);

    V<int> a = {1, -2, 3, 4};
    auto ps = prefix_sum_1d(a);
    assert((ps == V<int>{0, 1, -1, 2, 6}));
    assert(range_sum_1d(ps, 0, 4) == 6);
    assert(range_sum_1d(ps, 1, 3) == 1);
    assert(range_sum_1d(ps, 2, 2) == 0);

    V<ll> big = {1000000000000LL, -3, 5};
    auto big_ps = prefix_sum_1d(big);
    assert((big_ps == V<ll>{0, 1000000000000LL, 999999999997LL, 1000000000002LL}));
    assert(range_sum_1d(big_ps, 1, 3) == 2);

    V<V<int>> grid = {
        {1, 2, 3},
        {4, 5, 6},
    };
    auto ps2 = prefix_sum_2d(grid);
    assert(ps2.size() == 3);
    assert(ps2[0].size() == 4);
    assert(range_sum_2d(ps2, 0, 0, 2, 3) == 21);
    assert(range_sum_2d(ps2, 0, 1, 2, 3) == 16);
    assert(range_sum_2d(ps2, 1, 1, 2, 3) == 11);
    assert(range_sum_2d(ps2, 0, 0, 1, 3) == 6);
    assert(range_sum_2d(ps2, 0, 2, 2, 3) == 9);
    assert(range_sum_2d(ps2, 0, 1, 1, 2) == 2);
    assert(range_sum_2d(ps2, 1, 2, 1, 2) == 0);

    V<V<int>> empty;
    auto empty_ps = prefix_sum_2d(empty);
    assert(empty_ps.size() == 1);
    assert(empty_ps[0].size() == 1);
    assert(empty_ps[0][0] == 0);

    V<V<int>> one_cell = {{9}};
    auto one_cell_ps = prefix_sum_2d(one_cell);
    assert(range_sum_2d(one_cell_ps, 0, 0, 1, 1) == 9);
    assert(range_sum_2d(one_cell_ps, 0, 0, 0, 1) == 0);
    assert(range_sum_2d(one_cell_ps, 0, 0, 1, 0) == 0);

    V<V<int>> one_row = {{1, -1, 2}};
    auto one_row_ps = prefix_sum_2d(one_row);
    assert(range_sum_2d(one_row_ps, 0, 0, 1, 3) == 2);
    assert(range_sum_2d(one_row_ps, 0, 1, 1, 2) == -1);

    V<V<int>> one_col = {{2}, {-3}, {4}};
    auto one_col_ps = prefix_sum_2d(one_col);
    assert(range_sum_2d(one_col_ps, 0, 0, 3, 1) == 3);
    assert(range_sum_2d(one_col_ps, 1, 0, 2, 1) == -3);

    V<V<ll>> big_grid = {
        {1000000000000LL, 2},
        {-5, 7},
    };
    auto big_grid_ps = prefix_sum_2d(big_grid);
    assert(range_sum_2d(big_grid_ps, 0, 0, 2, 2) == 1000000000004LL);
    assert(range_sum_2d(big_grid_ps, 0, 1, 2, 2) == 9);

    auto empty_pm = prefix_max_1d(V<int>{});
    assert(empty_pm.L.size() == 2);
    assert(empty_pm.R.size() == 2);
    assert(empty_pm.L[0] == numeric_limits<int>::lowest());
    assert(empty_pm.R[1] == numeric_limits<int>::lowest());

    auto single_pm = prefix_max_1d(V<int>{7});
    assert(single_pm.L[1] == 7);
    assert(single_pm.R[1] == 7);

    auto inc_pm = prefix_max_1d(V<int>{1, 2, 3});
    assert((inc_pm.L == V<int>{numeric_limits<int>::lowest(), 1, 2, 3, numeric_limits<int>::lowest()}));
    assert(inc_pm.R[1] == 3);
    assert(inc_pm.R[2] == 3);
    assert(inc_pm.R[3] == 3);

    auto dec_pm = prefix_max_1d(V<int>{3, 2, 1});
    assert(dec_pm.L[1] == 3);
    assert(dec_pm.L[2] == 3);
    assert(dec_pm.L[3] == 3);
    assert(dec_pm.R[1] == 3);
    assert(dec_pm.R[2] == 2);
    assert(dec_pm.R[3] == 1);

    auto dup_pm = prefix_max_1d(V<int>{2, 2, 2});
    assert(dup_pm.L[1] == 2);
    assert(dup_pm.L[2] == 2);
    assert(dup_pm.L[3] == 2);
    assert(dup_pm.R[1] == 2);
    assert(dup_pm.R[2] == 2);
    assert(dup_pm.R[3] == 2);

    auto neg_pm = prefix_max_1d(V<int>{-5, -1, -3});
    assert(neg_pm.L[1] == -5);
    assert(neg_pm.L[2] == -1);
    assert(neg_pm.L[3] == -1);
    assert(neg_pm.R[1] == -1);
    assert(neg_pm.R[2] == -1);
    assert(neg_pm.R[3] == -3);

    auto pm = prefix_max_1d(V<int>{3, 1, 4, 2});
    assert(pm.L.size() == 6);
    assert(pm.R.size() == 6);
    assert(pm.L[0] == numeric_limits<int>::lowest());
    assert(pm.L[1] == 3);
    assert(pm.L[2] == 3);
    assert(pm.L[3] == 4);
    assert(pm.L[4] == 4);
    assert(pm.R[1] == 4);
    assert(pm.R[2] == 4);
    assert(pm.R[3] == 4);
    assert(pm.R[4] == 2);
    assert(pm.R[5] == numeric_limits<int>::lowest());

    return 0;
}
