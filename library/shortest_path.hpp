// Shortest path algorithms for Graph.
#pragma once

#include "graph.hpp"

// ============== Dijkstra ==============
struct Dijkstra {
    const Graph *graph_ref = nullptr;
    int source = -1;
    V<ll> dist;
    V<int> parent;
    V<int> order;

    Dijkstra() = default;

    Dijkstra(const Graph &graph, const int s) {
        build(graph, s);
    }

    void build(const Graph &graph, int s) {
        graph_ref = &graph;
        const auto &g = graph.graph;
        const int n = graph.size();

        s = graph.to_internal(s);
        source = s;

        dist.assign(n, INF_L);
        parent.assign(n, -1);
        order.clear();
        order.reserve(n);

        minpq<pair<ll, int>> pq;

        dist[s] = 0;
        pq.emplace(0, s);

        while (!pq.empty()) {
            const auto [d, v] = pq.top();
            pq.pop();

            if (d != dist[v]) continue;

            order.push_back(v);

            for (const auto &e : g[v]) {
                const int to = e.to;
                const ll nd = dist[v] + e.w;

                if (dist[to] <= nd) continue;

                dist[to] = nd;
                parent[to] = v;

                pq.emplace(nd, to);
            }
        }
    }

    [[nodiscard]] ll distance(int t) const {
        const Graph &graph = *graph_ref;
        t = graph.to_internal(t);
        return dist[t];
    }

    [[nodiscard]] bool reachable(int t) const {
        return distance(t) != INF_L;
    }

    [[nodiscard]] V<int> path(int t) const {
        const Graph &graph = *graph_ref;
        t = graph.to_internal(t);

        if (t == source) return V<int>{graph.to_external(source)};
        if (parent[t] == -1) return {};

        V<int> res;

        for (int v = t; v != -1; v = parent[v]) {
            res.push_back(v);
            if (v == source) break;
        }

        if (res.back() != source) return {};

        reverse(all(res));

        for (auto &v : res) {
            v = graph.to_external(v);
        }

        return res;
    }
};
