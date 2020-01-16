#ifndef INCG_GP_HIERHOLZER_ALGORITHM_HPP
#define INCG_GP_HIERHOLZER_ALGORITHM_HPP
#include "../directed_graph.hpp"         // gp::DirectedGraph
#include <pl/algo/ranged_algorithms.hpp> // pl::algo::find_if
#include <pl/annotations.hpp>            // PL_NODISCARD
#include <vector>                        // std::vector

namespace gp {
namespace hierholzer {
namespace detail {
#define GP_GRAPH_TEMPLATE          \
    template<                      \
        typename VertexIdentifier, \
        typename VertexData,       \
        typename EdgeIdentifier,   \
        typename EdgeData>

int sourceOf(int edgeIdentifier);

int targetOf(int edgeIdentifier);

int reverseEdgeOf(int edgeIdentifier);

GP_GRAPH_TEMPLATE
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

GP_GRAPH_TEMPLATE
VertexIdentifier takeStep(
    VertexIdentifier             sourceVertex,
    std::vector<EdgeIdentifier>& eulerCircuit,
    DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData>&
                                   graph,
    std::vector<VertexIdentifier>& openList)
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

    eulerCircuit.push_back(firstOutboundEdgeIdentifier);

    if (outboundEdges.size() > 1U) { openList.push_back(sourceVertex); }

    removeEdge(graph, firstOutboundEdgeIdentifier);

    return targetOf(firstOutboundEdgeIdentifier);
}

GP_GRAPH_TEMPLATE
std::vector<EdgeIdentifier> createCircuit(
    VertexIdentifier startVertex,
    DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData>&
                                   graph,
    std::vector<VertexIdentifier>& openList)
{
    std::vector<EdgeIdentifier> eulerCircuit{};
    VertexIdentifier            currentVertex{startVertex};

    do {
        currentVertex = takeStep(currentVertex, eulerCircuit, graph, openList);
    } while (currentVertex != startVertex);

    return eulerCircuit;
}

GP_GRAPH_TEMPLATE
VertexIdentifier chooseNextVertex(
    const DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData>&
                                   graph,
    std::vector<VertexIdentifier>& openList)
{
    using graph_type
        = DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData>;
    using edge_type = typename graph_type::edge_type;

    const VertexIdentifier              vertex{openList.front()};
    const std::vector<const edge_type*> outboundEdges{
        graph.outboundEdges(vertex)};

    if (outboundEdges.empty()) {
        openList.erase(openList.begin());
        return chooseNextVertex(graph, openList);
    }
    else {
        return vertex;
    }
}

template<typename EdgeIdentifier>
void insertInto(
    std::vector<EdgeIdentifier>&       eulerCircuit,
    const std::vector<EdgeIdentifier>& subCircuit)
{
    using VertexIdentifier = int;

    const EdgeIdentifier   first{subCircuit.front()};
    const VertexIdentifier firstSource{sourceOf(first)};

    const typename std::vector<EdgeIdentifier>::const_iterator position{
        pl::algo::find_if(
            eulerCircuit, [firstSource](EdgeIdentifier edgeIdentifier) {
                return targetOf(edgeIdentifier) == firstSource;
            })};

    assert(
        (position != eulerCircuit.end()) and "Failure to find in insertInto!");

    eulerCircuit.insert(
        /* insert after position */ position + 1,
        subCircuit.begin(),
        subCircuit.end());
}

GP_GRAPH_TEMPLATE
void createEularianTour(
    DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData>&
                                   graph,
    std::vector<EdgeIdentifier>&   eulerCircuit,
    std::vector<VertexIdentifier>& openList)
{
    using graph_type
        = DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData>;
    using edge_type = typename graph_type::edge_type;

    const std::vector<edge_type>& edges{graph.edges()};

    if (edges.empty()) { return; }

    const VertexIdentifier chosenVertex{chooseNextVertex(graph, openList)};
    const std::vector<EdgeIdentifier> subCircuit{
        createCircuit(chosenVertex, graph, openList)};
    insertInto(eulerCircuit, subCircuit);

    createEularianTour(graph, eulerCircuit, openList);
}
} // namespace detail

GP_GRAPH_TEMPLATE
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
    std::vector<VertexIdentifier> openList{};

    std::vector<EdgeIdentifier> eulerCircuit{
        detail::createCircuit(startVertex, graph, openList)};

    detail::createEularianTour(graph, eulerCircuit, openList);

    return eulerCircuit;
}

#undef GP_GRAPH_TEMPLATE
} // namespace hierholzer
} // namespace gp
#endif // INCG_GP_HIERHOLZER_ALGORITHM_HPP
