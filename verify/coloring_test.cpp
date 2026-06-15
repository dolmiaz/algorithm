#include "../library/coloring.hpp"

int main() {
    Graph empty(0, false, false, false);
    KColoring empty_coloring(empty, 0);
    assert(empty_coloring.found);
    assert(empty_coloring.valid());
    assert(empty_coloring.color.empty());

    Graph triangle(3, true, false, false);
    triangle.add_edge(0, 1);
    triangle.add_edge(1, 2);
    triangle.add_edge(2, 0);

    KColoring triangle_two(triangle, 2);
    assert(!triangle_two.found);

    KColoring triangle_three(triangle, 3);
    assert(triangle_three.found);
    assert(triangle_three.valid());
    assert(triangle_three.min_colors(triangle) == 3);
    assert(triangle_three.found);
    assert(triangle_three.valid());

    Graph path(4, true, false, false);
    path.add_edge(0, 1);
    path.add_edge(1, 2);
    path.add_edge(2, 3);

    KColoring path_coloring;
    assert(path_coloring.build(path, 2));
    assert(path_coloring.valid());
    assert(path_coloring.min_colors(path) == 2);

    Graph isolated(3, false, false, false);
    KColoring isolated_coloring;
    assert(isolated_coloring.min_colors(isolated) == 1);
    assert(isolated_coloring.valid());

    Graph directed_constraint(3, false, false, false);
    directed_constraint.add_edge(0, 1);
    directed_constraint.add_edge(1, 2);

    KColoring directed_one(directed_constraint, 1);
    assert(!directed_one.found);

    KColoring directed_two(directed_constraint, 2);
    assert(directed_two.found);
    assert(directed_two.valid());

    Graph self_loop(2, false, false, false);
    self_loop.add_edge(0, 0);

    KColoring self_loop_coloring(self_loop, 2);
    assert(!self_loop_coloring.found);

    Graph one_indexed_cycle(4, true, false, true);
    one_indexed_cycle.add_edge(1, 2);
    one_indexed_cycle.add_edge(2, 3);
    one_indexed_cycle.add_edge(3, 4);
    one_indexed_cycle.add_edge(4, 1);

    KColoring one_indexed_coloring(one_indexed_cycle, 2);
    assert(one_indexed_coloring.found);
    assert(one_indexed_coloring.valid());

    return 0;
}
