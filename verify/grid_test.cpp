#include "../library/grid_search.hpp"

#include <cassert>
#include <sstream>

int main() {
    Grid def;
    assert(def.H == 0);
    assert(def.W == 0);
    assert(def.cell.empty());
    assert(def.v.empty());
    assert(def.h.empty());
    assert(def.block == '#');
    assert(def.wall == '1');

    Grid g(3, 4);
    assert(g.H == 3);
    assert(g.W == 4);
    assert(g.cell.size() == 3);
    assert(g.cell[0] == "....");
    assert(g.v.size() == 3);
    assert(g.v[0] == "000");
    assert(g.h.size() == 2);
    assert(g.h[0] == "0000");
    assert(g.block == '#');
    assert(g.wall == '1');

    Grid one(1, 1);
    assert(one.cell.size() == 1);
    assert(one.cell[0] == ".");
    assert(one.v.size() == 1);
    assert(one.v[0].empty());
    assert(one.h.empty());
    assert(one.in(0, 0));
    assert(!one.in(0, 1));
    assert(one.id(0, 0) == 0);
    assert((one.rc(0) == pii{0, 0}));
    rep(d, 4) {
        assert(one.has_wall(0, 0, d));
        assert(!one.can_go(0, 0, d));
    }
    assert(one.neighbors4(0, 0).empty());

    Grid row(1, 3);
    assert(row.v.size() == 1);
    assert(row.v[0] == "00");
    assert(row.h.empty());
    assert(row.can_go(0, 0, 1));
    assert(row.can_go(0, 1, 3));
    assert(!row.can_go(0, 0, 0));
    assert(!row.can_go(0, 0, 2));

    Grid col(3, 1);
    assert(col.v.size() == 3);
    assert(col.v[0].empty());
    assert(col.h.size() == 2);
    assert(col.h[0] == "0");
    assert(col.can_go(0, 0, 2));
    assert(col.can_go(1, 0, 0));
    assert(!col.can_go(0, 0, 1));
    assert(!col.can_go(0, 0, 3));

    assert(g.in(2, 3));
    assert(!g.in(3, 0));
    assert(g.id(2, 3) == 11);
    assert((g.rc(11) == pii{2, 3}));

    g.cell[1][1] = '#';
    assert(g.is_block(1, 1));
    assert(!g.passable(1, 1));
    assert(!g.passable(-1, 0));
    assert(g.passable(0, 0));

    assert(g.has_wall(0, 1, 0));
    assert(g.has_wall(2, 1, 2));
    assert(g.has_wall(1, 0, 3));
    assert(g.has_wall(1, 3, 1));
    assert(g.has_wall(1, 1, -1));
    assert(g.has_wall(1, 1, 4));

    g.v[1][1] = '1';
    g.h[1][2] = '1';
    assert(g.has_wall(1, 1, 1));
    assert(g.has_wall(1, 2, 3));
    assert(g.has_wall(1, 2, 2));
    assert(g.has_wall(2, 2, 0));
    assert(!g.has_wall(1, 1, 0));
    assert(!g.has_wall(1, 1, 2));

    assert(!g.can_go(1, 0, 1));
    assert(!g.can_go(1, 1, 1));
    assert(!g.can_go(1, 2, 2));
    assert(!g.can_go(-1, 0, 2));
    assert(!g.can_go(1, 1, -1));
    assert(!g.can_go(1, 1, 4));

    Grid n4(3, 3);
    n4.cell[1][0] = '#';
    n4.v[1][1] = '1';
    n4.h[1][1] = '1';
    assert((n4.neighbors4(1, 1) == V<pii>{pii{0, 1}}));
    n4.v[1][1] = '0';
    n4.h[1][1] = '0';
    assert((n4.neighbors4(1, 1) == V<pii>{pii{0, 1}, pii{1, 2}, pii{2, 1}}));

    Grid custom(2, 2, 'X', 'W');
    custom.cell[0][1] = 'X';
    custom.v[1][0] = 'W';
    assert(custom.block == 'X');
    assert(custom.wall == 'W');
    assert(custom.is_block(0, 1));
    assert(custom.has_wall(1, 0, 1));

    Grid with_walls(2, 3, V<string>{"01", "10"}, V<string>{"101"}, '#', '1');
    assert(with_walls.v[0] == "01");
    assert(with_walls.h[0] == "101");
    assert(with_walls.has_wall(0, 1, 1));
    assert(with_walls.has_wall(1, 0, 1));
    assert(with_walls.has_wall(0, 0, 2));
    assert(!with_walls.has_wall(0, 1, 2));

    istringstream grid_in("2 3\n.#.\n..#\n");
    auto *old_cin = cin.rdbuf(grid_in.rdbuf());
    Grid read = read_grid();
    cin.rdbuf(old_cin);
    assert(read.H == 2);
    assert(read.W == 3);
    assert((read.cell == V<string>{".#.", "..#"}));
    assert(read.block == '#');
    assert(!read.passable(0, 1));
    assert(read.passable(1, 1));

    istringstream custom_grid_in("1 3\n.X.\n");
    old_cin = cin.rdbuf(custom_grid_in.rdbuf());
    Grid read_custom = read_grid('X');
    cin.rdbuf(old_cin);
    assert(read_custom.block == 'X');
    assert(!read_custom.passable(0, 1));

    istringstream walls_in("2 3\n010\n101\n001\n");
    old_cin = cin.rdbuf(walls_in.rdbuf());
    Grid read_walls = read_grid_with_walls();
    cin.rdbuf(old_cin);
    assert(read_walls.H == 2);
    assert(read_walls.W == 3);
    assert((read_walls.v == V<string>{"010", "101"}));
    assert((read_walls.h == V<string>{"001"}));
    assert(read_walls.wall == '1');

    istringstream one_row_walls_in("1 3\n01\n");
    old_cin = cin.rdbuf(one_row_walls_in.rdbuf());
    Grid read_one_row_walls = read_grid_with_walls();
    cin.rdbuf(old_cin);
    assert(read_one_row_walls.H == 1);
    assert(read_one_row_walls.W == 3);
    assert((read_one_row_walls.v == V<string>{"01"}));
    assert(read_one_row_walls.h.empty());

    Grid bfs_grid(3, 3);
    auto bfs_info = grid_bfs(bfs_grid, {0, 0});
    assert(bfs_info.dist[0][0] == 0);
    assert(bfs_info.dist[2][2] == 4);
    assert((bfs_info.parent[0][0] == pii{-1, -1}));
    assert(bfs_info.parent_dir[0][0] == -1);
    assert((restore_grid_path(bfs_info.parent, {0, 0}, {2, 2}) == V<pii>{pii{0, 0}, pii{0, 1}, pii{0, 2}, pii{1, 2}, pii{2, 2}}));
    assert(restore_grid_moves4(bfs_info.parent_dir, {0, 0}, {2, 2}) == "RRDD");
    assert((restore_grid_path(bfs_info.parent, {0, 0}, {0, 0}) == V<pii>{pii{0, 0}}));
    assert(restore_grid_moves4(bfs_info.parent_dir, {0, 0}, {0, 0}).empty());

    Grid blocked(3, 3);
    blocked.cell[0][1] = '#';
    blocked.cell[1][1] = '#';
    blocked.cell[2][1] = '#';
    auto blocked_info = grid_bfs(blocked, {0, 0});
    assert(blocked_info.dist[2][2] == -1);
    assert((blocked_info.parent[2][2] == pii{-1, -1}));
    assert(blocked_info.parent_dir[2][2] == -1);
    assert(restore_grid_path(blocked_info.parent, {0, 0}, {2, 2}).empty());
    assert(restore_grid_moves4(blocked_info.parent_dir, {0, 0}, {2, 2}).empty());

    Grid walled(2, 2);
    walled.v[0][0] = '1';
    walled.h[0][0] = '1';
    auto walled_info = grid_bfs(walled, {0, 0});
    assert(walled_info.dist[0][0] == 0);
    assert(walled_info.dist[0][1] == -1);
    assert(walled_info.dist[1][0] == -1);
    assert(walled_info.dist[1][1] == -1);

    V<V<int>> bad_dirs(2, V<int>(2, -1));
    bad_dirs[0][1] = 9;
    assert(restore_grid_moves4(bad_dirs, {0, 0}, {0, 1}).empty());

    return 0;
}
