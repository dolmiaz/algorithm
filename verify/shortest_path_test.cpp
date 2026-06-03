#include "../library/shortest_path.hpp"

#include <cassert>

int main() {
    Graph single(1, true, true, true);
    auto single_info = dijkstra(single, 1);
    assert((single_info.dist == V<ll>{0}));
    assert((single_info.parent == V<int>{-1}));
    assert((restore_shortest_path(single, single_info.parent, 1, 1) == V<int>{1}));

    Graph g(5, false, true, true);
    add_edge(g, 1, 2, 2);
    add_edge(g, 1, 3, 5);
    add_edge(g, 2, 3, 1);
    add_edge(g, 2, 4, 4);
    add_edge(g, 3, 4, 1);

    auto info = dijkstra(g, 1);
    assert((info.dist == V<ll>{0, 2, 3, 4, INF_L}));
    assert(info.parent[0] == -1);
    assert(info.parent[1] == 0);
    assert(info.parent[2] == 1);
    assert(info.parent[3] == 2);
    assert(info.parent[4] == -1);
    assert((restore_shortest_path(g, info.parent, 1, 4) == V<int>{1, 2, 3, 4}));
    assert(restore_shortest_path(g, info.parent, 1, 5).empty());
    assert((restore_shortest_path(g, info.parent, 1, 1) == V<int>{1}));

    Graph isolated_start(3, false, true, true);
    add_edge(isolated_start, 2, 3, 1);
    auto isolated_info = dijkstra(isolated_start, 1);
    assert((isolated_info.dist == V<ll>{0, INF_L, INF_L}));
    assert((isolated_info.parent == V<int>{-1, -1, -1}));

    Graph tie(4, false, true, true);
    add_edge(tie, 1, 2, 1);
    add_edge(tie, 1, 3, 1);
    add_edge(tie, 2, 4, 1);
    add_edge(tie, 3, 4, 1);
    auto tie_info = dijkstra(tie, 1);
    assert((tie_info.dist == V<ll>{0, 1, 1, 2}));
    assert(tie_info.parent[3] == 1 || tie_info.parent[3] == 2);

    Graph multi_edge(3, false, true, true);
    add_edge(multi_edge, 1, 2, 10);
    add_edge(multi_edge, 1, 2, 3);
    add_edge(multi_edge, 2, 3, 4);
    auto multi_edge_info = dijkstra(multi_edge, 1);
    assert((multi_edge_info.dist == V<ll>{0, 3, 7}));
    assert((restore_shortest_path(multi_edge, multi_edge_info.parent, 1, 3) == V<int>{1, 2, 3}));

    Graph zero_weight(3, false, true, true);
    add_edge(zero_weight, 1, 2, 0);
    add_edge(zero_weight, 2, 3, 0);
    add_edge(zero_weight, 1, 3, 5);
    auto zero_weight_info = dijkstra(zero_weight, 1);
    assert((zero_weight_info.dist == V<ll>{0, 0, 0}));
    assert((restore_shortest_path(zero_weight, zero_weight_info.parent, 1, 3) == V<int>{1, 2, 3}));

    Graph undirected(3, true, true, true);
    add_edge(undirected, 1, 2, 5);
    add_edge(undirected, 2, 3, 7);
    auto undirected_info = dijkstra(undirected, 3);
    assert((undirected_info.dist == V<ll>{12, 7, 0}));
    assert((restore_shortest_path(undirected, undirected_info.parent, 3, 1) == V<int>{3, 2, 1}));

    Graph zero_indexed(4, true, true, false);
    add_edge(zero_indexed, 0, 1, 10);
    add_edge(zero_indexed, 0, 2, 1);
    add_edge(zero_indexed, 2, 1, 2);
    add_edge(zero_indexed, 1, 3, 3);

    auto zinfo = dijkstra(zero_indexed, 0);
    assert((zinfo.dist == V<ll>{0, 3, 1, 6}));
    assert((restore_shortest_path(zero_indexed, zinfo.parent, 0, 3) == V<int>{0, 2, 1, 3}));
    assert((restore_shortest_path(zero_indexed, zinfo.parent, 0, 0) == V<int>{0}));

    V<int> broken_parent = {-1, -1, 1};
    assert(restore_shortest_path(zero_indexed, broken_parent, 0, 2).empty());

    return 0;
}
