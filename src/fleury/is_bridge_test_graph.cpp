#include "is_bridge_test_graph.hpp"

namespace gp {
namespace fleury {
using namespace is_bridge_test_graph_types;

graph_type isBridgeTestGraph()
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
    e(3, 'B', 'C');
    e(4, 'C', 'D');
    e(5, 'D', 'E');
    e(6, 'E', 'F');
    e(7, 'E', 'G');
    e(8, 'F', 'H');
    e(9, 'G', 'H');

    return g;
}
} // namespace fleury
} // namespace gp
