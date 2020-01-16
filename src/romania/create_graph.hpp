#ifndef INCG_GP_ROMANIA_CREATE_GRAPH_HPP
#define INCG_GP_ROMANIA_CREATE_GRAPH_HPP
#include "../directed_graph.hpp"   // gp::DirectedGraph
#include "../length_edge_data.hpp" // gp::LengthEdgeData
#include "city.hpp"                // gp::romania::City
#include <cstddef>                 // std::nullptr_t, std::size_t

namespace gp {
namespace romania {
/*!
 * \brief Creates a graph for the Romania example.
 * \return The resulting graph.
 **/
DirectedGraph<City, std::nullptr_t, int, LengthEdgeData<std::size_t>>
createGraph();
} // namespace romania
} // namespace gp
#endif // INCG_GP_ROMANIA_CREATE_GRAPH_HPP