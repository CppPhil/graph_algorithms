#ifndef INCG_GP_BELLMAN_FORD_POSITIVE_CYCLE_HPP
#define INCG_GP_BELLMAN_FORD_POSITIVE_CYCLE_HPP
#include "../directed_graph.hpp"   // gp::DirectedGraph
#include "../length_edge_data.hpp" // gp::LengthEdgeData
#include <cstddef>                 // std::nullptr_t
#include <cstdint>                 // std::int32_t
#include <string>                  // std::string

namespace gp {
namespace bellman_ford {
struct PositiveCycle {
    using vertex_identifier = std::string;
    using vertex_data       = std::nullptr_t;
    using edge_identifier   = int;
    using edge_data         = LengthEdgeData<std::int32_t>;
    using graph_type        = DirectedGraph<
        vertex_identifier,
        vertex_data,
        edge_identifier,
        edge_data>;

    /*!
     * \brief Creates a graph containing a positive-weight cycle
     * \return The graph created
     **/
    static graph_type create();
};
} // namespace bellman_ford
} // namespace gp
#endif // INCG_GP_BELLMAN_FORD_POSITIVE_CYCLE_HPP
