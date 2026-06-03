// Shortest path algorithms for Graph.
#pragma once

#include "graph.hpp"

// ============== Dijkstra ==============
struct Dijkstra_Info {
    V<ll> dist;
    V<int> parent;
    V<int> order;
};

inline Dijkstra_Info dijkstra(const Graph &graph, int s) {
    Dijkstra_Info info;

    const auto &g = graph.graph;
    const int n = graph.size();

    s = graph.to_internal(s);

    info.dist.assign(n, INF_L);
    info.parent.assign(n, -1);
    info.order.reserve(n);

    minpq<pair<ll, int>> pq;

    info.dist[s] = 0;
    pq.emplace(0, s);

    while (!pq.empty()) {
        const auto [d, v] = pq.top();
        pq.pop();

        if (d != info.dist[v]) continue;

        info.order.push_back(v);

        for (const auto &e : g[v]) {
            const int to = e.to;
            const ll nd = info.dist[v] + e.w;

            if (info.dist[to] <= nd) continue;

            info.dist[to] = nd;
            info.parent[to] = v;

            pq.emplace(nd, to);
        }
    }

    return info;
}

inline V<int> restore_shortest_path(const Graph &graph, const V<int> &parent, int s, int t) {
    V<int> path;

    s = graph.to_internal(s);
    t = graph.to_internal(t);

    if (s == t) {
        path.push_back(s);
    } else {
        if (parent[t] == -1) return {};

        for (int v = t; v != -1; v = parent[v]) {
            path.push_back(v);
            if (v == s) break;
        }

        if (path.back() != s) return {};

        reverse(all(path));
    }

    for (auto &v : path) {
        v = graph.to_external(v);
    }

    return path;
}
