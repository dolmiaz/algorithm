#pragma once

#include "basic.hpp"

struct DSU {
    vector<int> parent_or_size;
    int group_count;

    explicit DSU(const int n) {
        parent_or_size.assign(n, -1);
        group_count = n;
    }

    int leader(const int x){
        if (parent_or_size[x] < 0) return x;
        return parent_or_size[x] = leader(parent_or_size[x]);
    }

    bool merge(int a, int b) {
        const int leader_a = leader(a);
        const int leader_b = leader(b);

        if (leader_a == leader_b) return false;

        if (abs(parent_or_size[leader_a]) > abs(parent_or_size[leader_b])) {
            parent_or_size[leader_a] += parent_or_size[leader_b];
            parent_or_size[leader_b] = leader_a;
            group_count--;
            return true;
        }
        parent_or_size[leader_b] += parent_or_size[leader_a];
        parent_or_size[leader_a] = leader_b;
        group_count--;
        return true;
    }

    bool same(int a, int b) {
        return leader(a) == leader(b);
    }

    int size(int x) {
        x = leader(x);
        return -parent_or_size[x];
    }

    [[nodiscard]] int count_groups() const {
        return group_count;
    }
};
