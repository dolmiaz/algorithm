#include "../library/graph_search.hpp"

#include <cassert>
#include <sstream>

int main() {
    Graph empty(0);
    assert(empty.size() == 0);
    GraphDFS empty_dfs(empty);
    assert(empty_dfs.comp_cnt == 0);
    assert(empty_dfs.order.empty());
    assert(empty_dfs.post_order.empty());
    ConnectedComponents empty_cc(empty);
    assert(empty_cc.count() == 0);
    assert(empty_cc.comp_id.empty());
    assert(empty_cc.comp_size.empty());

    Graph single(1);
    GraphBFS single_bfs(single, 1);
    assert((single_bfs.dist == V<int>{0}));
    assert((single_bfs.parent == V<int>{-1}));
    assert((single_bfs.source == V<int>{0}));
    assert((single_bfs.path(1) == V<int>{1}));

    Graph g(6);
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    g.add_edge(4, 5);

    assert(g.size() == 6);
    assert(g.to_internal(1) == 0);
    assert(g.to_external(0) == 1);
    assert(g.graph[0].size() == 1);
    assert(g.graph[1].size() == 2);
    assert(g.graph[5].empty());

    GraphBFS bfs_info(g, 1);
    assert((bfs_info.dist == V<int>{0, 1, 2, -1, -1, -1}));
    assert(bfs_info.parent[0] == -1);
    assert(bfs_info.parent[1] == 0);
    assert(bfs_info.parent[2] == 1);
    assert((bfs_info.path(3) == V<int>{1, 2, 3}));
    assert(bfs_info.path(6).empty());
    assert((bfs_info.path(1) == V<int>{1}));

    GraphBFS multi;
    multi.build_multi(g, V<int>{1, 5});
    assert((multi.dist == V<int>{0, 1, 2, 1, 0, -1}));
    assert(multi.source[0] == 0);
    assert(multi.source[2] == 0);
    assert(multi.source[3] == 4);
    assert(multi.source[4] == 4);
    assert(multi.source[5] == -1);
    assert((multi.path(4) == V<int>{5, 4}));

    GraphBFS duplicated_starts;
    duplicated_starts.build_multi(g, V<int>{1, 1, 3});
    assert((duplicated_starts.dist == V<int>{0, 1, 0, -1, -1, -1}));
    assert(duplicated_starts.source[0] == 0);
    assert(duplicated_starts.source[1] == 0);
    assert(duplicated_starts.source[2] == 2);

    ConnectedComponents cc(g);
    assert(cc.count() == 3);
    assert((cc.comp_size == V<int>{3, 2, 1}));
    assert(cc.same(1, 3));
    assert(cc.same(4, 5));
    assert(!cc.same(1, 4));
    assert(cc.size(1) == 3);
    assert(cc.size(6) == 1);
    assert(cc.comp_id[5] == 2);

    GraphDFS dfs_info(g);
    assert(dfs_info.comp_cnt == 3);
    assert(dfs_info.order.size() == 6);
    assert(dfs_info.post_order.size() == 6);
    assert((dfs_info.post_order == V<int>{2, 1, 0, 4, 3, 5}));
    assert(dfs_info.used == V<int>(6, 1));
    rep(v, 6) {
        assert(dfs_info.tin[v] >= 0);
        assert(dfs_info.tout[v] >= dfs_info.tin[v]);
        assert(dfs_info.comp_id[v] == cc.comp_id[v]);
    }

    GraphDFS dfs_from_five(g, 5);
    assert(dfs_from_five.comp_cnt == 1);
    assert((dfs_from_five.used == V<int>{0, 0, 0, 1, 1, 0}));
    assert((dfs_from_five.order == V<int>{4, 3}));
    assert((dfs_from_five.post_order == V<int>{3, 4}));
    assert((dfs_from_five.comp_id == V<int>{-1, -1, -1, 0, 0, -1}));

    GraphDFS dfs_multi;
    dfs_multi.build_multi(g, V<int>{5, 1, 5});
    assert(dfs_multi.comp_cnt == 2);
    assert((dfs_multi.used == V<int>{1, 1, 1, 1, 1, 0}));
    assert((dfs_multi.order == V<int>{4, 3, 0, 1, 2}));
    assert((dfs_multi.post_order == V<int>{3, 4, 2, 1, 0}));
    assert((dfs_multi.comp_id == V<int>{1, 1, 1, 0, 0, -1}));

    GraphDFS dfs_ordered_all;
    dfs_ordered_all.build_all(g, V<int>{5, 1});
    assert(dfs_ordered_all.comp_cnt == 3);
    assert((dfs_ordered_all.used == V<int>(6, 1)));
    assert((dfs_ordered_all.order == V<int>{4, 3, 0, 1, 2, 5}));
    assert((dfs_ordered_all.post_order == V<int>{3, 4, 2, 1, 0, 5}));
    assert((dfs_ordered_all.comp_id == V<int>{1, 1, 1, 0, 0, 2}));

    Graph directed(3, false, false, false);
    directed.add_edge(0, 1);
    directed.add_edge(1, 2);
    assert(directed.graph[0].size() == 1);
    assert(directed.graph[1].size() == 1);
    assert(directed.graph[2].empty());
    assert(directed.to_internal(0) == 0);
    assert(directed.to_external(0) == 0);
    GraphBFS directed_from_zero(directed, 0);
    assert((directed_from_zero.dist == V<int>{0, 1, 2}));
    GraphBFS directed_from_two(directed, 2);
    assert((directed_from_two.dist == V<int>{-1, -1, 0}));
    assert((directed_from_zero.path(2) == V<int>{0, 1, 2}));
    assert(directed_from_two.path(0).empty());

    GraphBFS directed_multi;
    directed_multi.build_multi(directed, V<int>{0, 2});
    assert((directed_multi.dist == V<int>{0, 1, 0}));
    assert(directed_multi.source[0] == 0);
    assert(directed_multi.source[1] == 0);
    assert(directed_multi.source[2] == 2);

    Graph self_multi(2, true, false, false);
    self_multi.add_edge(0, 0);
    self_multi.add_edge(0, 1);
    self_multi.add_edge(0, 1);
    assert(self_multi.graph[0].size() == 4);
    assert(self_multi.graph[1].size() == 2);
    GraphBFS self_multi_bfs(self_multi, 0);
    assert((self_multi_bfs.dist == V<int>{0, 1}));
    ConnectedComponents self_multi_cc(self_multi);
    assert(self_multi_cc.count() == 1);
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
    rep(v, static_cast<int>(dfs_info.post_order.size())) {
        const int node = dfs_info.post_order[v];
        assert(0 <= node && node < g.size());
    }
    rep(v, g.size()) {
        if (dfs_info.parent[v] != -1) {
            assert(dfs_info.comp_id[v] == dfs_info.comp_id[dfs_info.parent[v]]);
        }
    }

    return 0;
}
