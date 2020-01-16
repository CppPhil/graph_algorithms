#include "create_graph.hpp"
#include <cinttypes> // PRId16
#include <cstdint>   // std::int32_t
#include <cstdio>    // std::sscanf
#include <sstream>   // std::istringstream
#include <string>    // std::string, std::getline

namespace gp {
namespace ford_fulkerson {
const char data[] =
    R"(0 1 16
0 2 13
1 2 10
2 1 4
3 2 9
1 3 12
2 4 14
4 3 7
3 5 20
4 5 4)";

const int lines{10};

types::graph_type createGraph()
{
    types::graph_type graph{};

    std::istringstream iss{data};

    for (int i{0}; i < lines; ++i) {
        std::int32_t vertex1{};
        std::int32_t vertex2{};
        std::int32_t currentCapacityValue{};

        std::string buf{};
        std::getline(iss, buf);

        std::sscanf(
            buf.data(),
            "%" PRId16 " %" PRId16 " %" PRId16,
            &vertex1,
            &vertex2,
            &currentCapacityValue);

        (void)graph.addVertex(vertex1, nullptr);
        (void)graph.addVertex(vertex2, nullptr);
        (void)graph.addEdge(
            i, vertex1, vertex2, types::edge_data{currentCapacityValue});
    }

    return graph;
}

types::graph_type createGraph2()
{
    types::graph_type g{};

    auto add
        = [&g, i = 0](
              std::int32_t v1, std::int32_t v2, std::int32_t capacity) mutable {
              (void)g.addVertex(v1, nullptr);
              (void)g.addVertex(v2, nullptr);
              (void)g.addEdge(i, v1, v2, types::edge_data{capacity});
              ++i;
          };

    add(0, 1, 2);
    add(0, 2, 1);
    add(0, 3, 3);
    add(2, 3, 6);
    add(3, 4, 8);
    add(2, 5, 5);
    add(4, 5, 4);
    add(1, 5, 4);

    return g;
}
} // namespace ford_fulkerson
} // namespace gp
