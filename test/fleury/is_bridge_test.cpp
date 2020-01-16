#include "gtest/gtest.h"
#include <array>
#include <fleury/is_bridge.hpp>
#include <fleury/is_bridge_test_graph.hpp>

using namespace gp;

class IsBridgeTest : public ::testing::Test {
protected:
    const fleury::is_bridge_test_graph_types::graph_type graph{
        fleury::isBridgeTestGraph()};

    static bool expected(
        fleury::is_bridge_test_graph_types::edge_identifier edgeIdentifier)
    {
        return expectedArray.at(edgeIdentifier - 1U);
    }

private:
    static constexpr std::array<bool, 9U> expectedArray{/* Edge 1 */ false,
                                                        /* Edge 2 */ false,
                                                        /* Edge 3 */ false,
                                                        /* Edge 4 */ true,
                                                        /* Edge 5 */ true,
                                                        /* Edge 6 */ false,
                                                        /* Edge 7 */ false,
                                                        /* Edge 8 */ false,
                                                        /* Edge 9 */ false};
};

TEST_F(IsBridgeTest, bridgeTest)
{
    EXPECT_EQ(expected(1), fleury::isBridge(graph, 1));
    EXPECT_EQ(expected(2), fleury::isBridge(graph, 2));
    EXPECT_EQ(expected(3), fleury::isBridge(graph, 3));
    EXPECT_EQ(expected(4), fleury::isBridge(graph, 4));
    EXPECT_EQ(expected(5), fleury::isBridge(graph, 5));
    EXPECT_EQ(expected(6), fleury::isBridge(graph, 6));
    EXPECT_EQ(expected(7), fleury::isBridge(graph, 7));
    EXPECT_EQ(expected(8), fleury::isBridge(graph, 8));
    EXPECT_EQ(expected(9), fleury::isBridge(graph, 9));

    EXPECT_EQ(expected(1), fleury::isBridge(graph, -1));
    EXPECT_EQ(expected(2), fleury::isBridge(graph, -2));
    EXPECT_EQ(expected(3), fleury::isBridge(graph, -3));
    EXPECT_EQ(expected(4), fleury::isBridge(graph, -4));
    EXPECT_EQ(expected(5), fleury::isBridge(graph, -5));
    EXPECT_EQ(expected(6), fleury::isBridge(graph, -6));
    EXPECT_EQ(expected(7), fleury::isBridge(graph, -7));
    EXPECT_EQ(expected(8), fleury::isBridge(graph, -8));
    EXPECT_EQ(expected(9), fleury::isBridge(graph, -9));
}
