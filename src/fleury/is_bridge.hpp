#ifndef INCG_GP_FLEURY_IS_BRIDGE_HPP
#define INCG_GP_FLEURY_IS_BRIDGE_HPP
#include "../directed_graph.hpp"       // gp::DirectedGraph
#include "reachable_vertices_from.hpp" // gp::fleury::reachableVerticesFrom
#include <cassert>                     // assert
#include <ciso646>                     // and
#include <cstdint>                     // std::uint64_t
#include <pl/annotations.hpp>          // PL_NODISCARD

namespace gp {
namespace fleury {
/*!
 * \tparam VertexIdentifier The type of which instances are used to uniquely
 *                          identify vertices in the graph.
 * \tparam VertexData The type of the data stored on a vertex in the graph.
 * \tparam EdgeIdentifier The type of which instances are used to uniquely
 *                        identify edges in the graph.
 * \tparam EdgeData The type of the data stored on an edge in the graph.
 * \param graph The graph that contains the edge given.
 * \param edge The edge for which it shall be determined whether it is a bridge.
 * \return true if the edge given is a bridge in the graph given; otherwise
 *         false.
 * \warning The edge given must be an edge of the graph given!
 *
 * Determines if the edge given is a bridge.
 * A bridge is an edge within a graph that if that edge were to be removed
 * it would create at least one additional strongly connected component
 * within the graph.
 * This function template is used by Fleury's algorithm to check if an
 * edge is a bridge, since it may only use bridge edges if no alternative exists
 * as to not prevent itself from being able to construct a Eulerian circuit.
 **/
template<
    typename VertexIdentifier,
    typename VertexData,
    typename EdgeIdentifier,
    typename EdgeData>
PL_NODISCARD bool isBridge(
    const DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData>&
                          graph,
    const EdgeIdentifier& edge)
{
    using graph_type
        = DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData>;

    const VertexIdentifier source{graph.source(edge).value()};

    // How many vertices can be reached from the source of our edge?
    const std::uint64_t count1{reachableVerticesFrom(graph, source)};

    // Create a copy of the graph. We don't want to modify the actual graph.
    graph_type graphCopy{graph};

    // Delete our edge from the copy.
    bool errC{graphCopy.removeEdge(edge)};
    (void)errC;
    assert(errC and "Edge couldn't be removed!");

    // Delete reverse as well (SPECIAL FOR C++)
    errC = graphCopy.removeEdge(-edge);
    (void)errC;
    assert(errC and "Edge couldn't be removed (the 2nd one)!");

    // Check how many vertices we can reach from source without our edge.
    const std::uint64_t count2{reachableVerticesFrom(graphCopy, source)};

    // If we can now reach fewer vertices
    // -> then that's because we've created a new strongly connected component.
    //    Hence our edge must be a bridge.
    // Otherwise our edge isn't a bridge.
    return count2 < count1;
}
} // namespace fleury
} // namespace gp
#endif // INCG_GP_FLEURY_IS_BRIDGE_HPP
