#include "export_graph.hpp"
#include "../contains.hpp"                    // gp::contains
#include "../graph_format/data_structure.hpp" // gp::graph_format::DataStructure
#include <cstdint>                            // std:int32_t
#include <iostream>                           // std::cout

namespace gp {
namespace hierholzer {
PL_NODISCARD bool exportGraph(
    const DirectedGraph<int, std::nullptr_t, int, std::nullptr_t>& graph,
    const std::vector<int>&                                        edgesToKeep,
    const std::string&                                             filePath)
{
    using graph_type = DirectedGraph<int, std::nullptr_t, int, std::nullptr_t>;
    using edge_type  = graph_type::edge_type;

    constexpr std::int32_t edgeLabel{INT32_C(0)};

    const std::vector<edge_type>& edges{graph.edges()};

    graph_format::DataStructure gf{};

    for (const edge_type& edge : edges) {
        if (contains(edgesToKeep, edge.identifier())) {
            gf.append(edge.source(), edge.target(), edgeLabel);
        }
    }

    if (gf.exportToFile(filePath)) {
        std::cout << "Successfully exported to \"" << filePath << "\"\n";
        return true;
    }

    std::cout << "Couldn't export to \"" << filePath << "\"!\n";
    return false;
}
} // namespace hierholzer
} // namespace gp
