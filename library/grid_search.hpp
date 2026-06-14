// Grid Algorithms.
#pragma once

#include "basic.hpp"
#include "grid.hpp"

struct GridBFS {
    const Grid *grid = nullptr;
    pii source = {-1, -1};
    V<V<int>> dist;
    V<V<pii>> parent;
    V<V<int>> parent_dir;

    GridBFS() = default;

    GridBFS(const Grid &g, const pii& s) {
        build(g, s);
    }

    void build(const Grid &g, const pii& s) {
        grid = &g;
        source = s;

        dist.assign(g.H, V<int>(g.W, -1));
        parent.assign(g.H, V<pii>(g.W, {-1, -1}));
        parent_dir.assign(g.H, V<int>(g.W, -1));

        queue<pii> q;
        dist[s.first][s.second] = 0;
        q.push(s);

        while (!q.empty()) {
            auto [i, j] = q.front();
            q.pop();

            V<pii> neighbors = g.neighbors4(i, j);

            for (const auto neighbor : neighbors) {
                const auto [ni, nj] = neighbor;

                if (dist[ni][nj] != -1) continue;

                const int di = ni - i, dj = nj - j;
                const int dir = (dj == 0 ? di + 1 : (dj == 1 ? 1 : 3));

                dist[ni][nj] = dist[i][j] + 1;
                parent[ni][nj] = {i, j};
                parent_dir[ni][nj] = dir;

                q.emplace(ni, nj);
            }
        }
    }

    [[nodiscard]] V<pii> path(const pii& t) const {
        V<pii> res;

        pii now = t;

        while (true) {
            res.emplace_back(now);

            if (now == source) break;

            pii p = parent[now.first][now.second];
            if (p == pii{-1, -1}) return {};

            now = p;
        }

        reverse(all(res));
        return res;
    }

    [[nodiscard]] string moves4(const pii& t) const {
        string moves;

        pii now = t;

        while (now != source) {
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
};
