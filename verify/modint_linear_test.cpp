#include "../library/linear_algebra.hpp"
#include "../library/matrix.hpp"
#include "../library/modint.hpp"
#include "../library/xor_basis.hpp"

#include <cassert>

int main() {
    using mint = modint998244353;
    assert((mint(2) + mint(998244352)).val() == 1);
    assert((mint(3) * mint(4)).val() == 12);
    assert((mint(2).pow(10)).val() == 1024);
    assert((mint(3) * mint(3).inv()).val() == 1);

    using dmint = dynamic_modint<0>;
    dmint::set_mod(17);
    assert((dmint(5) + dmint(15)).val() == 3);
    assert((dmint(3).pow(4)).val() == 13);

    Matrix<mint> fib{{1, 1}, {1, 0}};
    auto fib5 = matrix_pow(fib, 5);
    assert(fib5[0][1].val() == 5);

    Matrix<mint> a{{2, 1}, {1, 1}};
    V<mint> b{5, 3};
    auto [ok, sol] = solve_linear_system(a, b);
    assert(ok);
    assert(sol[0].val() == 2);
    assert(sol[1].val() == 1);

    Matrix<mint> rank_mat{{1, 2, 3}, {2, 4, 6}, {1, 0, 1}};
    assert(matrix_rank(rank_mat) == 2);

    XorBasis xb;
    assert(xb.insert(3));
    assert(xb.insert(5));
    assert(!xb.insert(6));
    assert(xb.can_make(6));
    assert(xb.max_xor() == 6);
    assert(xb.rank() == 2);

    return 0;
}
