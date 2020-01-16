#ifndef INCG_GP_FLEURY_REACHABLE_VERTICES_FROM_HPP
#define INCG_GP_FLEURY_REACHABLE_VERTICES_FROM_HPP
#include "../directed_graph.hpp"         // gp::DirectedGraph
#include "../vertex.hpp"                 // gp::Vertex
#include <cinttypes>                     // UINT64_C
#include <ciso646>                       // not
#include <cstdint>                       // std::uint64_t
#include <pl/algo/ranged_algorithms.hpp> // pl::algo::transform
#include <pl/annotations.hpp>            // PL_NODISCARD
#include <unordered_map>                 // std::unordered_map

namespace gp {
namespace fleury {
namespace detail {
/*!
 * \tparam VertexIdentifier The type of which instances are used to uniquely
 *                          identify vertices in the graph.
 * \tparam VertexData The type of the data stored on a vertex in the graph.
 * \tparam EdgeIdentifier The type of which instances are used to uniquely
 *                        identify edges in the graph.
 * \tparam EdgeData The type of the data stored on an edge in the graph.
 * \param graph The graph to operate on.
 * \param vertex The vertex for which to determine the amount of reachable
 *               vertices.
 * \param isVisited In-out parameter to keep track of which vertices are
 *                  already visited and which aren't.
 * \return The amount of vertices reachable from vertex.
 * \note This is an implementation function. It is not to be called directly
 *       from client code.
 **/
template<
    typename VertexIdentifier,
    typename VertexData,
    typename EdgeIdentifier,
    typename EdgeData>
PL_NODISCARD std::uint64_t reachableVerticesFromImpl(
    const DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData>&
                                                graph,
    const VertexIdentifier&                     vertex,
    std::unordered_map<VertexIdentifier, bool>& isVisited)
{
    // Type aliases
    using graph_type
        = DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData>;
    using edge_type = typename graph_type::edge_type;

    isVisited[vertex] = true;         // We're visiting it right now.
    std::uint64_t count{UINT64_C(1)}; // Every vertex can at least reach itself.

    // For all the reachables
    const std::vector<const edge_type*> outbounds{graph.outboundEdges(vertex)};
    const std::vector<VertexIdentifier> reachables{[&outbounds] {
        std::vector<VertexIdentifier> result(
            outbounds.size(), VertexIdentifier{});
        pl::algo::transform(
            outbounds, result.begin(), [](const edge_type* currentEdge) {
                return currentEdge->target();
            });
        return result;
    }()};

    for (const VertexIdentifier& reachable : reachables) {
        // If we haven't already visited it -> recurse (Depth First Search).
        if (not isVisited[reachable]) {
            count += reachableVerticesFromImpl(graph, reachable, isVisited);
        }
    }

    // Done.
    return count;
}
} // namespace detail

/*!
 * \tparam VertexIdentifier The type of which instances are used to uniquely
 *                          identify vertices in the graph.
 * \tparam VertexData The type of the data stored on a vertex in the graph.
 * \tparam EdgeIdentifier The type of which instances are used to uniquely
 *                        identify edges in the graph.
 * \tparam EdgeData The type of the data stored on an edge in the graph.
 * \param graph The graph to operate on.
 * \param vertex The vertex in the graph given for which to determine
 *               the amount of reachable vertices.
 * \return The amount (number) of vertices reachable from the vertex given.
 *         (This includes the vertex itself (vertices can always at least
 *         reach themselves))
 * \note Complexity is linear in the amount of edges in the graph.
 * \warning The vertex must be a vertex of the graph given!
 *
 * The entry point for the user into this algorithm.
 * Uses a DFS (depth first search) to count the amount of vertices
 * that can be reached from the vertex given in the given graph.
 **/
template<
    typename VertexIdentifier,
    typename VertexData,
    typename EdgeIdentifier,
    typename EdgeData>
PL_NODISCARD std::uint64_t reachableVerticesFrom(
    const DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData>&
                            graph,
    const VertexIdentifier& vertex)
{
    // Set up isVisited map
    std::unordered_map<VertexIdentifier, bool> isVisited{};

    // By default all vertices in the graph must be considered non-visited.
    for (const auto& v : graph.vertices()) {
        isVisited.emplace(v.identifier(), false);
    }

    // Branch into the recursive algorithm.
    return ::gp::fleury::detail::reachableVerticesFromImpl(
        graph, vertex, isVisited);
}
} // namespace fleury
} // namespace gp
#endif // INCG_GP_FLEURY_REACHABLE_VERTICES_FROM_HPP
