#include "gtest/gtest.h"
#include <bellman_ford/algorithm.hpp>
#include <bellman_ford/negative_cycle.hpp>
#include <bellman_ford/negative_edge_graph.hpp>
#include <bellman_ford/positive_cycle.hpp>
#include <directed_graph.hpp>
#include <length_edge_data.hpp>
#include <nm/create_graph.hpp>
#include <nm/identifiers.hpp>
#include <romania/city.hpp>
#include <romania/create_graph.hpp>
#include <string>

using namespace std;
using namespace gp;

class BellmanFordTest : public ::testing::Test {
public:
    using this_type = BellmanFordTest;
    using base_type = ::testing::Test;

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
        using vertex_type = typename graph_type::vertex_type;
        using edge_type   = typename graph_type::edge_type;
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
        using vertex_type = typename graph_type::vertex_type;
        using edge_type   = typename graph_type::edge_type;
    };

protected:
    virtual void SetUp() override
    {
        romaniaGraph       = romania::createGraph();
        nmGraph            = nm::createGraph();
        negativeEdgeGraph  = bellman_ford::NegativeEdgeGraph::create();
        negativeCycleGraph = bellman_ford::NegativeCycle::create();
        positiveCycleGraph = bellman_ford::PositiveCycle::create();
    }

    virtual void TearDown() override {}

    Romania::graph_type                         romaniaGraph;
    Nm::graph_type                              nmGraph;
    bellman_ford::NegativeEdgeGraph::graph_type negativeEdgeGraph;
    bellman_ford::NegativeCycle::graph_type     negativeCycleGraph;
    bellman_ford::PositiveCycle::graph_type     positiveCycleGraph;
};

