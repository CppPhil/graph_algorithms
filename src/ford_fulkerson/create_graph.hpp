#ifndef INCG_GP_FORD_FULKERSON_CREATE_GRAPH_HPP
#define INCG_GP_FORD_FULKERSON_CREATE_GRAPH_HPP
#include "../directed_graph.hpp" // gp::DirectedGraph
#include <cstddef>               // std::nullptr_t

namespace gp {
namespace ford_fulkerson {
namespace types {
using vertex_identifier = int;
using vertex_data       = std::nullptr_t;
using edge_identifier   = int;
class edge_data {
public:
    explicit edge_data(std::int32_t capacity) noexcept : m_capacity{capacity} {}

    std::int32_t capacity() const noexcept { return m_capacity; }

private:
    std::int32_t m_capacity;
};
using graph_type
    = DirectedGraph<vertex_identifier, vertex_data, edge_identifier, edge_data>;
} // namespace types

types::graph_type createGraph();

types::graph_type createGraph2();
} // namespace ford_fulkerson
} // namespace gp
#endif // INCG_GP_FORD_FULKERSON_CREATE_GRAPH_HPP
