#ifndef INCG_GP_NM_CREATE_GRAPH_HPP
#define INCG_GP_NM_CREATE_GRAPH_HPP
#include "../directed_graph.hpp"   // gp::DirectedGraph
#include "../length_edge_data.hpp" // gp::LengthEdgeData
#include <cstddef>                 // std::nullptr_t, std::size_t
#include <string>                  // std::string

namespace gp {
namespace nm {
/*!
 * \brief Creates the graph for the non-monotonic heuristic example.
 * \return The graph for the non-monotonic heuristic example.
 **/
DirectedGraph<std::string, std::nullptr_t, int, LengthEdgeData<std::size_t>>
createGraph();
} // namspace nm
} // namespace gp
#endif // INCG_GP_NM_CREATE_GRAPH_HPP