TEST_F(BellmanFordTest, romaniaTest)
{
    using namespace romania;
    using C = City;

    const Romania::vertex_identifier startCity{C::Arad};
    const auto lengthInvocable = [](const Romania::edge_type& edge) {
        return edge.data().edgeLength();
    };

    const ShortestPaths<Romania::vertex_identifier, int32_t> result{
        bellman_ford::algorithm(romaniaGraph, startCity, lengthInvocable)};

    // Test distances
    const int32_t aradExpectedDistance{0};
    const int32_t bucharestExpectedDistance{418};
    const int32_t craiovaExpectedDistance{366};
    const int32_t dobretaExpectedDistance{374};
    const int32_t eforieExpectedDistance{687};
    const int32_t fagarasExpectedDistance{239};
    const int32_t giurgiuExpectedDistance{508};
    const int32_t hirsovaExpectedDistance{601};
    const int32_t iasiExpectedDistance{737};
    const int32_t lugojExpectedDistance{229};
    const int32_t mehadiaExpectedDistance{299};
    const int32_t neamtExpectedDistance{824};
    const int32_t oradeaExpectedDistance{146};
    const int32_t pitestiExpectedDistance{317};
    const int32_t rimnicuVilceaExpectedDistance{220};
    const int32_t sibiuExpectedDistance{140};
    const int32_t timisoaraExpectedDistance{118};
    const int32_t urziceniExpectedDistance{503};
    const int32_t vasluiExpectedDistance{645};
    const int32_t zerindExpectedDistance{75};

    EXPECT_EQ(result.distanceTo(C::Arad), aradExpectedDistance);
    EXPECT_EQ(result.distanceTo(C::Bucharest), bucharestExpectedDistance);
    EXPECT_EQ(result.distanceTo(C::Craiova), craiovaExpectedDistance);
    EXPECT_EQ(result.distanceTo(C::Dobreta), dobretaExpectedDistance);
    EXPECT_EQ(result.distanceTo(C::Eforie), eforieExpectedDistance);
    EXPECT_EQ(result.distanceTo(C::Fagaras), fagarasExpectedDistance);
    EXPECT_EQ(result.distanceTo(C::Giurgiu), giurgiuExpectedDistance);
    EXPECT_EQ(result.distanceTo(C::Hirsova), hirsovaExpectedDistance);
    EXPECT_EQ(result.distanceTo(C::Iasi), iasiExpectedDistance);
    EXPECT_EQ(result.distanceTo(C::Lugoj), lugojExpectedDistance);
    EXPECT_EQ(result.distanceTo(C::Mehadia), mehadiaExpectedDistance);
    EXPECT_EQ(result.distanceTo(C::Neamt), neamtExpectedDistance);
    EXPECT_EQ(result.distanceTo(C::Oradea), oradeaExpectedDistance);
    EXPECT_EQ(result.distanceTo(C::Pitesti), pitestiExpectedDistance);
    EXPECT_EQ(
        result.distanceTo(C::RimnicuVilcea), rimnicuVilceaExpectedDistance);
    EXPECT_EQ(result.distanceTo(C::Sibiu), sibiuExpectedDistance);
    EXPECT_EQ(result.distanceTo(C::Timisoara), timisoaraExpectedDistance);
    EXPECT_EQ(result.distanceTo(C::Urziceni), urziceniExpectedDistance);
    EXPECT_EQ(result.distanceTo(C::Vaslui), vasluiExpectedDistance);
    EXPECT_EQ(result.distanceTo(C::Zerind), zerindExpectedDistance);

    // Test paths
    using Path = vector<C>;

    const Path aradExpectedPath{C::Arad};
    const Path bucharestExpectedPath{
        C::Arad, C::Sibiu, C::RimnicuVilcea, C::Pitesti, C::Bucharest};
    const Path craiovaExpectedPath{
        C::Arad, C::Sibiu, C::RimnicuVilcea, C::Craiova};
    const Path dobretaExpectedPath{
        C::Arad, C::Timisoara, C::Lugoj, C::Mehadia, C::Dobreta};
    const Path eforieExpectedPath{C::Arad,
                                  C::Sibiu,
                                  C::RimnicuVilcea,
                                  C::Pitesti,
                                  C::Bucharest,
                                  C::Urziceni,
                                  C::Hirsova,
                                  C::Eforie};
    const Path fagarasExpectedPath{C::Arad, C::Sibiu, C::Fagaras};
    const Path giurgiuExpectedPath{C::Arad,
                                   C::Sibiu,
                                   C::RimnicuVilcea,
                                   C::Pitesti,
                                   C::Bucharest,
                                   C::Giurgiu};
    const Path hirsovaExpectedPath{C::Arad,
                                   C::Sibiu,
                                   C::RimnicuVilcea,
                                   C::Pitesti,
                                   C::Bucharest,
                                   C::Urziceni,
                                   C::Hirsova};
    const Path iasiExpectedPath{C::Arad,
                                C::Sibiu,
                                C::RimnicuVilcea,
                                C::Pitesti,
                                C::Bucharest,
                                C::Urziceni,
                                C::Vaslui,
                                C::Iasi};
    const Path lugojExpectedPath{C::Arad, C::Timisoara, C::Lugoj};
    const Path mehadiaExpectedPath{C::Arad, C::Timisoara, C::Lugoj, C::Mehadia};
    const Path neamtExpectedPath{C::Arad,
                                 C::Sibiu,
                                 C::RimnicuVilcea,
                                 C::Pitesti,
                                 C::Bucharest,
                                 C::Urziceni,
                                 C::Vaslui,
                                 C::Iasi,
                                 C::Neamt};
    const Path oradeaExpectedPath{C::Arad, C::Zerind, C::Oradea};
    const Path pitestiExpectedPath{
        C::Arad, C::Sibiu, C::RimnicuVilcea, C::Pitesti};
    const Path rimnicuVilceaExpectedPath{C::Arad, C::Sibiu, C::RimnicuVilcea};
    const Path sibiuExpectedPath{C::Arad, C::Sibiu};
    const Path timisoaraExpectedPath{C::Arad, C::Timisoara};
    const Path urziceniExpectedPath{C::Arad,
                                    C::Sibiu,
                                    C::RimnicuVilcea,
                                    C::Pitesti,
                                    C::Bucharest,
                                    C::Urziceni};
    const Path vasluiExpectedPath{C::Arad,
                                  C::Sibiu,
                                  C::RimnicuVilcea,
                                  C::Pitesti,
                                  C::Bucharest,
                                  C::Urziceni,
                                  C::Vaslui};
    const Path zerindExpectedPath{C::Arad, C::Zerind};

    EXPECT_EQ(result.shortestPathTo(C::Arad), aradExpectedPath);
    EXPECT_EQ(result.shortestPathTo(C::Bucharest), bucharestExpectedPath);
    EXPECT_EQ(result.shortestPathTo(C::Craiova), craiovaExpectedPath);
    EXPECT_EQ(result.shortestPathTo(C::Dobreta), dobretaExpectedPath);
    EXPECT_EQ(result.shortestPathTo(C::Eforie), eforieExpectedPath);
    EXPECT_EQ(result.shortestPathTo(C::Fagaras), fagarasExpectedPath);
    EXPECT_EQ(result.shortestPathTo(C::Giurgiu), giurgiuExpectedPath);
    EXPECT_EQ(result.shortestPathTo(C::Hirsova), hirsovaExpectedPath);
    EXPECT_EQ(result.shortestPathTo(C::Iasi), iasiExpectedPath);
    EXPECT_EQ(result.shortestPathTo(C::Lugoj), lugojExpectedPath);
    EXPECT_EQ(result.shortestPathTo(C::Mehadia), mehadiaExpectedPath);
    EXPECT_EQ(result.shortestPathTo(C::Neamt), neamtExpectedPath);
    EXPECT_EQ(result.shortestPathTo(C::Oradea), oradeaExpectedPath);
    EXPECT_EQ(result.shortestPathTo(C::Pitesti), pitestiExpectedPath);
    EXPECT_EQ(
        result.shortestPathTo(C::RimnicuVilcea), rimnicuVilceaExpectedPath);
    EXPECT_EQ(result.shortestPathTo(C::Sibiu), sibiuExpectedPath);
    EXPECT_EQ(result.shortestPathTo(C::Timisoara), timisoaraExpectedPath);
    EXPECT_EQ(result.shortestPathTo(C::Urziceni), urziceniExpectedPath);
    EXPECT_EQ(result.shortestPathTo(C::Vaslui), vasluiExpectedPath);
    EXPECT_EQ(result.shortestPathTo(C::Zerind), zerindExpectedPath);
}

