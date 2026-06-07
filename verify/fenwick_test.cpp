#include <cassert>

#include "../library/fenwick.hpp"

int main() {
    Fenwick<ll> fw(5);

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

    const Fenwick<ll> &cfw = fw;
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

    Fenwick<int> empty;
    assert(empty.size == 0);
    assert(empty.bit.empty());
    empty.init(0);
    assert(empty.sum(0) == 0);

    Fenwick<ll> pushed;
    pushed.push(2);
    pushed.push(4);
    pushed.push(1);
    assert(pushed.size == 3);
    assert(pushed.sum(0, 3) == 7);
    assert(pushed.lower_bound(0) == 0);
    assert(pushed.lower_bound(1) == 0);
    assert(pushed.lower_bound(2) == 0);
    assert(pushed.lower_bound(3) == 1);
    assert(pushed.lower_bound(6) == 1);
    assert(pushed.lower_bound(7) == 2);
    assert(pushed.lower_bound(8) == 3);

    RangeFenwick<ll> range(5);
    assert(range.size == 5);
    assert(range.sum(0, 5) == 0);
    range.add(1, 4, 3);
    assert(range.get(0) == 0);
    assert(range.get(1) == 3);
    assert(range.get(3) == 3);
    assert(range.get(4) == 0);
    assert(range.sum(0, 5) == 9);
    assert(range.sum(2, 5) == 6);
    range.add(2, 5, -1);
    assert(range.get(1) == 3);
    assert(range.get(2) == 2);
    assert(range.get(4) == -1);
    assert(range.sum(0, 5) == 6);
    range.set(2, 10);
    assert(range.get(2) == 10);
    assert(range.sum(1, 4) == 15);
    range.add(4, 4, 100);
    assert(range.get(4) == -1);

    return 0;
}
