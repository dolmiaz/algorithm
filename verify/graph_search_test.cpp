#include "../library/graph_search.hpp"

#include <cassert>
#include <sstream>

int main() {
    Graph empty(0);
    assert(empty.size() == 0);
    auto empty_dfs = dfs_all(empty);
    assert(empty_dfs.comp_cnt == 0);
    assert(empty_dfs.order.empty());
    auto empty_cc = connected_components(empty);
    assert(empty_cc.comp_cnt == 0);
    assert(empty_cc.comp_id.empty());
    assert(empty_cc.comp_size.empty());

    Graph single(1);
    auto single_bfs = bfs(single, 1);
    assert((single_bfs.dist == V<int>{0}));
    assert((single_bfs.parent == V<int>{-1}));
    assert((single_bfs.source == V<int>{0}));
    assert((restore_path(single, single_bfs.parent, 1, 1) == V<int>{1}));

    Graph g(6);
    add_edge(g, 1, 2);
    add_edge(g, 2, 3);
    add_edge(g, 4, 5);

    assert(g.size() == 6);
    assert(g.to_internal(1) == 0);
    assert(g.to_external(0) == 1);
    assert(g.graph[0].size() == 1);
    assert(g.graph[1].size() == 2);
    assert(g.graph[5].empty());

    auto bfs_info = bfs(g, 1);
    assert((bfs_info.dist == V<int>{0, 1, 2, -1, -1, -1}));
    assert(bfs_info.parent[0] == -1);
    assert(bfs_info.parent[1] == 0);
    assert(bfs_info.parent[2] == 1);
    assert((restore_path(g, bfs_info.parent, 1, 3) == V<int>{1, 2, 3}));
    assert(restore_path(g, bfs_info.parent, 1, 6).empty());
    assert((restore_path(g, bfs_info.parent, 1, 1) == V<int>{1}));

    auto multi = bfs_multi(g, V<int>{1, 5});
    assert((multi.dist == V<int>{0, 1, 2, 1, 0, -1}));
    assert(multi.source[0] == 0);
    assert(multi.source[2] == 0);
    assert(multi.source[3] == 4);
    assert(multi.source[4] == 4);
    assert(multi.source[5] == -1);

    auto duplicated_starts = bfs_multi(g, V<int>{1, 1, 3});
    assert((duplicated_starts.dist == V<int>{0, 1, 0, -1, -1, -1}));
    assert(duplicated_starts.source[0] == 0);
    assert(duplicated_starts.source[1] == 0);
    assert(duplicated_starts.source[2] == 2);

    auto cc = connected_components(g);
    assert(cc.comp_cnt == 3);
    assert((cc.comp_size == V<int>{3, 2, 1}));
    assert(cc.comp_id[0] == cc.comp_id[2]);
    assert(cc.comp_id[3] == cc.comp_id[4]);
    assert(cc.comp_id[0] != cc.comp_id[3]);
    assert(cc.comp_id[5] == 2);

    auto dfs_info = dfs_all(g);
    assert(dfs_info.comp_cnt == 3);
    assert(dfs_info.order.size() == 6);
    assert(dfs_info.used == V<int>(6, 1));
    rep(v, 6) {
        assert(dfs_info.tin[v] >= 0);
        assert(dfs_info.tout[v] >= dfs_info.tin[v]);
        assert(dfs_info.comp_id[v] == cc.comp_id[v]);
    }

    Graph directed(3, false, false, false);
    add_edge(directed, 0, 1);
    add_edge(directed, 1, 2);
    assert(directed.graph[0].size() == 1);
    assert(directed.graph[1].size() == 1);
    assert(directed.graph[2].empty());
    assert(directed.to_internal(0) == 0);
    assert(directed.to_external(0) == 0);
    auto directed_from_zero = bfs(directed, 0);
    assert((directed_from_zero.dist == V<int>{0, 1, 2}));
    auto directed_from_two = bfs(directed, 2);
    assert((directed_from_two.dist == V<int>{-1, -1, 0}));
    assert((restore_path(directed, directed_from_zero.parent, 0, 2) == V<int>{0, 1, 2}));
    assert(restore_path(directed, directed_from_two.parent, 2, 0).empty());

    auto directed_multi = bfs_multi(directed, V<int>{0, 2});
    assert((directed_multi.dist == V<int>{0, 1, 0}));
    assert(directed_multi.source[0] == 0);
    assert(directed_multi.source[1] == 0);
    assert(directed_multi.source[2] == 2);

    Graph self_multi(2, true, false, false);
    add_edge(self_multi, 0, 0);
    add_edge(self_multi, 0, 1);
    add_edge(self_multi, 0, 1);
    assert(self_multi.graph[0].size() == 4);
    assert(self_multi.graph[1].size() == 2);
    auto self_multi_bfs = bfs(self_multi, 0);
    assert((self_multi_bfs.dist == V<int>{0, 1}));
    auto self_multi_cc = connected_components(self_multi);
    assert(self_multi_cc.comp_cnt == 1);
    assert((self_multi_cc.comp_size == V<int>{2}));

    istringstream in("1 2 7\n2 3 8\n");
    auto *old_cin = cin.rdbuf(in.rdbuf());
    Graph weighted = read_graph(3, 2, true, true, true);
    cin.rdbuf(old_cin);
    assert(weighted.weighted);
    assert(weighted.undirected);
    assert(weighted.graph[0][0].to == 1);
    assert(weighted.graph[0][0].w == 7);
    assert(weighted.graph[1].size() == 2);

    istringstream directed_weighted_in("1 2 4\n2 3 6\n");
    old_cin = cin.rdbuf(directed_weighted_in.rdbuf());
    Graph directed_weighted = read_graph(3, 2, false, true, true);
    cin.rdbuf(old_cin);
    assert(directed_weighted.weighted);
    assert(!directed_weighted.undirected);
    assert(directed_weighted.one_indexed);
    assert(directed_weighted.graph[0].size() == 1);
    assert(directed_weighted.graph[0][0].to == 1);
    assert(directed_weighted.graph[0][0].w == 4);
    assert(directed_weighted.graph[2].empty());

    istringstream unweighted_in("0 1\n");
    old_cin = cin.rdbuf(unweighted_in.rdbuf());
    Graph unweighted = read_graph(2, 1, false, false, false);
    cin.rdbuf(old_cin);
    assert(!unweighted.weighted);
    assert(!unweighted.undirected);
    assert(!unweighted.one_indexed);
    assert(unweighted.graph[0].size() == 1);
    assert(unweighted.graph[0][0].to == 1);
    assert(unweighted.graph[0][0].w == 1);
    assert(unweighted.graph[1].empty());

    istringstream undirected_zero_in("0 1\n");
    old_cin = cin.rdbuf(undirected_zero_in.rdbuf());
    Graph undirected_zero = read_graph(2, 1, true, false, false);
    cin.rdbuf(old_cin);
    assert(undirected_zero.graph[0].size() == 1);
    assert(undirected_zero.graph[1].size() == 1);
    assert(undirected_zero.graph[0][0].to == 1);
    assert(undirected_zero.graph[1][0].to == 0);

    rep(v, static_cast<int>(dfs_info.order.size())) {
        const int node = dfs_info.order[v];
        assert(0 <= node && node < g.size());
    }
    rep(v, g.size()) {
        if (dfs_info.parent[v] != -1) {
            assert(dfs_info.comp_id[v] == dfs_info.comp_id[dfs_info.parent[v]]);
        }
    }

    return 0;
}
