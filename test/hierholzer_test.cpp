#include "gtest/gtest.h"
#include <hierholzer/algorithm.hpp>
#include <hierholzer/algorithm_test_graph.hpp>

using namespace gp;
using namespace hierholzer::algorithm_test_graph_types;

class HierholzerTest : public ::testing::Test {
protected:
    const graph_type graph{hierholzer::algorithmTestGraph()};
};

TEST_F(HierholzerTest, isCircle)
{
    const std::vector<edge_identifier> result{hierholzer::algorithm(graph)};

    ASSERT_FALSE(result.empty());

    const edge_identifier& first{result.front()};
    const edge_identifier& last{result.back()};

    const tl::optional<vertex_identifier> firstSource{graph.source(first)};
    const tl::optional<vertex_identifier> lastTarget{graph.target(last)};

    ASSERT_TRUE(firstSource.has_value());
    ASSERT_TRUE(lastTarget.has_value());

    EXPECT_EQ(*firstSource, *lastTarget);
}

TEST_F(HierholzerTest, hasAllEdges)
{
    const std::vector<edge_identifier> result{hierholzer::algorithm(graph)};

    const auto contains = [&result](int v1, int v2) {
        return ::gp::contains(result, (v1 * 10) + v2)
               or ::gp::contains(result, (v2 * 10) + v1);
    };

    EXPECT_TRUE(contains(1, 2));
    EXPECT_TRUE(contains(1, 3));
    EXPECT_TRUE(contains(2, 3));
    EXPECT_TRUE(contains(2, 4));
    EXPECT_TRUE(contains(2, 5));
    EXPECT_TRUE(contains(3, 4));
    EXPECT_TRUE(contains(3, 8));
    EXPECT_TRUE(contains(5, 6));
    EXPECT_TRUE(contains(5, 7));
    EXPECT_TRUE(contains(5, 9));
    EXPECT_TRUE(contains(6, 7));
    EXPECT_TRUE(contains(8, 9));
}

TEST_F(HierholzerTest, isTraversable)
{
    const std::vector<edge_identifier> result{hierholzer::algorithm(graph)};

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
