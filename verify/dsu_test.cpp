#include <cassert>

#include "../library/dsu.hpp"

int main() {
    DSU dsu(6);

    assert(dsu.count_groups() == 6);
    for (int i = 0; i < 6; i++) {
        assert(dsu.leader(i) == i);
        assert(dsu.size(i) == 1);
        assert(dsu.same(i, i));
    }
    assert(!dsu.same(0, 1));

    assert(dsu.merge(0, 1));
    assert(dsu.same(0, 1));
    assert(dsu.size(0) == 2);
    assert(dsu.size(1) == 2);
    assert(dsu.count_groups() == 5);

    assert(!dsu.merge(1, 0));
    assert(dsu.count_groups() == 5);
    assert(dsu.size(0) == 2);

    assert(dsu.merge(2, 3));
    assert(dsu.merge(4, 5));
    assert(dsu.count_groups() == 3);

    assert(dsu.merge(0, 2));
    assert(dsu.same(1, 3));
    assert(dsu.size(0) == 4);
    assert(dsu.size(3) == 4);
    assert(dsu.count_groups() == 2);

    assert(dsu.merge(4, 0));
    assert(dsu.count_groups() == 1);
    for (int i = 0; i < 6; i++) {
        assert(dsu.same(0, i));
        assert(dsu.size(i) == 6);
    }

    DSU tie(4);
    assert(tie.merge(0, 1));
    assert(tie.leader(0) == 1);
    assert(tie.leader(1) == 1);

    return 0;
}
