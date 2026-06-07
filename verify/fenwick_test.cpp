#include <cassert>

#include "../library/fenwick.hpp"

int main() {
    XorFenwick<ll> fw(5);

    assert(fw.size == 5);
    assert(fw.bit.size() == 6);
    assert(fw.sum(0) == 0);
    assert(fw.sum(5) == 0);
    assert(fw.sum(0, 5) == 0);

    fw.add(0, 3);
    fw.add(1, -2);
    fw.add(3, 7);

    assert(fw.sum(0) == 0);
    assert(fw.sum(1) == 3);
    assert(fw.sum(2) == 1);
    assert(fw.sum(4) == 8);
    assert(fw.sum(5) == 8);
    assert(fw.sum(0, 1) == 3);
    assert(fw.sum(1, 4) == 5);
    assert(fw.sum(2, 4) == 7);
    assert(fw.sum(2, 2) == 0);
    assert(fw.get(0) == 3);
    assert(fw.get(1) == -2);
    assert(fw.get(2) == 0);
    assert(fw.get(3) == 7);
    assert(fw.get(4) == 0);

    fw.set(1, 5);
    assert(fw.get(0) == 3);
    assert(fw.get(1) == 5);
    assert(fw.get(3) == 7);
    assert(fw.sum(0, 5) == 15);
    assert(fw.sum(1, 4) == 12);

    fw.set(3, -4);
    assert(fw.get(3) == -4);
    assert(fw.sum(0, 5) == 4);

    const XorFenwick<ll> &cfw = fw;
    assert(cfw.sum(3) == 8);
    assert(cfw.sum(2, 5) == -4);
    assert(cfw.get(1) == 5);

    fw.init(3);
    assert(fw.size == 3);
    assert(fw.bit.size() == 4);
    assert(fw.sum(0) == 0);
    assert(fw.sum(3) == 0);
    fw.add(2, 10);
    assert(fw.sum(0, 3) == 10);
    assert(fw.get(2) == 10);

    XorFenwick<int> empty;
    assert(empty.size == 0);
    assert(empty.bit.empty());
    empty.init(0);
    assert(empty.sum(0) == 0);

    return 0;
}
