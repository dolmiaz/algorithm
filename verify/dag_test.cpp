#include "../library/dag.h"

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
}  // namespace

int main() {
    Graph empty(0, false, false, false);
    TopologicalSort empty_topo(empty);
    assert(empty_topo.is_dag);
    assert(empty_topo.order.empty());
    assert(empty_topo.indeg.empty());

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

    topo.build(dag);
    assert(topo.is_dag);
    assert(valid_topological_order(dag, topo.order));

    return 0;
}
