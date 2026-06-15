#pragma once

#include "basic.hpp"
#include "graph.hpp"
#include "io.hpp"

struct KColoring {
    const Graph *graph_ref = nullptr;
    int k = 0;
    V<int> color;
    bool found = false;

    KColoring() = default;

    KColoring(const Graph& g, const int k_) {
        build(g, k_);
    }

    bool build(const Graph& g, const int k_) {
        graph_ref = &g;
        k = k_;
        color.assign(g.size(), -1);

        found = solve_by_dsat(g);
        return found;
    }

    int min_colors(const Graph& g) {
        const int n = g.size();
        rep(colors, n + 1) {
            if (build(g, colors)) return colors;
        }
        return -1;
    }

    bool valid() const {
        if (!graph_ref) return false;
        if (static_cast<int>(color.size()) != graph_ref->size()) return false;

        rep(v, graph_ref->size()) {
            if (color[v] < 0 || color[v] >= k) return false;

            for (const auto& e : graph_ref->graph[v]) {
                if (color[v] == color[e.to]) return false;
            }
        }

        return true;
    }

  private:
    V<V<int>> build_undirected_adjacency(const Graph& g) const {
        const int n = g.size();
        V<V<int>> adj(n);

        rep(v, n) {
            for (const auto& e : g.graph[v]) {
                const int to = e.to;
                adj[v].push_back(to);
                if (v != to) adj[to].push_back(v);
            }
        }

        rep(v, n) {
            sort(all(adj[v]));
            adj[v].erase(unique(all(adj[v])), adj[v].end());
        }

        return adj;
    }

    bool solve_by_dsat(const Graph& g) {
        const int n = g.size();
        if (n == 0) return k >= 0;
        if (k <= 0) return false;

        const V<V<int>> adj = build_undirected_adjacency(g);
        rep(v, n) {
            if (binary_search(all(adj[v]), v)) return false;
        }

        const auto dfs = yc([&](auto self, const int colored_count) -> bool {
            if (colored_count == n) return true;

            int best = -1;
            int best_saturation = -1;
            int best_degree = -1;

            rep(v, n) {
                if (color[v] != -1) continue;

                V<int> seen(k, 0);
                int saturation = 0;

                for (const int to : adj[v]) {
                    if (color[to] == -1) continue;
                    if (seen[color[to]]) continue;
                    seen[color[to]] = 1;
                    saturation++;
                }

                const int degree = static_cast<int>(adj[v].size());
                if (
                    saturation > best_saturation ||
                    (saturation == best_saturation && degree > best_degree)
                ) {
                    best = v;
                    best_saturation = saturation;
                    best_degree = degree;
                }
            }

            V<int> forbidden(k, 0);
            for (const int to : adj[best]) {
                if (color[to] != -1) forbidden[color[to]] = 1;
            }

            rep(c, k) {
                if (forbidden[c]) continue;

                color[best] = c;
                if (self(colored_count + 1)) return true;
                color[best] = -1;
            }

            return false;
        });

        return dfs(0);
    }

};