TEST_F(BellmanFordTest, nonMonotonicTest)
{
    using namespace nm;

    const Nm::vertex_identifier startVertex{start};
    const auto                  lengthInvocable
        = [](const Nm::edge_type& edge) { return edge.data().edgeLength(); };

    const ShortestPaths<Nm::vertex_identifier, int32_t> result{
        bellman_ford::algorithm(nmGraph, startVertex, lengthInvocable)};

    // Test distances
    const int32_t startExpectedDistance{0};
    const int32_t bExpectedDistance{5};
    const int32_t cExpectedDistance{5};
    const int32_t dExpectedDistance{10};
    const int32_t eExpectedDistance{15};
    const int32_t goalExpectedDistance{20};

    EXPECT_EQ(result.distanceTo(start), startExpectedDistance);
    EXPECT_EQ(result.distanceTo(b), bExpectedDistance);
    EXPECT_EQ(result.distanceTo(c), cExpectedDistance);
    EXPECT_EQ(result.distanceTo(d), dExpectedDistance);
    EXPECT_EQ(result.distanceTo(e), eExpectedDistance);
    EXPECT_EQ(result.distanceTo(goal), goalExpectedDistance);

    // Test paths
    using Path = vector<string>;
    const Path startExpectedPath{start};
    const Path bExpectedPath{start, b};
    const Path cExpectedPath{start, c};
    const Path dExpectedPath{start, c, d};
    const Path eExpectedPath{start, c, d, e};
    const Path goalExpectedPath{start, c, d, e, goal};

    EXPECT_EQ(result.shortestPathTo(start), startExpectedPath);
    EXPECT_EQ(result.shortestPathTo(b), bExpectedPath);
    EXPECT_EQ(result.shortestPathTo(c), cExpectedPath);
    EXPECT_EQ(result.shortestPathTo(d), dExpectedPath);
    EXPECT_EQ(result.shortestPathTo(e), eExpectedPath);
    EXPECT_EQ(result.shortestPathTo(goal), goalExpectedPath);
}

