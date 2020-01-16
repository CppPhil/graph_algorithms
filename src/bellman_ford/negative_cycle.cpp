#include "negative_cycle.hpp"

namespace gp {
namespace bellman_ford {
NegativeCycle::graph_type NegativeCycle::create()
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

    edge("a", "b", 10);
    edge("b", "c", 1);
    edge("c", "e", 3);
    edge("d", "b", 4);
    edge("e", "d", -10);
    edge("e", "f", 22);

    return g;
}
} // namespace bellman_ford
} // namespace gp
