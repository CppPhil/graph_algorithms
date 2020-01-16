#include "export_graph.hpp"
#include <cstdint>  // std::uint8_t, std::int32_t, std::uint32_t
#include <iostream> // std::cerr
#include <sstream>  // std::ostringstream

namespace gp {
namespace fleury {
PL_NODISCARD bool exportGraph(
    const DirectedGraph<char, std::nullptr_t, int, std::nullptr_t>& graph,
    pl::string_view                                                 filePath)
{
    std::ostringstream          oss{};
    graph_format::DataStructure graphFormat{graph.graphFormat(
        [&oss](char vertexIdentifier) {
            const std::int32_t result{
                static_cast<std::int32_t>(static_cast<std::uint32_t>(
                    static_cast<std::uint8_t>(vertexIdentifier)))};

            oss << "vertex: " << vertexIdentifier << " => " << result << '\n';

            return result;
        },
        [&oss](const auto& edge) {
            const std::int32_t res{0};
            oss << "edge: " << edge.identifier() << " => " << res
                << " (label)\n";
            return res;
        })};
    graphFormat.text(oss.str());

    if (graphFormat.exportToFile(filePath.to_string())) {
        std::cerr << "Successfully exported to \"" << filePath << "\"\n";
        return true;
    }

    std::cerr << "Couldn't export to \"" << filePath << "\"\n";
    return false;
}
} // namespace fleury
} // namespace gp
