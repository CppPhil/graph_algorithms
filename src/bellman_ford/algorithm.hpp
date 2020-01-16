#ifndef INCG_GP_BELLMAN_FORD_ALGORITHM_HPP
#define INCG_GP_BELLMAN_FORD_ALGORITHM_HPP
#include "../directed_graph.hpp" // gp::DirectedGraph
#include "../shortest_paths.hpp" // gp::ShortestPaths
#include <cstddef>               // std::size_t
#include <cstdint>               // std::int32_t, std::int64_t, INT32_MAX
#include <pl/except.hpp>         // PL_THROW_WITH_SOURCE_INFO
#include <pl/invoke.hpp>         // pl::invoke
#include <pl/size_t.hpp>   // pl::literals::integer_literals::operator""_zu
#include <stdexcept>       // std::runtime_error
#include <tl/optional.hpp> // tl::optional, tl::nullopt
#include <unordered_map>   // std::unordered_map
#include <utility>         // std::move

namespace gp {
namespace bellman_ford {
/*!
 * \brief Implements the bellman ford algorithm.
 * \tparam VertexIdentifier The type of the unique identifiers used for the
 *                          vertices in the directed graph to operate on.
 * \tparam VertexData The type of the data that is stored on a vertex.
 * \tparam EdgeIdentifier The type of the unique identifiers used for the
 *                        edges in the directed graph to operate on.
 * \tparam EdgeData The type of the data that is stored on an edge.
 * \tparam LengthInvocable The type of the unary length invocable.
 * \param graph The directed graph to find the shortest paths in.
 * \param source The source vertex to use.
 * \param lengthInvocable The unary length invocable object.
 * \return The result object containing the shortest paths from 'source'
 *         to all the vertices in the graph given.
 * \note Unlike Dijkstra's algorithm this algorithm supports negatively
 *       weighted edges.
 * \throws std::runtime_error if there is a negative-weight cycle in the graph
 *                            given.
 **/
template<
    typename VertexIdentifier,
    typename VertexData,
    typename EdgeIdentifier,
    typename EdgeData,
    typename LengthInvocable>
ShortestPaths<VertexIdentifier, std::int32_t> algorithm(
    const DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData>&
                     graph,
    VertexIdentifier source,
    LengthInvocable  lengthInvocable)
{
    using namespace pl::literals::integer_literals;

    using graph_type
        = DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData>;
    using vertex_type = typename graph_type::vertex_type;
    using edge_type   = typename graph_type::edge_type;

    constexpr std::int32_t               infinity{INT32_MAX};
    const tl::optional<VertexIdentifier> undefined{tl::nullopt};

    std::unordered_map<VertexIdentifier, std::int32_t> distance{};
    std::unordered_map<VertexIdentifier, tl::optional<VertexIdentifier>>
        predecessor{};

    const std::vector<vertex_type>& vertices{graph.vertices()};
    const std::vector<edge_type>&   edges{graph.edges()};

    // Initialize graph
    for (const vertex_type& vertex : vertices) {
        const VertexIdentifier& v{vertex.identifier()};

        distance[v]
            = infinity; // Initialize the distance to all vertices to infinity
        predecessor[v] = undefined; // And having a null predecessor
    }

    distance[source] = 0; // The distance from the source to itself is zero

    // Relax edges repeatedly
    for (std::size_t i{1_zu}; i <= (vertices.size() - 1_zu); ++i) {
        for (const edge_type& edge : edges) {
            const VertexIdentifier& u{edge.source()};
            const VertexIdentifier& v{edge.target()};
            const std::int32_t      w{
                static_cast<std::int32_t>(std::invoke(lengthInvocable, edge))};

            if ((static_cast<std::int64_t>(distance[u]) + w) < distance[v]) {
                distance[v]    = distance[u] + w;
                predecessor[v] = u;
            }
        }
    }

    // Check for negative-weight cycles
    for (const edge_type& edge : edges) {
        const VertexIdentifier& u{edge.source()};
        const VertexIdentifier& v{edge.target()};
        const std::int32_t      w{
            static_cast<std::int32_t>(std::invoke(lengthInvocable, edge))};

        if ((static_cast<std::int64_t>(distance[u]) + w) < distance[v]) {
            PL_THROW_WITH_SOURCE_INFO(
                std::runtime_error, "Graph contains a negative-weight cycle");
        }
    }

    return ShortestPaths<VertexIdentifier, std::int32_t>{
        std::move(source), std::move(predecessor), std::move(distance)};
}
} // namespace bellman_ford
} // namespace gp
#endif // INCG_GP_BELLMAN_FORD_ALGORITHM_HPP
