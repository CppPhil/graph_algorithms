#include "algorithm_test_graph.hpp"

namespace gp {
namespace hierholzer {
using namespace algorithm_test_graph_types;

graph_type algorithmTestGraph()
{
    graph_type g{};

    const auto v = [&g](vertex_identifier vertex) {
        (void)g.addVertex(vertex, nullptr);
    };

    const auto e = [&g](vertex_identifier src, vertex_identifier dst) {
        (void)g.addEdge((src * 10) + dst, src, dst, nullptr);
        (void)g.addEdge((dst * 10) + src, dst, src, nullptr);
    };

    for (vertex_identifier i{1}; i <= 9; ++i) { v(i); }

    e(1, 2);
    e(1, 3);
    e(2, 3);
    e(2, 4);
    e(2, 5);
    e(3, 4);
    e(3, 8);
    e(5, 6);
    e(5, 7);
    e(5, 9);
    e(6, 7);
    e(8, 9);

    return g;
}
} // namespace hierholzer
} // namespace gp
