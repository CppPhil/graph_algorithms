#include "gtest/gtest.h"
#include <cinttypes>
#include <cstdint>
#include <fleury/reachable_test_graph.hpp>
#include <fleury/reachable_vertices_from.hpp>

using namespace std;
using namespace gp;

class ReachableVerticesFromTest : public ::testing::Test {
protected:
    const fleury::reachable_test_graph_types::graph_type graph{
        fleury::reachableTestGraph()};
};

TEST_F(ReachableVerticesFromTest, aTest)
{
    constexpr std::uint64_t expected{UINT64_C(4)};
    const std::uint64_t     actual{fleury::reachableVerticesFrom(graph, 'A')};
    EXPECT_EQ(expected, actual);
}

TEST_F(ReachableVerticesFromTest, bTest)
{
    constexpr std::uint64_t expected{UINT64_C(4)};
    const std::uint64_t     actual{fleury::reachableVerticesFrom(graph, 'B')};
    EXPECT_EQ(expected, actual);
}

TEST_F(ReachableVerticesFromTest, cTest)
{
    constexpr std::uint64_t expected{UINT64_C(4)};
    const std::uint64_t     actual{fleury::reachableVerticesFrom(graph, 'C')};
    EXPECT_EQ(expected, actual);
}

TEST_F(ReachableVerticesFromTest, dTest)
{
    constexpr std::uint64_t expected{UINT64_C(4)};
    const std::uint64_t     actual{fleury::reachableVerticesFrom(graph, 'D')};
    EXPECT_EQ(expected, actual);
}

TEST_F(ReachableVerticesFromTest, eTest)
{
    constexpr std::uint64_t expected{UINT64_C(2)};
    const std::uint64_t     actual{fleury::reachableVerticesFrom(graph, 'E')};
    EXPECT_EQ(expected, actual);
}

TEST_F(ReachableVerticesFromTest, fTest)
{
    constexpr std::uint64_t expected{UINT64_C(2)};
    const std::uint64_t     actual{fleury::reachableVerticesFrom(graph, 'F')};
    EXPECT_EQ(expected, actual);
}

TEST_F(ReachableVerticesFromTest, gTest)
{
    constexpr std::uint64_t expected{UINT64_C(1)};
    const std::uint64_t     actual{fleury::reachableVerticesFrom(graph, 'G')};
    EXPECT_EQ(expected, actual);
}
