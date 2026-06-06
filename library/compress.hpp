#pragma once

#include "basic.hpp"

template <class T>
struct Compress {
    V<T> xs;

    Compress() {}

    Compress(const V<T> &v) {
        xs = v;
        build();
    }

    void add(const T &x) {
        xs.push_back(x);
    }

    void add(const V<T> &vec) {
        xs.insert(xs.end(), all(vec));
    }

    void build() {
        sort(all(xs));
        xs.erase(unique(all(xs)), xs.end());
    }

    int get(const T x) {
        return lower_bound(all(xs), x) - xs.begin();
    }

    T val(const int i) const {
        return xs[i];
    }

    int size() const {
        return static_cast<int>(xs.size());
    }
};
