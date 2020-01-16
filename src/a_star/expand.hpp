#ifndef INCG_GP_A_STAR_EXPAND_HPP
#define INCG_GP_A_STAR_EXPAND_HPP
#include "../directed_graph.hpp"    // gp::DirectedGraph
#include "identifier_with_cost.hpp" // gp::a_star::IdentifierWithCost
#include <vector>                   // std::vector

namespace gp {
namespace a_star {
/*!
 * \brief Expands a given vertex.
 * \tparam VertexIdentifier The type used to identify vertices.
 * \tparam VertexData The data that is stored on vertices.
 * \tparam EdgeIdentifier The type used to identify edges.
 * \tparam EdgeData The data that is stored on edges.
 * \param vertexToExpand The vertex that shall be expanded.
 * \param graph The graph that the vertex is in.
 * \return A vector containing vertex identifiers associated with
 *         the g value (edge length) of the edge used to get to it
 *         from 'vertexToExpand'.
 * \note The EdgeData shall have a nullary edgeLength member function
 *       returning the length (g value) of the edge.
 **/
template<
    typename VertexIdentifier,
    typename VertexData,
    typename EdgeIdentifier,
    typename EdgeData>
std::vector<IdentifierWithCost<VertexIdentifier>> expand(
    const VertexIdentifier& vertexToExpand,
    const DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData>&
        graph)
{
    // Type aliases
    using graph_type
        = DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData>;
    using edge_type = typename graph_type::edge_type;

    // Get the outbound edges of the vertex.
    const std::vector<const edge_type*> edges{
        graph.outboundEdges(vertexToExpand)};

    std::vector<IdentifierWithCost<VertexIdentifier>> result{};

    // Put the neighboring (and reachable) vertex associated with the edges
    // length in the result vector.
    for (const edge_type* edge : edges) {
        result.emplace_back(edge->target(), edge->data().edgeLength());
    }

    return result;
}
} // namespace a_star
} // namespace gp
#endif // INCG_GP_A_STAR_EXPAND_HPP
