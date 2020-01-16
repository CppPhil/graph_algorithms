#ifndef INCG_GP_HIERHOLZER_EXPORT_GRAPH_HPP
#define INCG_GP_HIERHOLZER_EXPORT_GRAPH_HPP
#include "../directed_graph.hpp" // gp::DirectedGraph
#include <cstddef>               // std::nullptr_t
#include <pl/annotations.hpp>    // PL_NODISCARD
#include <string>                // std::string
#include <vector>                // std::vector

namespace gp {
namespace hierholzer {
PL_NODISCARD bool exportGraph(
    const DirectedGraph<int, std::nullptr_t, int, std::nullptr_t>& graph,
    const std::vector<int>&                                        edgesToKeep,
    const std::string&                                             filePath);
} // namespace hierholzer
} // namespace gp
#endif // INCG_GP_HIERHOLZER_EXPORT_GRAPH_HPP
