#ifndef INCG_GP_FLEURY_ALGORITHM_TEST_GRAPH_HPP
#define INCG_GP_FLEURY_ALGORITHM_TEST_GRAPH_HPP
#include "../directed_graph.hpp" // gp::DirectedGraph
#include <cstddef>               // std::nullptr_t

namespace gp {
namespace fleury {
namespace algorithm_test_graph_types {
using vertex_identifier = char;
using vertex_data       = std::nullptr_t;
using edge_identifier   = int;
using edge_data         = std::nullptr_t;
using graph_type
    = DirectedGraph<vertex_identifier, vertex_data, edge_identifier, edge_data>;
} // namespace algorithm_test_graph_types

algorithm_test_graph_types::graph_type algorithmTestGraph();
} // namespace fleury
} // namespace gp
#endif // INCG_GP_FLEURY_ALGORITHM_TEST_GRAPH_HPP
