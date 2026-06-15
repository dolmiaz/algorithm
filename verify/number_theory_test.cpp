#include "../library/crt.hpp"
#include "../library/discrete_log.hpp"
#include "../library/floor_sum.hpp"
#include "../library/garner.hpp"
#include "../library/mobius.hpp"
#include "../library/pollard_rho.hpp"
#include "../library/primitive_root.hpp"

#include <cassert>

int main() {
    assert(fast_pow<ll>(2, 10) == 1024);
    assert(mod_pow(2, 10, 1000) == 24);

    ll x, y;
    assert(ext_gcd(30, 18, x, y) == 6);
    assert(30 * x + 18 * y == 6);
    assert(mod_inv(3, 11) == 4);

    assert((divisors(12) == V<ll>{1, 2, 3, 4, 6, 12}));
    assert((factorize(360) == V<pair<ll, int>>{{2, 3}, {3, 2}, {5, 1}}));
    assert(euler_phi(36) == 12);

    auto mu = mobius_table(10);
    assert((mu == V<int>{0, 1, -1, -1, 0, -1, 1, -1, 0, 0, 1}));

    assert(crt(V<ll>{2, 3}, V<ll>{3, 5}) == make_pair(8LL, 15LL));
    assert(crt(V<ll>{1, 2}, V<ll>{2, 4}) == make_pair(0LL, 0LL));
    assert(floor_sum(6, 5, 4, 3) == 13);

    assert(is_prime64(2));
    assert(is_prime64(1'000'000'007ULL));
    assert(!is_prime64(1'000'000'008ULL));

    auto pf = factorize_pollard(600851475143ULL);
    assert((pf == V<ull>{71, 839, 1471, 6857}));

    assert(discrete_log(2, 8, 13) == 3);
    assert(discrete_log(2, 3, 4) == -1);

    assert(primitive_root(998244353) == 3);
    assert(garner(V<ll>{2, 3}, V<ll>{3, 5}, 1000000007) == 8);

    return 0;
}
