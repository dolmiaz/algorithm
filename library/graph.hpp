// Graph data structures and input helpers.
#pragma once

#include "basic.hpp"

// ============== グラフテンプレ ==============
struct Edge {
    int to;
    ll w;
    Edge() : to(0), w(1) {}
    Edge(int _to, ll _w = 1) : to(_to), w(_w) {}
};

struct Graph {
    V<V<Edge>> graph;
    bool undirected = true;
    bool weighted = false;
    bool one_indexed = true;

    Graph() = default;

    explicit Graph(const int n, const bool _undirected = true, const bool _weighted = false, const bool _one_indexed = true)
        : graph(n),
          undirected(_undirected),
          weighted(_weighted),
          one_indexed(_one_indexed) {}

    [[nodiscard]] int size() const {
        return static_cast<int>(graph.size());
    }

    [[nodiscard]] int to_internal(const int v) const {
        return one_indexed ? v - 1 : v;
    }

    [[nodiscard]] int to_external(const int v) const {
        return one_indexed ? v + 1 : v;
    }

    void add_edge_internal(const int a, const int b, const ll w = 1) {
        graph[a].emplace_back(b, w);
        if (undirected) {
            graph[b].emplace_back(a, w);
        }
    }

    void add_edge(int a, int b, const ll w = 1) {
        a = to_internal(a);
        b = to_internal(b);
        add_edge_internal(a, b, w);
    }
};

inline Graph read_graph(
    const int n,
    const int m,
    const bool undirected = true,
    const bool weighted = false,
    const bool one_indexed = true
) {
    Graph g(n, undirected, weighted, one_indexed);

    rep(_, m) {
        int a, b;
        ll w = 1;

        if (weighted) {
            cin >> a >> b >> w;
        } else {
            cin >> a >> b;
        }

        g.add_edge(a, b, w);
    }

    return g;
}
