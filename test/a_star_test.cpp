#include "gtest/gtest.h"
#include <a_star/algorithm.hpp>
#include <a_star/path.hpp>
#include <cstddef>
#include <grid/create.hpp>
#include <grid/data_structure.hpp>
#include <grid/manhattan_distance.hpp>
#include <nm/create_graph.hpp>
#include <nm/heuristic.hpp>
#include <nm/identifiers.hpp>
#include <pl/algo/ranged_algorithms.hpp>
#include <romania/city.hpp>
#include <romania/create_graph.hpp>
#include <romania/heuristic.hpp>

using namespace std;
using namespace gp;
using namespace a_star;

class AStarTest : public ::testing::Test {
public:
    using this_type = AStarTest;
    using base_type = ::testing::Test;

    AStarTest()
        : romaniaGraph{romania::createGraph()}
        , nmGraph{nm::createGraph()}
        , grid{grid::create()}
        , gridGraph{grid.graph()}
    {
    }

    struct Romania {
        using vertex_identifier = romania::City;
        using vertex_data       = nullptr_t;
        using edge_identifier   = int;
        using edge_data         = LengthEdgeData<size_t>;
        using graph_type        = DirectedGraph<
            vertex_identifier,
            vertex_data,
            edge_identifier,
            edge_data>;
        using vertex_type = graph_type::vertex_type;
        using edge_type   = graph_type::edge_type;
    };

    struct Nm {
        using vertex_identifier = string;
        using vertex_data       = nullptr_t;
        using edge_identifier   = int;
        using edge_data         = LengthEdgeData<size_t>;
        using graph_type        = DirectedGraph<
            vertex_identifier,
            vertex_data,
            edge_identifier,
            edge_data>;
        using vertex_type = graph_type::vertex_type;
        using edge_type   = graph_type::edge_type;
    };

    struct G {
        using graph_type        = grid::DataStructure::graph_type;
        using vertex_identifier = graph_type::vertex_identifier;
        using vertex_data       = graph_type::vertex_data;
        using edge_identifier   = graph_type::edge_identifier;
        using edge_data         = graph_type::edge_data;
        using vertex_type       = graph_type::vertex_type;
        using edge_type         = graph_type::edge_type;
    };

protected:
    virtual void SetUp() override {}

    virtual void TearDown() override {}

    const Romania::graph_type romaniaGraph;
    const Nm::graph_type      nmGraph;
    const grid::DataStructure grid;
    const G::graph_type       gridGraph;
};

TEST_F(AStarTest, romaniaTest)
{
    using namespace romania;
    using C = City;

    const Path<C> path{algorithm(
        romaniaGraph,
        {C::Arad},
        [](C city) { return city == C::Bucharest; },
        &heuristic,
        true)};

    const size_t    expectedTotalCost{418};
    const vector<C> expectedPath{
        C::Arad, C::Sibiu, C::RimnicuVilcea, C::Pitesti, C::Bucharest};

    EXPECT_EQ(path.g(), expectedTotalCost);
    EXPECT_EQ(path.rawPath(), expectedPath);
}

TEST_F(AStarTest, nonMonotonicTest)
{
    using namespace nm;
    const Nm::vertex_identifier startVertex{start};

    const Path<Nm::vertex_identifier> path{algorithm(
        nmGraph,
        {startVertex},
        [](const Nm::vertex_identifier& vertex) { return vertex == goal; },
        &heuristic,
        false)};

    const size_t expectedTotalCost{20};
    EXPECT_EQ(path.g(), expectedTotalCost);

    const vector<Nm::vertex_identifier> expectedPath{start, c, d, e, goal};
    EXPECT_EQ(path.rawPath(), expectedPath);
}

TEST_F(AStarTest, gridWorldTest)
{
    ASSERT_TRUE(grid.hasStart());
    const grid::Position startPosition{*grid.start()};

    ASSERT_TRUE(grid.hasGoal());
    const grid::Position goalPosition{*grid.goal()};

    const Path<G::vertex_identifier> path{algorithm(
        gridGraph,
        {startPosition},
        [&goalPosition](const G::vertex_identifier& position) {
            return position == goalPosition;
        },
        [&goalPosition](const grid::Position& position) {
            return grid::manhattanDistance(position, goalPosition);
        },
        true)};

    const size_t expectedTotalCost{25};
    EXPECT_EQ(path.g(), expectedTotalCost);

    const auto p = [](size_t col, size_t row) {
        return grid::Position{grid::Column{col}, grid::Row{row}};
    };

    const vector<grid::Position> expectedPath{
        p(0, 12), p(0, 11), p(0, 10), p(0, 9),  p(0, 8), p(0, 7), p(0, 6),
        p(0, 5),  p(0, 4),  p(0, 3),  p(0, 2),  p(0, 1), p(1, 1), p(2, 1),
        p(3, 1),  p(4, 1),  p(5, 1),  p(6, 1),  p(7, 1), p(8, 1), p(9, 1),
        p(10, 1), p(11, 1), p(12, 1), p(13, 1), p(13, 2)};
    EXPECT_EQ(path.rawPath(), expectedPath);
}
