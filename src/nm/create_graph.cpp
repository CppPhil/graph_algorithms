#include "create_graph.hpp"
#include "identifiers.hpp" // gp::nm::start, gp::nm::b, gp::nm::c, gp::nm::d, gp::nm::e, gp::nm::goal

namespace gp {
namespace nm {
DirectedGraph<std::string, std::nullptr_t, int, LengthEdgeData<std::size_t>>
createGraph()
{
    DirectedGraph<std::string, std::nullptr_t, int, LengthEdgeData<std::size_t>>
        g{};

    (void)g.addVertex(start, nullptr);
    (void)g.addVertex(b, nullptr);
    (void)g.addVertex(c, nullptr);
    (void)g.addVertex(d, nullptr);
    (void)g.addVertex(e, nullptr);
    (void)g.addVertex(goal, nullptr);

    (void)g.addEdge(1, start, b, LengthEdgeData<std::size_t>{5});
    (void)g.addEdge(2, start, c, LengthEdgeData<std::size_t>{5});
    (void)g.addEdge(3, b, d, LengthEdgeData<std::size_t>{6});
    (void)g.addEdge(4, c, d, LengthEdgeData<std::size_t>{5});
    (void)g.addEdge(5, d, e, LengthEdgeData<std::size_t>{5});
    (void)g.addEdge(6, e, goal, LengthEdgeData<std::size_t>{5});

    return g;
}
} // namespace nm
} // namespace gp