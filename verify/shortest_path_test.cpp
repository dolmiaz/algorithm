#include "../library/shortest_path.hpp"

#include <cassert>

int main() {
    Graph single(1, true, true, true);
    Dijkstra single_info(single, 1);
    assert((single_info.dist == V<ll>{0}));
    assert((single_info.parent == V<int>{-1}));
    assert(single_info.distance(1) == 0);
    assert(single_info.reachable(1));
    assert((single_info.path(1) == V<int>{1}));

    Graph g(5, false, true, true);
    g.add_edge(1, 2, 2);
    g.add_edge(1, 3, 5);
    g.add_edge(2, 3, 1);
    g.add_edge(2, 4, 4);
    g.add_edge(3, 4, 1);

    Dijkstra info(g, 1);
    assert((info.dist == V<ll>{0, 2, 3, 4, INF_L}));
    assert(info.parent[0] == -1);
    assert(info.parent[1] == 0);
    assert(info.parent[2] == 1);
    assert(info.parent[3] == 2);
    assert(info.parent[4] == -1);
    assert(info.distance(4) == 4);
    assert(!info.reachable(5));
    assert((info.path(4) == V<int>{1, 2, 3, 4}));
    assert(info.path(5).empty());
    assert((info.path(1) == V<int>{1}));

    Graph isolated_start(3, false, true, true);
    isolated_start.add_edge(2, 3, 1);
    Dijkstra isolated_info(isolated_start, 1);
    assert((isolated_info.dist == V<ll>{0, INF_L, INF_L}));
    assert((isolated_info.parent == V<int>{-1, -1, -1}));

    Graph tie(4, false, true, true);
    tie.add_edge(1, 2, 1);
    tie.add_edge(1, 3, 1);
    tie.add_edge(2, 4, 1);
    tie.add_edge(3, 4, 1);
    Dijkstra tie_info(tie, 1);
    assert((tie_info.dist == V<ll>{0, 1, 1, 2}));
    assert(tie_info.parent[3] == 1 || tie_info.parent[3] == 2);

    Graph multi_edge(3, false, true, true);
    multi_edge.add_edge(1, 2, 10);
    multi_edge.add_edge(1, 2, 3);
    multi_edge.add_edge(2, 3, 4);
    Dijkstra multi_edge_info(multi_edge, 1);
    assert((multi_edge_info.dist == V<ll>{0, 3, 7}));
    assert((multi_edge_info.path(3) == V<int>{1, 2, 3}));

    Graph zero_weight(3, false, true, true);
    zero_weight.add_edge(1, 2, 0);
    zero_weight.add_edge(2, 3, 0);
    zero_weight.add_edge(1, 3, 5);
    Dijkstra zero_weight_info(zero_weight, 1);
    assert((zero_weight_info.dist == V<ll>{0, 0, 0}));
    assert((zero_weight_info.path(3) == V<int>{1, 2, 3}));

    Graph undirected(3, true, true, true);
    undirected.add_edge(1, 2, 5);
    undirected.add_edge(2, 3, 7);
    Dijkstra undirected_info(undirected, 3);
    assert((undirected_info.dist == V<ll>{12, 7, 0}));
    assert((undirected_info.path(1) == V<int>{3, 2, 1}));

    Graph zero_indexed(4, true, true, false);
    zero_indexed.add_edge(0, 1, 10);
    zero_indexed.add_edge(0, 2, 1);
    zero_indexed.add_edge(2, 1, 2);
    zero_indexed.add_edge(1, 3, 3);

    Dijkstra zinfo(zero_indexed, 0);
    assert((zinfo.dist == V<ll>{0, 3, 1, 6}));
    assert((zinfo.path(3) == V<int>{0, 2, 1, 3}));
    assert((zinfo.path(0) == V<int>{0}));

    Dijkstra rebuilt;
    rebuilt.build(zero_indexed, 0);
    assert(rebuilt.distance(3) == 6);

    return 0;
}