TEST_F(BellmanFordTest, negativeEdgeTest)
{
    const string startVertex{"a"};
    const auto   lengthInvocable
        = [](const bellman_ford::NegativeEdgeGraph::graph_type::edge_type& e) {
              return e.data().edgeLength();
          };

    const ShortestPaths<
        bellman_ford::NegativeEdgeGraph::vertex_identifier,
        std::int32_t>
        result{bellman_ford::algorithm(
            negativeEdgeGraph, startVertex, lengthInvocable)};

    // Test distances
    const int32_t aExpectedDist{0}, bExpectedDist{10}, cExpectedDist{20},
        dExpectedDist{40}, eExpectedDist{20}, fExpectedDist{21};

    EXPECT_EQ(result.distanceTo("a"), aExpectedDist);
    EXPECT_EQ(result.distanceTo("b"), bExpectedDist);
    EXPECT_EQ(result.distanceTo("c"), cExpectedDist);
    EXPECT_EQ(result.distanceTo("d"), dExpectedDist);
    EXPECT_EQ(result.distanceTo("e"), eExpectedDist);
    EXPECT_EQ(result.distanceTo("f"), fExpectedDist);

    // Test paths
    using Path = vector<string>;
    const Path aExpectedPath{"a"}, bExpectedPath{"a", "b"},
        cExpectedPath{"a", "c"}, dExpectedPath{"a", "c", "d"},
        eExpectedPath{"a", "b", "e"}, fExpectedPath{"a", "b", "e", "f"};

    EXPECT_EQ(result.shortestPathTo("a"), aExpectedPath);
    EXPECT_EQ(result.shortestPathTo("b"), bExpectedPath);
    EXPECT_EQ(result.shortestPathTo("c"), cExpectedPath);
    EXPECT_EQ(result.shortestPathTo("d"), dExpectedPath);
    EXPECT_EQ(result.shortestPathTo("e"), eExpectedPath);
    EXPECT_EQ(result.shortestPathTo("f"), fExpectedPath);
}

TEST_F(BellmanFordTest, negativeCycleTest)
{
    const string startVertex{"a"};
    const auto   lengthInvocable
        = [](const bellman_ford::NegativeCycle::graph_type::edge_type& e) {
              return e.data().edgeLength();
          };

    const auto invokeSample = [this, &startVertex, &lengthInvocable] {
        bellman_ford::algorithm(
            negativeCycleGraph, startVertex, lengthInvocable);
    };

    EXPECT_THROW(invokeSample(), std::runtime_error);
}

TEST_F(BellmanFordTest, positiveCycleTest)
{
    const string startVertex{"a"};
    const auto   lengthInvocable
        = [](const bellman_ford::PositiveCycle::graph_type::edge_type& e) {
              return e.data().edgeLength();
          };

    const ShortestPaths<
        bellman_ford::PositiveCycle::vertex_identifier,
        std::int32_t>
        result{bellman_ford::algorithm(
            positiveCycleGraph, startVertex, lengthInvocable)};

    // Test distances
    const int32_t aExpectedDist{0}, bExpectedDist{10}, cExpectedDist{20},
        dExpectedDist{32}, eExpectedDist{27}, fExpectedDist{42};

    EXPECT_EQ(result.distanceTo("a"), aExpectedDist);
    EXPECT_EQ(result.distanceTo("b"), bExpectedDist);
    EXPECT_EQ(result.distanceTo("c"), cExpectedDist);
    EXPECT_EQ(result.distanceTo("d"), dExpectedDist);
    EXPECT_EQ(result.distanceTo("e"), eExpectedDist);
    EXPECT_EQ(result.distanceTo("f"), fExpectedDist);

    // Test paths
    using Path = vector<string>;
    const Path aExpectedPath{"a"}, bExpectedPath{"a", "b"},
        cExpectedPath{"a", "b", "c"}, dExpectedPath{"a", "b", "c", "e", "d"},
        eExpectedPath{"a", "b", "c", "e"},
        fExpectedPath{"a", "b", "c", "e", "f"};

    EXPECT_EQ(result.shortestPathTo("a"), aExpectedPath);
    EXPECT_EQ(result.shortestPathTo("b"), bExpectedPath);
    EXPECT_EQ(result.shortestPathTo("c"), cExpectedPath);
    EXPECT_EQ(result.shortestPathTo("d"), dExpectedPath);
    EXPECT_EQ(result.shortestPathTo("e"), eExpectedPath);
    EXPECT_EQ(result.shortestPathTo("f"), fExpectedPath);
}
