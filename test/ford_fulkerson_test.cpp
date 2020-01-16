#include "gtest/gtest.h"
#include <ford_fulkerson/algorithm.hpp>
#include <ford_fulkerson/create_graph.hpp>

using namespace gp;

const int lines{10};

class FordFulkersonTest : public ::testing::Test {
public:
    using this_type         = FordFulkersonTest;
    using base_type         = ::testing::Test;
    using vertex_identifier = ford_fulkerson::types::vertex_identifier;
    using vertex_data       = ford_fulkerson::types::vertex_data;
    using edge_identifier   = ford_fulkerson::types::edge_identifier;
    using edge_data         = ford_fulkerson::types::edge_data;
    using graph_type        = ford_fulkerson::types::graph_type;

protected:
    const graph_type graph{ford_fulkerson::createGraph()};
};

TEST_F(FordFulkersonTest, basicTest)
{
    const int source{0};
    const int sink{5};

    const ford_fulkerson::Result result{
        ford_fulkerson::algorithm(graph, source, sink)};
    const std::int32_t expectedMaximumFlow{23};
    using K = ford_fulkerson::VertexPair<vertex_identifier>;
    const std::unordered_map<K, std::int32_t> expectedFlow{
        {K{0, 0}, 0},   {K{0, 1}, 12},  {K{0, 2}, 11},  {K{0, 3}, 0},
        {K{0, 4}, 0},   {K{0, 5}, 0},   {K{1, 0}, -12}, {K{1, 1}, 0},
        {K{1, 2}, 0},   {K{1, 3}, 12},  {K{1, 4}, 0},   {K{1, 5}, 0},
        {K{2, 0}, -11}, {K{2, 1}, 0},   {K{2, 2}, 0},   {K{2, 3}, 0},
        {K{2, 4}, 11},  {K{2, 5}, 0},   {K{3, 0}, 0},   {K{3, 1}, -12},
        {K{3, 2}, 0},   {K{3, 3}, 0},   {K{3, 4}, -7},  {K{3, 5}, 19},
        {K{4, 0}, 0},   {K{4, 1}, 0},   {K{4, 2}, -11}, {K{4, 3}, 7},
        {K{4, 4}, 0},   {K{4, 5}, 4},   {K{5, 0}, 0},   {K{5, 1}, 0},
        {K{5, 2}, 0},   {K{5, 3}, -19}, {K{5, 4}, -4},  {K{5, 5}, 0}};

    EXPECT_EQ(expectedMaximumFlow, result.maxFlow);
    EXPECT_EQ(expectedFlow, result.flow);
}
