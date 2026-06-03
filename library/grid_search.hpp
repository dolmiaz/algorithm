// Grid Algorithms.
#pragma once

#include "basic.hpp"
#include "grid.hpp"

struct GridBFS_Info {
    V<V<int>> dist;
    V<V<pii>> parent;
    V<V<int>> parent_dir;
};

inline GridBFS_Info grid_bfs(const Grid& g, const pair<int, int> s) {
    GridBFS_Info info;

    info.dist.assign(g.H, V<int>(g.W, -1));
    info.parent.assign(g.H, V<pii>(g.W, {-1, -1}));
    info.parent_dir.assign(g.H, V<int>(g.W, -1));

    queue<pii> q;
    info.dist[s.first][s.second] = 0;
    q.push(s);

    while (!q.empty()) {
        auto [i, j] = q.front();
        q.pop();

        V<pii> neighbors = g.neighbors4(i, j);

        for (const auto neighbor : neighbors) {
            const auto [ni, nj] = neighbor;

            if (info.dist[ni][nj] != -1) continue;

            const int di = ni - i, dj = nj - j;
            const int dir = (dj == 0 ? di + 1 : (dj == 1 ? 1 : 3));

            info.dist[ni][nj] = info.dist[i][j] + 1;
            info.parent[ni][nj] = {i, j};
            info.parent_dir[ni][nj] = dir;

            q.emplace(ni, nj);
        }
    }

    return info;
}

inline V<pii> restore_grid_path(const V<V<pii>> &parent, const pii s, const pii t) {
    V<pii> path;

    pii now = t;

    while (true) {
        path.emplace_back(now);

        if (now == s) break;

        pii p = parent[now.first][now.second];

        if (p == pii{-1, -1}) return {};

        now = p;
    }

    reverse(all(path));
    return path;
}

inline string restore_grid_moves4(const V<V<int>> &parent_dir, const pii s, const pii t) {
    string moves;

    pii now = t;

    while (now != s) {
        const int dir = parent_dir[now.first][now.second];

        if (dir < 0 || dir >= 4) return "";

        moves.push_back(DIR4[dir]);

        const int pi = now.first - DR4[dir];
        const int pj = now.second - DC4[dir];

        now = {pi, pj};
    }

    reverse(all(moves));
    return moves;
}