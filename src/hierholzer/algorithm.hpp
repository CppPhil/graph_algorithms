#ifndef INCG_GP_HIERHOLZER_ALGORITHM_HPP
#define INCG_GP_HIERHOLZER_ALGORITHM_HPP
#include "../directed_graph.hpp"         // gp::DirectedGraph
#include <pl/algo/ranged_algorithms.hpp> // pl::algo::find_if
#include <pl/annotations.hpp>            // PL_NODISCARD
#include <vector>                        // std::vector

namespace gp {
namespace hierholzer {
namespace detail {
int sourceOf(int edgeIdentifier);

int targetOf(int edgeIdentifier);

int reverseEdgeOf(int edgeIdentifier);

template<
    typename VertexIdentifier,
    typename VertexData,
    typename EdgeIdentifier,
    typename EdgeData>
void removeEdge(
    DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData>&
                   graph,
    EdgeIdentifier edge)
{
    const bool hasSucceeded{graph.removeEdge(edge)};
    assert(hasSucceeded and "Couldn't remove edge from graph");
    (void)hasSucceeded;

    const bool hasSucceeded2{graph.removeEdge(reverseEdgeOf(edge))};
    assert(hasSucceeded2 and "Couldn't remove reverse edge from graph");
    (void)hasSucceeded2;
}

template<
    typename VertexIdentifier,
    typename VertexData,
    typename EdgeIdentifier,
    typename EdgeData>
VertexIdentifier traverseNextEdge(
    VertexIdentifier             sourceVertex,
    std::vector<EdgeIdentifier>& eularianCircuit,
    DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData>&
                                   graph,
    std::vector<VertexIdentifier>& toExplore)
{
    using graph_type
        = DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData>;
    using edge_type = typename graph_type::edge_type;

    const std::vector<const edge_type*> outboundEdges{
        graph.outboundEdges(sourceVertex)};
    assert((not outboundEdges.empty()) and "Vertex has no outbound edges!");
    const edge_type* const firstOutboundEdge{outboundEdges.front()};
    const EdgeIdentifier   firstOutboundEdgeIdentifier{
        firstOutboundEdge->identifier()};

    eularianCircuit.push_back(firstOutboundEdgeIdentifier);

    if (outboundEdges.size() > 1U) { toExplore.push_back(sourceVertex); }

    removeEdge(graph, firstOutboundEdgeIdentifier);

    return targetOf(firstOutboundEdgeIdentifier);
}

template<
    typename VertexIdentifier,
    typename VertexData,
    typename EdgeIdentifier,
    typename EdgeData>
std::vector<EdgeIdentifier> findCircuit(
    VertexIdentifier startVertex,
    DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData>&
                                   graph,
    std::vector<VertexIdentifier>& toExplore)
{
    std::vector<EdgeIdentifier> eularianCircuit{};
    VertexIdentifier            currentVertex{startVertex};

    do {
        currentVertex = traverseNextEdge(
            currentVertex, eularianCircuit, graph, toExplore);
    } while (currentVertex != startVertex);

    return eularianCircuit;
}

template<
    typename VertexIdentifier,
    typename VertexData,
    typename EdgeIdentifier,
    typename EdgeData>
VertexIdentifier pickVertex(
    const DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData>&
                                   graph,
    std::vector<VertexIdentifier>& toExplore)
{
    using graph_type
        = DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData>;
    using edge_type = typename graph_type::edge_type;

    const VertexIdentifier              vertex{toExplore.front()};
    const std::vector<const edge_type*> outboundEdges{
        graph.outboundEdges(vertex)};

    if (outboundEdges.empty()) {
        toExplore.erase(toExplore.begin());
        return pickVertex(graph, toExplore);
    }
    else {
        return vertex;
    }
}

template<typename EdgeIdentifier>
void insertInto(
    std::vector<EdgeIdentifier>&       eularianCircuit,
    const std::vector<EdgeIdentifier>& subCircuit)
{
    using VertexIdentifier = int;

    const EdgeIdentifier   first{subCircuit.front()};
    const VertexIdentifier firstSource{sourceOf(first)};

    const typename std::vector<EdgeIdentifier>::const_iterator position{
        pl::algo::find_if(
            eularianCircuit, [firstSource](EdgeIdentifier edgeIdentifier) {
                const int currentTarget{targetOf(edgeIdentifier)};
                return currentTarget == firstSource;
            })};

    assert(
        (position == eularianCircuit.end())
        and "Failure to find in insertInto!");

    eularianCircuit.insert(position + 1, subCircuit.begin(), subCircuit.end());
}

template<
    typename VertexIdentifier,
    typename VertexData,
    typename EdgeIdentifier,
    typename EdgeData>
std::vector<EdgeIdentifier> createEularianTour(
    DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData>&
                                   graph,
    std::vector<EdgeIdentifier>&   eularianCircuit,
    std::vector<VertexIdentifier>& toExplore)
{
    using graph_type
        = DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData>;
    using edge_type = typename graph_type::edge_type;

    const std::vector<edge_type>& edges{graph.edges()};

    if (edges.empty()) { return eularianCircuit; }

    const VertexIdentifier vertexPicked{pickVertex(graph, toExplore)};
    const std::vector<EdgeIdentifier> subCircuit{
        findCircuit(vertexPicked, graph, toExplore)};
    insertInto(eularianCircuit, subCircuit);

    return createEularianTour(graph, eularianCircuit, toExplore);
}
} // namespace detail

template<
    typename VertexIdentifier,
    typename VertexData,
    typename EdgeIdentifier,
    typename EdgeData>
PL_NODISCARD std::vector<EdgeIdentifier> algorithm(
    DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData> graph)
{
    static_assert(
        std::is_same_v<EdgeIdentifier, int>,
        "EdgeIdentifier should be an alias of type int!");

    static_assert(
        std::is_same_v<VertexIdentifier, EdgeIdentifier>,
        "VertexIdentifier and EdgeIdentifier aren't the same type!");

    assert(graph.hasVertices() and "graph had no vertices!");

    const VertexIdentifier startVertex{graph.vertices().front().identifier()};
    std::vector<VertexIdentifier> toExplore{};

    std::vector<EdgeIdentifier> eularianCircuit{
        detail::findCircuit(startVertex, graph, toExplore)};

    return detail::createEularianTour(graph, eularianCircuit, toExplore);
}
} // namespace hierholzer
} // namespace gp
#endif // INCG_GP_HIERHOLZER_ALGORITHM_HPP
