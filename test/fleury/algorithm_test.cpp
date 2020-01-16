#include "gtest/gtest.h"
#include <ciso646>
#include <contains.hpp>
#include <fleury/algorithm.hpp>
#include <fleury/algorithm_test_graph.hpp>

using namespace gp;
using namespace fleury::algorithm_test_graph_types;

class FleuryTest : public ::testing::Test {
protected:
    const fleury::algorithm_test_graph_types::graph_type graph{
        fleury::algorithmTestGraph()};

    const std::vector<edge_identifier> result{fleury::algorithm(graph)};
};

TEST_F(FleuryTest, isCircle)
{
    ASSERT_FALSE(result.empty());

    const edge_identifier& first{result.front()};
    const edge_identifier& last{result.back()};

    const tl::optional<vertex_identifier> firstSource{graph.source(first)};
    const tl::optional<vertex_identifier> lastTarget{graph.target(last)};

    ASSERT_TRUE(firstSource.has_value());
    ASSERT_TRUE(lastTarget.has_value());

    EXPECT_EQ(*firstSource, *lastTarget);
}

TEST_F(FleuryTest, hasAllEdges)
{
    const auto contains = [this](int val) {
        return ::gp::contains(result, val) or ::gp::contains(result, -val);
    };

    EXPECT_TRUE(contains(1));
    EXPECT_TRUE(contains(2));
    EXPECT_TRUE(contains(3));
    EXPECT_TRUE(contains(4));
    EXPECT_TRUE(contains(5));
    EXPECT_TRUE(contains(6));
    EXPECT_TRUE(contains(7));
    EXPECT_TRUE(contains(8));
    EXPECT_TRUE(contains(9));
    EXPECT_TRUE(contains(10));
    EXPECT_TRUE(contains(11));
    EXPECT_TRUE(contains(12));
    EXPECT_TRUE(contains(13));
}

TEST_F(FleuryTest, isTraversable)
{
    ASSERT_FALSE(result.empty());

    vertex_identifier previousTarget{};
    vertex_identifier currentSource{};

    for (std::size_t i{}; i < result.size(); ++i) {
        const edge_identifier cur{result[i]};

        ASSERT_TRUE(graph.hasEdge(cur));

        const tl::optional<vertex_identifier> src{graph.source(cur)};

        const tl::optional<vertex_identifier> target{graph.target(cur)};

        ASSERT_TRUE(src.has_value());
        ASSERT_TRUE(target.has_value());

        currentSource = *src;

        if (i != 0U) {
            previousTarget = graph.target(result[i - 1]).value();

            EXPECT_EQ(currentSource, previousTarget);
        }
    }
}
