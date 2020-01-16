#ifndef INCG_GP_FLEURY_EXPORT_GRAPH_HPP
#define INCG_GP_FLEURY_EXPORT_GRAPH_HPP
#include "../directed_graph.hpp" // gp::DirectedGraph
#include <cstddef>               // std::nullptr_t
#include <pl/annotations.hpp>    // PL_NODISCARD
#include <pl/string_view.hpp>    // pl::string_view

namespace gp {
namespace fleury {
PL_NODISCARD bool exportGraph(
    const DirectedGraph<char, std::nullptr_t, int, std::nullptr_t>& graph,
    pl::string_view                                                 filePath);
} // namespace fleury
} // namespace gp
#endif // INCG_GP_FLEURY_EXPORT_GRAPH_HPP
