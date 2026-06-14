#pragma once

#include "basic.hpp"
#include "graph.hpp"

struct TopologicalSort {
    const Graph* graph_ref = nullptr;
    V<int> order;
    V<int> indeg;
    bool is_dag = false;

    TopologicalSort() = default;
    explicit TopologicalSort(const Graph& g) {
        build(g);
    }

    void build(const Graph& g) {
        order.clear();
        is_dag = false;

        graph_ref = &g;

        const int n = g.size();
        indeg.assign(n, 0);

        rep(i, n) {
            for (const auto& e : g.graph[i]) {
                indeg[e.to]++;
            }
        }

        queue<int> q;
        rep(i, n) {
            if (indeg[i] == 0) q.push(i);
        }

        V<int> cur_indeg = indeg;

        while (!q.empty()) {
            const int v = q.front();
            order.push_back(v);
            q.pop();

            for (auto e : g.graph[v]) {
                const int to = e.to;

                cur_indeg[to]--;
                if (cur_indeg[to] == 0) q.push(to);
            }
        }

        is_dag = static_cast<int>(order.size()) == n;
    }

    V<int> order_external() const {
        V<int> res = order;
        if (graph_ref && graph_ref->one_indexed) {
            for (auto& v : res) v++;
        }
        return res;
    }
};

struct DirectedCycle {
    V<int> cycle;
    bool has_cycle = false;

    DirectedCycle() = default;

    explicit DirectedCycle(const Graph& g) {
        build(g);
    }

    void build(const Graph& g);

    V<int> cycle_external() const;
};
struct SCC {
    int comp_cnt = 0;
    V<int> comp_id;
    V<V<int>> groups;

    SCC() = default;

    explicit SCC(const Graph& g) {
        build(g);
    }

    void build(const Graph& g);

    bool same(int a, int b) const;

    int id(int v) const;

    int size(int v) const;
};

template <class T>
struct DAGLongestPath {
    const Graph* graph_ref = nullptr;
    V<ll> dist;
    V<int> parent;
    V<int> order;
    bool is_dag = false;

    void build(const Graph& g, int s);
    void build_all(const Graph& g);
    ll distance(int t) const;
    bool reachable(int t) const;
    V<int> path(int t) const;
};