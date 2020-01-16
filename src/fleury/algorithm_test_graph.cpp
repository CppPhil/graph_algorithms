#include "algorithm_test_graph.hpp"

namespace gp {
namespace fleury {
using namespace algorithm_test_graph_types;

graph_type algorithmTestGraph()
{
    graph_type g{};

    const auto v = [&g](vertex_identifier identifier) {
        (void)g.addVertex(identifier, nullptr);
    };

    const auto addEdgeImpl = [&g](
                                 edge_identifier   identifier,
                                 vertex_identifier src,
                                 vertex_identifier target) {
        (void)g.addEdge(identifier, src, target, nullptr);
    };

    const auto e
        = [&addEdgeImpl](
              edge_identifier fwd, vertex_identifier v1, vertex_identifier v2) {
              addEdgeImpl(fwd, v1, v2);
              addEdgeImpl(-fwd, v2, v1);
          };

    for (char c{'A'}; c <= 'I'; ++c) { v(c); }

    e(1, 'A', 'B');
    e(2, 'A', 'C');
    e(3, 'B', 'D');
    e(4, 'D', 'E');
    e(5, 'B', 'E');
    e(6, 'C', 'E');
    e(7, 'C', 'F');
    e(8, 'E', 'F');
    e(9, 'E', 'H');
    e(10, 'E', 'G');
    e(11, 'H', 'I');
    e(12, 'G', 'I');
    e(13, 'C', 'B');

    return g;
}
} // namespace fleury
} // namespace gp
