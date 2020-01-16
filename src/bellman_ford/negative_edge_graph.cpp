#include "negative_edge_graph.hpp"
#include <cstdint> // std::int32_t
#include <string>  // std::string
#include <utility> // std::move

namespace gp {
namespace bellman_ford {
NegativeEdgeGraph::graph_type NegativeEdgeGraph::create()
{
    graph_type g{};

    const auto vertex = [&g](std::string&& identifier) {
        (void)g.addVertex(std::move(identifier), nullptr);
    };

    auto edge = [&g, i = 0](
                    const auto&  source,
                    const auto&  target,
                    std::int32_t weight) mutable {
        (void)g.addEdge(
            i, source, target, LengthEdgeData<std::int32_t>{weight});
        i++;
    };

    vertex("a");
    vertex("b");
    vertex("c");
    vertex("d");
    vertex("e");
    vertex("f");

    edge("a", "c", 20);
    edge("a", "b", 10);
    edge("b", "e", 10);
    edge("b", "d", 50);
    edge("c", "e", 33);
    edge("c", "d", 20);
    edge("d", "e", -20);
    edge("d", "f", -2);
    edge("e", "f", 1);

    return g;
}
} // namespace bellman_ford
} // namespace gp
