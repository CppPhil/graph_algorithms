#ifndef INCG_GP_DIJKSTRA_ALGORITHM_HPP
#define INCG_GP_DIJKSTRA_ALGORITHM_HPP
#include "../directed_graph.hpp"         // gp::DirectedGraph
#include "../shortest_paths.hpp"         // gp::ShortestPaths
#include "insert.hpp"                    // gp::dijkstra::insert
#include "vertex_with_priority.hpp"      // gp::dijkstra::VertexWithPriority
#include <ciso646>                       // not
#include <cstddef>                       // std::size_t
#include <cstdint>                       // SIZE_MAX
#include <pl/algo/ranged_algorithms.hpp> // pl::algo::find_if
#include <pl/annotations.hpp>            // PL_NODISCARD
#include <pl/invoke.hpp>                 // pl::invoke
#include <tl/optional.hpp>               // tl::optional, tl::nullopt
#include <unordered_map>                 // std::unordered_map
#include <utility>                       // std::move
#include <vector>                        // std::vector

namespace gp {
namespace dijkstra {
/*!
 * \brief Dijkstra's algorithm. Calculates the shortest paths to all vertices
 *        from a given source vertex.
 * \tparam VertexIdentifier The type of the unique identifiers used for the
 *                          vertices in the directed graph to operate on.
 * \tparam VertexData The type of the data that is stored on a vertex.
 * \tparam EdgeIdentifier The type of the unique identifiers used for the
 *                        edges in the directed graph to operate on.
 * \tparam EdgeData The type of the data that is stored on an edge.
 * \tparam LengthInvocable The type of the unary length invocable.
 * \param graph The directed graph to perform Dijkstra's algorithm on.
 * \param source The source vertex to use.
 * \param lengthInvocable A unary invocable that shall take an lvalue reference
 *                        to const typename DirectedGraph<VertexIdentifier,
 *                                                        VertexData,
 *                                                        EdgeIdentifier,
 *                                                        EdgeData>::edge_type
 *                        and return the length of the given edge as an object
 *                        of type std::size_t.
 * \return The resulting ShortestPaths object.
 **/
template<
    typename VertexIdentifier,
    typename VertexData,
    typename EdgeIdentifier,
    typename EdgeData,
    typename LengthInvocable>
PL_NODISCARD ShortestPaths<VertexIdentifier, std::size_t> algorithm(
    const DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData>&
                     graph,
    VertexIdentifier source,
    LengthInvocable  lengthInvocable)
{
    // Type aliases to cut down on the typing a little.
    using graph_type
        = DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData>;
    using vertex_type          = typename graph_type::vertex_type;
    using edge_type            = typename graph_type::edge_type;
    using vertex_with_priority = VertexWithPriority<VertexIdentifier>;

    // Constants
    constexpr std::size_t                infinity{SIZE_MAX};
    const tl::optional<VertexIdentifier> undefined{tl::nullopt};

    // Data structures
    // 'prev' associates vertices with their predecessors on the current
    // shortest path to them.
    std::unordered_map<VertexIdentifier, tl::optional<VertexIdentifier>> prev{};

    // 'dist' associates vertices with their distance (cost) values to get to
    // them from the source.
    std::unordered_map<VertexIdentifier, std::size_t> dist{};

    // The queue used by Dijkstra's algorithm.
    std::vector<vertex_with_priority> q{};

    // Initialization.
    // The distance to the source is 0. (We're already there.)
    dist[source] = 0;

    for (const vertex_type& v : graph.vertices()) {
        const VertexIdentifier& identifier{v.identifier()};

        // If it ain't the source -> consider the distance to be 'infinity' for
        // now. We consider the distance (cost) from source to 'v' to be unknown
        // at this point.
        if (identifier != source) { dist[identifier] = infinity; }

        // Set all the predecessor
        prev[identifier] = undefined;

        // Insert 'em all into the queue using their current distance value as
        // the priority.
        insert(q, vertex_with_priority{identifier, dist[identifier]});
    }
    // Done with the initialization.

    // The main loop.
    while (not q.empty()) {
        // Get the best vertex.
        const vertex_with_priority u{q.front()};
        q.erase(q.begin()); // Remove it from the queue

        // Get the outbound edges of the vertex that's the best one.
        // We want to get to all the neighbors of 'u'.
        // But we need to keep the edges around to query them for their length.
        const std::vector<const edge_type*> outbounds{
            graph.outboundEdges(u.vertex())};

        for (const edge_type* edge : outbounds) {
            // Get a neighbor of 'u'.
            const VertexIdentifier& target{edge->target()};

            // Try to get an iterator to the neighbor in the queue.
            const auto targetIterator{pl::algo::find_if(
                q, [&target](const vertex_with_priority& vertexWithPriority) {
                    return vertexWithPriority.vertex() == target;
                })};

            // If target is not in q -> skip it. We only care about neighbors of
            // 'u' that are still in q.
            if (targetIterator == q.end()) { continue; }

            // Calculate the alternative distance, which is the distance to 'u'
            // plus the edge that connects 'u' to the neighbor vertex of 'u'
            // that we're handling.
            const std::size_t alt{dist[u.vertex()]
                                  + pl::invoke(lengthInvocable, *edge)};

            // Get the distance to the neighbor.
            const std::size_t distanceNeighbor{dist[target]};

            // If the alternative distance is cheaper
            if (alt < distanceNeighbor) {
                dist[target] = alt; // It's cheaper, use the alternative
                                    // distance reaching the neighbor over 'u'
                                    // with the connecting edge between 'em.
                prev[target]
                    = u.vertex(); // Update the previous vertex to be 'u'.

                q.erase(targetIterator); // Temporarily remove the neighbor from
                                         // the queue
                insert(
                    q,
                    vertex_with_priority{target,
                                         alt}); // Add it again using the new
                                                // distance as the new priority.
            }
        }
    }

    // We're done here now.
    return ShortestPaths<VertexIdentifier, std::size_t>{
        std::move(source), std::move(prev), std::move(dist)};
}
} // namespace dijkstra
} // namespace gp
#endif // INCG_GP_DIJKSTRA_ALGORITHM_HPP
