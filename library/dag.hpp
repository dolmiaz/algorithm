#pragma once

#include "basic.hpp"
#include "graph.hpp"
#include "graph_search.hpp"

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
    const Graph* graph_ref = nullptr;
    V<int> cycle;
    bool has_cycle = false;

    DirectedCycle() = default;

    explicit DirectedCycle(const Graph& g) {
        build(g);
    }

    void build(const Graph& g) {
        graph_ref = &g;
        cycle.clear();
        has_cycle = false;

        const int n = g.size();
        V<int> color(n, 0), parent(n, -1);

        const auto dfs = yc([&](auto self, int v) -> bool {
            color[v] = 1;

            for (const auto &e : g.graph[v]) {
                const int to = e.to;

                if (color[to] == 0) {
                    parent[to] = v;
                    if (self(to)) return true;
                } else if (color[to] == 1) {
                    cycle.push_back(to);
                    for (int x = v; x != to; x = parent[x]) {
                        cycle.push_back(x);
                    }
                    reverse(all(cycle));
                    has_cycle = true;
                    return true;
                }
            }

            color[v] = 2;
            return false;
        });

        rep(v, n) {
            if (color[v] != 0) continue;
            if (dfs(v)) return;
        }
    }

    V<int> cycle_external() const {
        V<int> res = cycle;
        if (graph_ref && graph_ref->one_indexed) {
            for (auto &v : res) v++;
        }
        return res;
    }
};
struct SCC {
    const Graph* graph_ref = nullptr;
    int comp_cnt = 0;
    V<int> comp_id;
    V<V<int>> groups;

    SCC() = default;

    explicit SCC(const Graph& g) {
        build(g);
    }

    void build(const Graph& g) {
        graph_ref = &g;

        const int n = g.size();

        Graph rg(n, false, g.weighted, false);
        rep(v, n) {
            for (const auto &e : g.graph[v]) {
                rg.add_edge_internal(e.to, v, e.w);
            }
        }

        GraphDFS dfs(g);
        V<int> order = dfs.post_order;
        reverse(all(order));

        comp_id.assign(n, -1);
        groups.clear();

        GraphDFS rdfs;
        rdfs.build_all(rg, order);

        comp_cnt = rdfs.comp_cnt;
        comp_id = rdfs.comp_id;

        groups.assign(comp_cnt, {});
        rep(v, n) {
            groups[comp_id[v]].push_back(v);
        }
    }

    bool same(int a, int b) const {
        a = graph_ref->to_internal(a);
        b = graph_ref->to_internal(b);
        return comp_id[a] == comp_id[b];
    }

    int id(int v) const {
        v = graph_ref->to_internal(v);
        return comp_id[v];
    }

    int size(int v) const {
        v = graph_ref->to_internal(v);
        return static_cast<int>(groups[comp_id[v]].size());
    }
};

template <class T = ll>
struct DAGLongestPath {
    const Graph* graph_ref = nullptr;
    V<T> dist;
    V<int> parent;
    V<int> order;
    bool is_dag = false;

    DAGLongestPath() = default;

    DAGLongestPath(const Graph& g, int s) {
        build(g, s);
    }

    explicit DAGLongestPath(const Graph& g) {
        build_all(g);
    }

    void build(const Graph& g, int s) {
        graph_ref = &g;
        s = g.to_internal(s);

        init(g);
        if (!is_dag) return;

        dist[s] = T(0);
        relax(g);
    }

    void build_all(const Graph& g) {
        graph_ref = &g;
        const int n = g.size();

        init(g);
        if (!is_dag) return;

        rep(v, n) {
            dist[v] = T(0);
        }
        relax(g);
    }

    T distance(int t) const {
        t = graph_ref->to_internal(t);
        return dist[t];
    }

    bool reachable(int t) const {
        return distance(t) != neg_inf();
    }

    V<int> path(int t) const {
        t = graph_ref->to_internal(t);
        if (dist[t] == neg_inf()) return {};

        V<int> res;
        for (int v = t; v != -1; v = parent[v]) {
            res.push_back(v);
        }
        reverse(all(res));

        for (auto &v : res) {
            v = graph_ref->to_external(v);
        }
        return res;
    }

  private:
    static T neg_inf() {
        return numeric_limits<T>::lowest() / T(4);
    }

    void init(const Graph& g) {
        const int n = g.size();
        TopologicalSort topo(g);

        is_dag = topo.is_dag;
        order = topo.order;
        dist.assign(n, neg_inf());
        parent.assign(n, -1);
    }

    void relax(const Graph& g) {
        for (const int v : order) {
            if (dist[v] == neg_inf()) continue;

            for (const auto &e : g.graph[v]) {
                const int to = e.to;
                const T nd = dist[v] + static_cast<T>(e.w);

                if (dist[to] >= nd) continue;

                dist[to] = nd;
                parent[to] = v;
            }
        }
    }
};
