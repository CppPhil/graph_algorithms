#ifndef INCG_GP_FLEURY_ALGORITHM_HPP
#define INCG_GP_FLEURY_ALGORITHM_HPP
#include "../directed_graph.hpp"         // gp::DirectedGraph
#include "is_bridge.hpp"                 // gp::fleury::isBridge
#include <cassert>                       // assert
#include <ciso646>                       // not, and
#include <pl/algo/ranged_algorithms.hpp> // pl::algo::find_if
#include <pl/annotations.hpp>            // PL_NODISCARD
#include <pl/except.hpp>                 // PL_THROW_WITH_SOURCE_INFO
#include <pl/size_t.hpp> // pl::literals::integer_literals::operator""_zu
#include <stdexcept>     // std::logic_error
#include <type_traits>   // std::is_same_v
#include <vector>        // std::vector

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
 * \param outbounds The current outbound edges.
 * \return A pointer to the edge picked.
 *
 * Implementation function template for Fleury's algorithm.
 * Picks an edge.
 * If there's only one outbound edge -> that edge is picked.
 * If there are multiple the first one that isn't a bridge is picked.
 * This works because Fleury's algorithm guarantees that there will
 * never be more than one outbound bridge.
 **/
template<
    typename VertexIdentifier,
    typename VertexData,
    typename EdgeIdentifier,
    typename EdgeData>
PL_NODISCARD const Edge<EdgeIdentifier, EdgeData, VertexIdentifier>* pickEdge(
    const DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData>&
        graph,
    const std::vector<const Edge<EdgeIdentifier, EdgeData, VertexIdentifier>*>&
        outbounds)
{
    // Type aliases
    using graph_type
        = DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData>;
    using edge_type = typename graph_type::edge_type;

    using namespace pl::literals::integer_literals;

    // If there's only one -> we have to pick that.
    if (outbounds.size() == 1_zu) { return outbounds.front(); }

    // Otherwise take the first outbound edge that isn't a bridge.
    const typename std::vector<const edge_type*>::const_iterator it{
        pl::algo::find_if(outbounds, [&graph](const edge_type* currentEdge) {
            return not isBridge(graph, currentEdge->identifier());
        })};

    assert(
        (it != outbounds.end())
        and "outbounds contained more than one edge that is a bridge!");

    // Return the non-bridge edge found.
    return *it;
}

/*!
 * \tparam VertexIdentifier The type of which instances are used to uniquely
 *                          identify vertices in the graph.
 * \tparam VertexData The type of the data stored on a vertex in the graph.
 * \tparam EdgeIdentifier The type of which instances are used to uniquely
 *                        identify edges in the graph.
 * \tparam EdgeData The type of the data stored on an edge in the graph.
 * \param graph In-out parameter. The graph to delete the reverse edge from.
 * \param edgeIdentifier The identifier of the edge of which the reverse
 *                       edge shall be deleted from the graph given.
 *
 * Implementation function template for Fleury's algorithm.
 * Deletes the reverse edge of a given edge identifier.
 * This is used because we only have implemented directed graphs
 * in this C++ project.
 * Hence we have reverse edges for every edge and need to delete
 * them as well when having deleted the forward edge.
 * It's like that because Fleury's algorithm can only work
 * on undirected graphs (I think).
 * This function template assumes that the reverse edge can be
 * obtained by just negating (unary operator-) the forward
 * edge identifier given. This works for all the test cases
 * that we actually use Fleury's algorithm in.
 **/
template<
    typename VertexIdentifier,
    typename VertexData,
    typename EdgeIdentifier,
    typename EdgeData>
void deleteReverseEdge(
    DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData>&
                          graph,
    const EdgeIdentifier& edgeIdentifier)
{
    // Statically assert for sanity.
    static_assert(
        std::is_same_v<EdgeIdentifier, int>, "EdgeIdentifier should be int");

    // Create the reverse edge identifier
    const EdgeIdentifier reverseEdgeIdentifer{-edgeIdentifier};

    // If the graph actually has that reverse edge -> remove it.
    if (graph.hasEdge(reverseEdgeIdentifer)) {
        if (not graph.removeEdge(reverseEdgeIdentifer)) {
            PL_THROW_WITH_SOURCE_INFO(
                std::logic_error,
                "Couldn't remove reverse edge even though the graph has it!");
        }
    }
}
} // namespace detail

/*!
 * \tparam VertexIdentifier The type of which instances are used to uniquely
 *                          identify vertices in the graph.
 * \tparam VertexData The type of the data stored on a vertex in the graph.
 * \tparam EdgeIdentifier The type of which instances are used to uniquely
 *                        identify edges in the graph.
 * \tparam EdgeData The type of the data stored on an edge in the graph.
 * \param graph The graph to get a Eularian circuit of.
 * \return The Eularian circuit found in the graph as a vector of the edges
 *         traversed (to be read from the front).
 * \throw std::logic_error on error.
 * \note Complexity is quadratic in the amount of edges in the graph.
 * \warning Fleury's algorithm requires that the graph given is connected!
 *          Fleury's algorithm requires that every vertex in the graph has an
 *          even degree!
 *
 * Implements Fleury's algorithm.
 * Finds a Eularian circuit in the graph given when there is one and
 * the preconditions are met.
 **/
template<
    typename VertexIdentifier,
    typename VertexData,
    typename EdgeIdentifier,
    typename EdgeData>
PL_NODISCARD std::vector<EdgeIdentifier> algorithm(
    DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData> graph)
{
    // Type aliases
    using graph_type
        = DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData>;
    using vertex_type = typename graph_type::vertex_type;
    using edge_type   = typename graph_type::edge_type;

    // Sanity check
    if (not graph.hasVertices()) {
        PL_THROW_WITH_SOURCE_INFO(std::logic_error, "Graph has no vertices!");
    }

    // We will build up the Eularian circuit in here.
    std::vector<EdgeIdentifier> result{};

    // Get the vertices of the graph.
    const std::vector<vertex_type>& vertices{graph.vertices()};

    // The start vertex. (Chosen arbitrarily)
    const VertexIdentifier s{vertices.front().identifier()};

    // The current vertex. (Starts out as s)
    VertexIdentifier v{s};

    // Get the remaining outbound edges of the current vertex.
    // If there are no more -> We're done.
    for (std::vector<const edge_type*> outbounds{};
         not(outbounds = graph.outboundEdges(v)).empty();) {
        // Otherwise (there are still outbound edges)
        // Pick the next edge (e).
        const edge_type* e{detail::pickEdge(graph, outbounds)};

        // Move along the edge picked.
        // Our current vertex is now the target vertex of the edge.
        v = e->target();

        // Put the edge identifier into the result (We've just traversed it)
        result.push_back(e->identifier());

        // Copy the edge identifier on out.
        // We'll delete edges shortly invalidating the pointers.
        const EdgeIdentifier edgeIdentifier{e->identifier()};

        // Delete the edge. (We can no longer touch the pointers now until the
        // end of the iteration)
        if (not graph.removeEdge(edgeIdentifier)) {
            PL_THROW_WITH_SOURCE_INFO(
                std::logic_error, "Could not remove edge!");
        }

        // Since this codebase technically only works with
        // directed graphs the reverse edge also has to be
        // removed.
        detail::deleteReverseEdge(graph, edgeIdentifier);

        // Go back up.
    }

    // We're done.
    // Return the Eularian circuit found.
    return result;
}
} // namespace fleury
} // namespace gp
#endif // INCG_GP_FLEURY_ALGORITHM_HPP
