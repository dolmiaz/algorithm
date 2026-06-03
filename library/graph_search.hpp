// DFS, BFS, path restoration, and connected-component helpers.
#pragma once

#include "graph.hpp"
#include "io.hpp"

// ============== グラフアルゴリズム ==============
// ============== DFS ==============
struct DFS_Info {
    V<int> used, parent, tin, tout, comp_id, order;
    int comp_cnt = 0;
    int timer = 0;
};

inline DFS_Info dfs_all(const Graph &graph) {
    DFS_Info info;

    const auto &g = graph.graph;
    const int n = graph.size();

    info.used.assign(n, 0);
    info.parent.assign(n, -1);
    info.tin.assign(n, -1);
    info.tout.assign(n, -1);
    info.comp_id.assign(n, -1);
    info.order.reserve(n);

    const auto dfs = yc([&](auto self, int v, const int p) -> void {
        info.used[v] = 1;
        info.parent[v] = p;
        info.tin[v] = info.timer++;
        info.comp_id[v] = info.comp_cnt;
        info.order.push_back(v);

        for (const auto &e : g[v]) {
            const int to = e.to;
            if (info.used[to]) continue;
            self(to, v);
        }

        info.tout[v] = info.timer;
    });

    rep(v, n) {
        if (info.used[v]) continue;
        dfs(v, -1);
        info.comp_cnt++;
    }

    return info;
}

// ============== BFS ==============
struct BFS_Info {
    V<int> dist, parent;
    V<int> order, source;
};

inline BFS_Info bfs(const Graph &graph, int s) {
    BFS_Info info;

    const auto &g = graph.graph;
    const int n = graph.size();

    s = graph.to_internal(s);

    info.dist.assign(n, -1);
    info.parent.assign(n, -1);
    info.source.assign(n, -1);
    info.order.reserve(n);

    queue<int> q;

    info.dist[s] = 0;
    info.source[s] = s;
    q.push(s);

    while (!q.empty()) {
        const int v = q.front();
        q.pop();

        info.order.push_back(v);

        for (const auto &e : g[v]) {
            const int to = e.to;
            if (info.dist[to] != -1) continue;

            info.dist[to] = info.dist[v] + 1;
            info.parent[to] = v;
            info.source[to] = info.source[v];

            q.push(to);
        }
    }

    return info;
}

inline V<int> restore_path(const Graph &graph, const V<int> &parent, int s, int t) {
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

inline BFS_Info bfs_multi(const Graph &graph, const V<int> &starts) {
    BFS_Info info;

    const auto &g = graph.graph;
    const int n = graph.size();

    info.dist.assign(n, -1);
    info.parent.assign(n, -1);
    info.source.assign(n, -1);
    info.order.reserve(n);

    queue<int> q;

    for (int s : starts) {
        s = graph.to_internal(s);

        if (info.dist[s] != -1) continue;

        info.dist[s] = 0;
        info.source[s] = s;
        q.push(s);
    }

    while (!q.empty()) {
        const int v = q.front();
        q.pop();

        info.order.push_back(v);

        for (const auto &e : g[v]) {
            const int to = e.to;

            if (info.dist[to] != -1) continue;

            info.dist[to] = info.dist[v] + 1;
            info.parent[to] = v;
            info.source[to] = info.source[v];

            q.push(to);
        }
    }

    return info;
}

// ============== 連結成分 ==============
struct CC_Info {
    V<int> comp_id;
    V<int> comp_size;
    int comp_cnt = 0;
};

inline CC_Info connected_components(const Graph &graph) {
    CC_Info info;

    const auto &g = graph.graph;
    const int n = graph.size();

    info.comp_id.assign(n, -1);

    rep(s, n) {
        if (info.comp_id[s] != -1) continue;

        queue<int> q;
        q.push(s);
        info.comp_id[s] = info.comp_cnt;

        int sz = 0;

        while (!q.empty()) {
            const int v = q.front();
            q.pop();

            sz++;

            for (const auto &e : g[v]) {
                const int to = e.to;

                if (info.comp_id[to] != -1) continue;

                info.comp_id[to] = info.comp_cnt;
                q.push(to);
            }
        }

        info.comp_size.push_back(sz);
        info.comp_cnt++;
    }

    return info;
}
