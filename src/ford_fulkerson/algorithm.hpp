#ifndef INCG_GP_FORD_FULKERSON_ALGORITHM_HPP
#define INCG_GP_FORD_FULKERSON_ALGORITHM_HPP
#include "../directed_graph.hpp"    // gp::DirectedGraph
#include "breadth_first_search.hpp" // gp::ford_fulkerson::breadthFirstSearch, ...
#include <algorithm>                // std::min
#include <cstdint>                  // std::int32_t
#include <utility>                  // std::move

namespace gp {
namespace ford_fulkerson {
template<typename VertexIdentifier>
struct Result {
    Result(
        std::int32_t p_maxFlow,
        std::unordered_map<VertexPair<VertexIdentifier>, std::int32_t>&&
            p_flow) noexcept
        : maxFlow{p_maxFlow}, flow{std::move(p_flow)}
    {
    }

    std::int32_t                                                   maxFlow;
    std::unordered_map<VertexPair<VertexIdentifier>, std::int32_t> flow;
};

template<
    typename VertexIdentifier,
    typename VertexData,
    typename EdgeIdentifier,
    typename EdgeData>
Result<VertexIdentifier> algorithm(
    const DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData>&
                            graph,
    const VertexIdentifier& source,
    const VertexIdentifier& sink)
{
    using graph_type
        = DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData>;
    using edge_type = typename graph_type::edge_type;

    // Initialize empty flow.
    std::int32_t maxFlow{INT32_C(0)};
    std::unordered_map<VertexPair<VertexIdentifier>, std::int32_t> flow{};
    std::unordered_map<VertexPair<VertexIdentifier>, std::int32_t> capacity{};

    for (const auto& vertex : graph.vertices()) {
        const VertexIdentifier& v{vertex.identifier()};

        for (const auto& vert : graph.vertices()) {
            const VertexIdentifier& otherVert{vert.identifier()};
            flow[VertexPair{v, otherVert}]     = INT32_C(0);
            capacity[VertexPair{v, otherVert}] = INT32_C(0);
        }
    }

    // Set up capacity.
    for (const edge_type& edge : graph.edges()) {
        const VertexIdentifier& edgeSource{edge.source()};
        const VertexIdentifier& edgeTarget{edge.target()};
        capacity[VertexPair{edgeSource, edgeTarget}] = edge.data().capacity();
    }

    // While there exists an augmenting path,
    // increment the flow along this path.
    for (tl::optional<std::unordered_map<
             VertexIdentifier,
             tl::optional<VertexIdentifier>>> pred{tl::nullopt};
         (pred = breadthFirstSearch(graph, source, sink, capacity, flow))
             .has_value();) {
        // Determine the amount by which we can increment the flow.
        std::int32_t increment{INT32_MAX};

        for (VertexIdentifier u{sink}; (*pred)[u].has_value();
             u = (*pred)[u].value()) {
            increment = std::min(
                increment,
                capacity[VertexPair{(*pred)[u].value(), u}]
                    - flow[VertexPair{(*pred)[u].value(), u}]);
        }

        // Now increment the flow.
        for (VertexIdentifier u{sink}; (*pred)[u].has_value();
             u = (*pred)[u].value()) {
            flow[VertexPair{(*pred)[u].value(), u}] += increment;
            flow[VertexPair{u, (*pred)[u].value()}] -= increment;
        }

        maxFlow += increment;
    }

    // No augmenting path anymore. We are done.
    return Result<VertexIdentifier>{maxFlow, std::move(flow)};
}
} // namespace ford_fulkerson
} // namespace gp
#endif // INCG_GP_FORD_FULKERSON_ALGORITHM_HPP
