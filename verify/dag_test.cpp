#include "../library/dag.hpp"

namespace {
bool valid_topological_order(const Graph &g, const V<int> &order) {
    if (static_cast<int>(order.size()) != g.size()) return false;

    V<int> pos(g.size(), -1);
    rep(i, order.size()) {
        const int v = order[i];
        if (v < 0 || v >= g.size()) return false;
        if (pos[v] != -1) return false;
        pos[v] = i;
    }

    rep(v, g.size()) {
        for (const auto &e : g.graph[v]) {
            if (pos[v] >= pos[e.to]) return false;
        }
    }

    return true;
}

bool valid_directed_cycle(const Graph &g, const V<int> &cycle) {
    if (cycle.empty()) return false;

    rep(i, cycle.size()) {
        const int from = cycle[i];
        const int to = cycle[(i + 1) % cycle.size()];
        bool found = false;

        for (const auto &e : g.graph[from]) {
            if (e.to == to) {
                found = true;
                break;
            }
        }

        if (!found) return false;
    }

    return true;
}
}  // namespace

int main() {
    Graph empty(0, false, false, false);
    TopologicalSort empty_topo(empty);
    assert(empty_topo.is_dag);
    assert(empty_topo.order.empty());
    assert(empty_topo.indeg.empty());
    SCC empty_scc(empty);
    assert(empty_scc.comp_cnt == 0);
    assert(empty_scc.comp_id.empty());
    assert(empty_scc.groups.empty());
    DirectedCycle empty_cycle(empty);
    assert(!empty_cycle.has_cycle);
    assert(empty_cycle.cycle.empty());

    DAGLongestPath<> empty_longest(empty);
    assert(empty_longest.is_dag);
    assert(empty_longest.dist.empty());
    assert(empty_longest.parent.empty());

    Graph dag(4, false, false, false);
    dag.add_edge(0, 1);
    dag.add_edge(0, 2);
    dag.add_edge(1, 3);
    dag.add_edge(2, 3);

    TopologicalSort topo(dag);
    assert(topo.is_dag);
    assert(valid_topological_order(dag, topo.order));
    assert((topo.indeg == V<int>{0, 1, 1, 2}));
    assert(topo.order_external() == topo.order);

    DirectedCycle dag_cycle(dag);
    assert(!dag_cycle.has_cycle);
    assert(dag_cycle.cycle.empty());

    Graph one_indexed_dag(3, false, false, true);
    one_indexed_dag.add_edge(1, 2);
    one_indexed_dag.add_edge(1, 3);
    TopologicalSort one_indexed_topo(one_indexed_dag);
    assert(one_indexed_topo.is_dag);
    assert(valid_topological_order(one_indexed_dag, one_indexed_topo.order));
    assert((one_indexed_topo.order_external() == V<int>{1, 2, 3}));

    Graph cycle(3, false, false, false);
    cycle.add_edge(0, 1);
    cycle.add_edge(1, 2);
    cycle.add_edge(2, 0);
    topo.build(cycle);
    assert(!topo.is_dag);
    assert(topo.order.empty());
    assert((topo.indeg == V<int>{1, 1, 1}));

    DirectedCycle directed_cycle(cycle);
    assert(directed_cycle.has_cycle);
    assert(valid_directed_cycle(cycle, directed_cycle.cycle));

    topo.build(dag);
    assert(topo.is_dag);
    assert(valid_topological_order(dag, topo.order));

    Graph self_loop(2, false, false, false);
    self_loop.add_edge(0, 0);
    DirectedCycle self_loop_cycle(self_loop);
    assert(self_loop_cycle.has_cycle);
    assert((self_loop_cycle.cycle == V<int>{0}));

    Graph one_indexed_cycle(3, false, false, true);
    one_indexed_cycle.add_edge(1, 2);
    one_indexed_cycle.add_edge(2, 3);
    one_indexed_cycle.add_edge(3, 1);
    DirectedCycle one_indexed_directed_cycle(one_indexed_cycle);
    assert(one_indexed_directed_cycle.has_cycle);
    assert((one_indexed_directed_cycle.cycle_external() == V<int>{2, 3, 1}));

    Graph scc_graph(6, false, false, false);
    scc_graph.add_edge(0, 1);
    scc_graph.add_edge(1, 2);
    scc_graph.add_edge(2, 0);
    scc_graph.add_edge(2, 3);
    scc_graph.add_edge(3, 4);
    scc_graph.add_edge(4, 3);

    SCC scc(scc_graph);
    assert(scc.comp_cnt == 3);
    assert(scc.same(0, 2));
    assert(scc.same(3, 4));
    assert(!scc.same(0, 3));
    assert(!scc.same(0, 5));
    assert(scc.size(0) == 3);
    assert(scc.size(3) == 2);
    assert(scc.size(5) == 1);
    assert(scc.id(0) == scc.id(1));
    assert(scc.id(1) == scc.id(2));
    assert(scc.id(3) == scc.id(4));

    V<int> group_sizes;
    for (const auto &group : scc.groups) {
        group_sizes.push_back(static_cast<int>(group.size()));
    }
    sort(all(group_sizes));
    assert((group_sizes == V<int>{1, 2, 3}));

    Graph one_indexed_scc_graph(4, false, false, true);
    one_indexed_scc_graph.add_edge(1, 2);
    one_indexed_scc_graph.add_edge(2, 1);
    one_indexed_scc_graph.add_edge(2, 3);
    one_indexed_scc_graph.add_edge(3, 4);
    one_indexed_scc_graph.add_edge(4, 3);

    SCC one_indexed_scc(one_indexed_scc_graph);
    assert(one_indexed_scc.comp_cnt == 2);
    assert(one_indexed_scc.same(1, 2));
    assert(one_indexed_scc.same(3, 4));
    assert(!one_indexed_scc.same(1, 3));
    assert(one_indexed_scc.size(1) == 2);
    assert(one_indexed_scc.size(3) == 2);

    Graph weighted_dag(5, false, true, false);
    weighted_dag.add_edge(0, 1, 2);
    weighted_dag.add_edge(0, 2, 5);
    weighted_dag.add_edge(1, 3, 4);
    weighted_dag.add_edge(2, 3, 1);
    weighted_dag.add_edge(3, 4, 3);

    DAGLongestPath<> longest(weighted_dag, 0);
    assert(longest.is_dag);
    assert(longest.reachable(4));
    assert(longest.distance(4) == 9);
    assert((longest.path(4) == V<int>{0, 1, 3, 4}));

    DAGLongestPath<> longest_from_two(weighted_dag, 2);
    assert(longest_from_two.is_dag);
    assert(!longest_from_two.reachable(1));
    assert(longest_from_two.distance(4) == 4);
    assert((longest_from_two.path(4) == V<int>{2, 3, 4}));

    DAGLongestPath<> longest_all(weighted_dag);
    assert(longest_all.is_dag);
    assert(longest_all.distance(4) == 9);
    assert((longest_all.path(4) == V<int>{0, 1, 3, 4}));

    Graph negative_dag(3, false, true, false);
    negative_dag.add_edge(0, 1, -5);
    negative_dag.add_edge(1, 2, -2);
    DAGLongestPath<> negative_longest(negative_dag, 0);
    assert(negative_longest.is_dag);
    assert(negative_longest.reachable(2));
    assert(negative_longest.distance(2) == -7);
    assert((negative_longest.path(2) == V<int>{0, 1, 2}));

    DAGLongestPath<> cyclic_longest(cycle, 0);
    assert(!cyclic_longest.is_dag);
    assert(cyclic_longest.order.empty());

    return 0;
}
