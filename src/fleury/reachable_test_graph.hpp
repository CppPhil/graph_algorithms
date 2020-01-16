#ifndef INCG_GP_FLEURY_REACHABLE_TEST_GRAPH_HPP
#define INCG_GP_FLEURY_REACHABLE_TEST_GRAPH_HPP
#include "../directed_graph.hpp" // gp::DirectedGraph
#include <cstddef>               // std::nullptr_t

namespace gp {
namespace fleury {
namespace reachable_test_graph_types {
using vertex_identifier = char;
using vertex_data       = std::nullptr_t;
using edge_identifier   = int;
using edge_data         = std::nullptr_t;
using graph_type
    = DirectedGraph<vertex_identifier, vertex_data, edge_identifier, edge_data>;
} // namespace reachable_test_graph_types

reachable_test_graph_types::graph_type reachableTestGraph();
} // namespace fleury
} // namespace gp
#endif // INCG_GP_FLEURY_REACHABLE_TEST_GRAPH_HPP
