#ifndef INCG_GP_HIERHOLZER_ALGORITHM_HPP
#define INCG_GP_HIERHOLZER_ALGORITHM_HPP
#include "../directed_graph.hpp" // gp::DirectedGraph
#include <pl/annotations.hpp>    // PL_NODISCARD
#include <tl/optional.hpp>       // tl::optional

namespace gp {
namespace hierholzer {
namespace detail {
template<
    typename VertexIdentifier,
    typename VertexData,
    typename EdgeIdentifier,
    typename EdgeData>
PL_NODISCARD tl::optional<VertexIdentifier> pickVertex(
    const std::vector<EdgeIdentifier>& result,
    const DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData>&
        graph)
{
    using namespace pl::literals::integer_literals;

    const auto target
        = [](EdgeIdentifier identifier) { return identifier % 10; };

    for (EdgeIdentifier edge : result) {
        const VertexIdentifier dst{target(edge)};

        if (graph.outboundDegree(dst) > 0_zu) { return dst; }
    }

    return tl::nullopt;
}

template<typename EdgeIdentifier>
typename std::vector<EdgeIdentifier>::const_iterator insertionPoint(
    const std::vector<EdgeIdentifier>& result,
    const std::vector<EdgeIdentifier>& subCircuit)
{
    using iterator = typename std::vector<EdgeIdentifier>::const_iterator;

    const auto source
        = [](EdgeIdentifier identifier) { return identifier / 10; };
    const auto target
        = [](EdgeIdentifier identifier) { return identifier % 10; };
    const EdgeIdentifier firstSource{source(subCircuit.front())};
    const iterator       it{pl::algo::find_if(
        result, [firstSource, &target](EdgeIdentifier curEdge) {
            return target(curEdge) == firstSource;
        })};

    assert((it != result.end()) and "iterator was invalid!");

    return it + 1;
}

template<
    typename VertexIdentifier,
    typename VertexData,
    typename EdgeIdentifier,
    typename EdgeData>
PL_NODISCARD std::vector<EdgeIdentifier> algorithm(
    VertexIdentifier startVertex,
    DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData>&
        graph)
{
    using graph_type
        = DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData>;
    using edge_type = typename graph_type::edge_type;

    std::vector<EdgeIdentifier> result{};
    VertexIdentifier            currentVertex{startVertex};

    do {
        const std::vector<const edge_type*> outbounds{
            graph.outboundEdges(currentVertex)};
        assert((not outbounds.empty()) and "vertex had no outbound edges!");

        const edge_type* const edgeToTake{outbounds.front()};
        currentVertex = edgeToTake->target();
        const EdgeIdentifier edgeToTakeIdentifier{edgeToTake->identifier()};
        result.push_back(edgeToTakeIdentifier);
        bool errC{graph.removeEdge(edgeToTakeIdentifier)};
        assert(errC and "Couldn't remove edge from graph!");

        // Special for C++: remove reverse edge.
        const auto swapTwoDecimalDigits = [](EdgeIdentifier i) {
            static_assert(
                std::is_same_v<EdgeIdentifier, int>,
                "EdgeIdentifier should be an alias of type int!");
            return ((i % 10) * 10) + (i / 10);
        };
        errC = graph.removeEdge(swapTwoDecimalDigits(edgeToTakeIdentifier));
        assert(errC and "Couldn't remove REVERSE edge from graph!");
    } while (currentVertex != startVertex);

    for (tl::optional<VertexIdentifier> pickedVertex{tl::nullopt};
         (pickedVertex = ::gp::hierholzer::detail::pickVertex(result, graph))
             .has_value();) {
        const std::vector<EdgeIdentifier> subCircuit{
            ::gp::hierholzer::detail::algorithm(pickedVertex.value(), graph)};

        if (subCircuit.empty()) {
            std::cerr << "file: " << __FILE__
                      << " function: " << PL_CURRENT_FUNCTION << ": "
                      << "subCircuit was empty!\n";
        }
        else {
            const typename std::vector<EdgeIdentifier>::const_iterator it{
                ::gp::hierholzer::detail::insertionPoint(result, subCircuit)};
            result.insert(it, subCircuit.begin(), subCircuit.end());
        }
    }

    return result;
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
    using graph_type
        = DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData>;
    using vertex_type = typename graph_type::vertex_type;

    assert(graph.hasVertices() and "graph had no vertices!");

    const std::vector<vertex_type>& vertices{graph.vertices()};
    const VertexIdentifier&         startVertex{vertices.front().identifier()};

    return ::gp::hierholzer::detail::algorithm(startVertex, graph);
}
} // namespace hierholzer
} // namespace gp
#endif // INCG_GP_HIERHOLZER_ALGORITHM_HPP
