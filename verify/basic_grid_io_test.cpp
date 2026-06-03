#include "../library/grid.hpp"
#include "../library/io.hpp"

#include <cassert>
#include <sstream>

int main() {
    static_assert(is_same_v<ll, long long>);
    static_assert(is_same_v<ull, unsigned long long>);
    static_assert(is_same_v<ld, long double>);
    static_assert(is_same_v<V<int>, vector<int>>);
    static_assert(is_same_v<pii, pair<int, int>>);
    static_assert(is_same_v<pll, pair<ll, ll>>);

    assert(INF == (1 << 30) - 1);
    assert(INF_L == (1LL << 60));
    assert(ABC == "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    assert(abc == "abcdefghijklmnopqrstuvwxyz");
    assert(modNum == 998244353);
    assert(PI > 3.14159L && PI < 3.14160L);

    V<int> v = {1, 2, 3, 4};
    int sum = 0;
    rep(i, v.size()) sum += v[i];
    assert(sum == 10);

    int zero_rep_count = 0;
    rep(i, 0) zero_rep_count += i;
    assert(zero_rep_count == 0);

    int one_rep_count = 0;
    rep(i, 1) one_rep_count += i + 1;
    assert(one_rep_count == 1);

    int one_based_sum = 0;
    rep1(i, 4) one_based_sum += i;
    assert(one_based_sum == 10);

    int zero_rep1_count = 0;
    rep1(i, 0) zero_rep1_count += i;
    assert(zero_rep1_count == 0);

    V<int> rev;
    rrep(i, 4) rev.push_back(i);
    assert((rev == V<int>{3, 2, 1, 0}));

    V<int> rev1;
    rrep1(i, 4) rev1.push_back(i);
    assert((rev1 == V<int>{4, 3, 2, 1}));

    V<int> empty_rev;
    rrep(i, 0) empty_rev.push_back(i);
    assert(empty_rev.empty());

    V<int> empty_rev1;
    rrep1(i, 0) empty_rev1.push_back(i);
    assert(empty_rev1.empty());

    V<int> single_rev;
    rrep(i, 1) single_rev.push_back(i);
    assert((single_rev == V<int>{0}));

    sort(rall(v));
    assert((v == V<int>{4, 3, 2, 1}));
    sort(all(v));
    assert((v == V<int>{1, 2, 3, 4}));

    minpq<int> mn;
    mn.push(3);
    mn.push(1);
    mn.push(2);
    mn.push(1);
    assert(mn.top() == 1);
    mn.pop();
    assert(mn.top() == 1);

    maxpq_ll mx;
    mx.push(3LL);
    mx.push(1);
    mx.push(1LL << 40);
    mx.push(-(1LL << 40));
    assert(mx.top() == (1LL << 40));

    assert((DR4 == array<int, 4>{-1, 0, 1, 0}));
    assert((DC4 == array<int, 4>{0, 1, 0, -1}));
    assert((DIR4 == array<char, 4>{'U', 'R', 'D', 'L'}));
    assert((dir4 == array<char, 4>{'u', 'r', 'd', 'l'}));
    assert((DR8 == array<int, 8>{-1, -1, 0, 1, 1, 1, 0, -1}));
    assert((DC8 == array<int, 8>{0, 1, 1, 1, 0, -1, -1, -1}));
    assert((DIR8 == array<string, 8>{"U", "UR", "R", "DR", "D", "DL", "L", "UL"}));
    assert((dir8 == array<string, 8>{"u", "ur", "r", "dr", "d", "dl", "l", "ul"}));
    assert(in_grid(0, 0, 3, 4));
    assert(in_grid(2, 3, 3, 4));
    assert(!in_grid(-1, 0, 3, 4));
    assert(!in_grid(0, 4, 3, 4));
    assert(!in_grid(0, 0, 0, 4));
    assert(!in_grid(0, 0, 3, 0));

    int a = 10;
    assert(chmin(a, 7));
    assert(a == 7);
    assert(!chmin(a, 8));
    assert(!chmin(a, 7));
    assert(chmax(a, 9));
    assert(a == 9);
    assert(!chmax(a, 8));
    assert(!chmax(a, 9));

    assert(sgn(10) == 1);
    assert(sgn(0) == 0);
    assert(sgn(-10) == -1);
    assert(clampv(5, 1, 4) == 4);
    assert(clampv(-1, 1, 4) == 1);
    assert(clampv(3, 1, 4) == 3);
    assert(clampv(1, 1, 4) == 1);
    assert(clampv(4, 1, 4) == 4);
    assert(clampv(10, 5, 5) == 5);
    assert(clampv(-10, 5, 5) == 5);
    assert(ceil_div(5, 2) == 3);
    assert(ceil_div(7, 3) == 3);
    assert(ceil_div(-5, 2) == -2);
    assert(ceil_div(-7, 3) == -2);
    assert(ceil_div(5, -2) == -2);
    assert(ceil_div(7, -3) == -2);
    assert(ceil_div(-5, -2) == 3);
    assert(ceil_div(-7, -3) == 3);
    assert(ceil_div(4, 2) == 2);
    assert(ceil_div(0, 3) == 0);
    assert(floor_div(5, 2) == 2);
    assert(floor_div(7, 3) == 2);
    assert(floor_div(-5, 2) == -3);
    assert(floor_div(-7, 3) == -3);
    assert(floor_div(5, -2) == -3);
    assert(floor_div(7, -3) == -3);
    assert(floor_div(-5, -2) == 2);
    assert(floor_div(-7, -3) == 2);
    assert(floor_div(4, 2) == 2);
    assert(floor_div(0, 3) == 0);
    assert(tri0(0) == 0);
    assert(tri0(5) == 10);
    assert(tri1(0) == 0);
    assert(tri1(5) == 15);

    auto fact = yc([](auto self, int x) -> int {
        if (x <= 1) return 1;
        return x * self(x - 1);
    });
    assert(fact(5) == 120);

    auto fib = yc([](auto self, int x) -> int {
        if (x <= 1) return x;
        return self(x - 1) + self(x - 2);
    });
    assert(fib(0) == 0);
    assert(fib(7) == 13);

    ostringstream out;
    auto *old_cout = cout.rdbuf(out.rdbuf());
    println();
    println(1, "abc", 2);
    print_one("x", 1);
    println();
    printAll(V<int>{4, 5});
    printAll(V<int>{});
    yes();
    yes(false);
    YES();
    YES(false);
    cout.rdbuf(old_cout);

    assert(out.str() == "\n1 abc 2\nx 1\n4\n5\nYes\nNo\nYES\nNO\n");

    return 0;
}
