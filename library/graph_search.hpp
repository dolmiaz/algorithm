// DFS, BFS, path restoration, and connected-component helpers.
#pragma once

#include "graph.hpp"
#include "io.hpp"

// ============== グラフアルゴリズム ==============
// ============== DFS ==============
struct GraphDFS {
    const Graph *graph_ref = nullptr;
    V<int> used, parent, tin, tout, comp_id, order, post_order;
    int comp_cnt = 0;
    int timer = 0;

    GraphDFS() = default;

    explicit GraphDFS(const Graph &graph) {
        build_all(graph);
    }

    GraphDFS(const Graph &graph, const int s) {
        build(graph, s);
    }

    void build(const Graph &graph, int s) {
        s = graph.to_internal(s);
        init(graph);
        run_dfs(V<int>{s});
    }

    void build_multi(const Graph &graph, const V<int> &starts) {
        V<int> internal_starts = starts;
        for (auto &s : internal_starts) {
            s = graph.to_internal(s);
        }

        init(graph);
        run_dfs(internal_starts);
    }

    void build_all(const Graph &graph) {
        const int n = graph.size();
        V<int> starts(n);
        iota(all(starts), 0);

        init(graph);
        run_dfs(starts);
    }

    void build_all(const Graph &graph, const V<int> &starts) {
        const int n = graph.size();
        V<int> internal_starts = starts;
        for (auto &s : internal_starts) {
            s = graph.to_internal(s);
        }
        rep(v, n) {
            internal_starts.push_back(v);
        }

        init(graph);
        run_dfs(internal_starts);
    }

  private:
    void init(const Graph &graph) {
        graph_ref = &graph;
        const int n = graph.size();

        used.assign(n, 0);
        parent.assign(n, -1);
        tin.assign(n, -1);
        tout.assign(n, -1);
        comp_id.assign(n, -1);
        order.clear();
        order.reserve(n);
        post_order.clear();
        post_order.reserve(n);
        comp_cnt = 0;
        timer = 0;
    }

    void run_dfs(const V<int> &starts) {
        const auto &g = graph_ref->graph;

        const auto dfs = yc([&](auto self, int v, const int p) -> void {
            used[v] = 1;
            parent[v] = p;
            tin[v] = timer++;
            comp_id[v] = comp_cnt;
            order.push_back(v);

            for (const auto &e : g[v]) {
                const int to = e.to;
                if (used[to]) continue;
                self(to, v);
            }

            tout[v] = timer;
            post_order.push_back(v);
        });

        for (const int v : starts) {
            if (used[v]) continue;
            dfs(v, -1);
            comp_cnt++;
        }
    }
};

// ============== BFS ==============
struct GraphBFS {
    const Graph *graph_ref = nullptr;
    V<int> dist, parent;
    V<int> order, source;

    GraphBFS() = default;

    GraphBFS(const Graph &graph, const int s) {
        build(graph, s);
    }

    void build(const Graph &graph, int s) {
        graph_ref = &graph;
        const auto &g = graph.graph;
        const int n = graph.size();

        s = graph.to_internal(s);

        dist.assign(n, -1);
        parent.assign(n, -1);
        source.assign(n, -1);
        order.clear();
        order.reserve(n);

        queue<int> q;

        dist[s] = 0;
        source[s] = s;
        q.push(s);

        run_bfs(q, g);
    }

    void build_multi(const Graph &graph, const V<int> &starts) {
        graph_ref = &graph;
        const auto &g = graph.graph;
        const int n = graph.size();

        dist.assign(n, -1);
        parent.assign(n, -1);
        source.assign(n, -1);
        order.clear();
        order.reserve(n);

        queue<int> q;

        for (int s : starts) {
            s = graph.to_internal(s);

            if (dist[s] != -1) continue;

            dist[s] = 0;
            source[s] = s;
            q.push(s);
        }

        run_bfs(q, g);
    }

    [[nodiscard]] V<int> path(int t) const {
        const Graph &graph = *graph_ref;
        t = graph.to_internal(t);

        if (source[t] == -1) return {};

        V<int> res;
        const int s = source[t];

        for (int v = t; v != -1; v = parent[v]) {
            res.push_back(v);
            if (v == s) break;
        }

        if (res.back() != s) return {};

        reverse(all(res));
        for (auto &v : res) {
            v = graph.to_external(v);
        }
        return res;
    }

private:
    void run_bfs(queue<int> &q, const V<V<Edge>> &g) {
        while (!q.empty()) {
            const int v = q.front();
            q.pop();

            order.push_back(v);

            for (const auto &e : g[v]) {
                const int to = e.to;
                if (dist[to] != -1) continue;

                dist[to] = dist[v] + 1;
                parent[to] = v;
                source[to] = source[v];

                q.push(to);
            }
        }
    }
};

// ============== 連結成分 ==============
struct ConnectedComponents {
    const Graph *graph_ref = nullptr;
    V<int> comp_id;
    V<int> comp_size;
    int comp_cnt = 0;

    ConnectedComponents() = default;

    explicit ConnectedComponents(const Graph &graph) {
        build(graph);
    }

    void build(const Graph &graph) {
        graph_ref = &graph;
        const auto &g = graph.graph;
        const int n = graph.size();

        comp_id.assign(n, -1);
        comp_size.clear();
        comp_cnt = 0;

        rep(s, n) {
            if (comp_id[s] != -1) continue;

            queue<int> q;
            q.push(s);
            comp_id[s] = comp_cnt;

            int sz = 0;

            while (!q.empty()) {
                const int v = q.front();
                q.pop();

                sz++;

                for (const auto &e : g[v]) {
                    const int to = e.to;

                    if (comp_id[to] != -1) continue;

                    comp_id[to] = comp_cnt;
                    q.push(to);
                }
            }

            comp_size.push_back(sz);
            comp_cnt++;
        }
    }

    [[nodiscard]] bool same(int a, int b) const {
        const Graph &graph = *graph_ref;
        a = graph.to_internal(a);
        b = graph.to_internal(b);
        return comp_id[a] == comp_id[b];
    }

    [[nodiscard]] int size(int v) const {
        const Graph &graph = *graph_ref;
        v = graph.to_internal(v);
        return comp_size[comp_id[v]];
    }

    [[nodiscard]] int count() const {
        return comp_cnt;
    }
};
