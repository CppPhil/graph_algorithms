#include "gtest/gtest.h"
#include <ciso646>
#include <cstdint>
#include <directed_graph.hpp>
#include <string>
#include <tl/optional.hpp>
#include <type_traits>

using namespace std;
using namespace gp;

enum Vertices : uint32_t {
    V1 = UINT32_C(0),
    V2 = UINT32_C(1),
    V3 = UINT32_C(2),
    V4 = UINT32_C(3),
    V5 = UINT32_C(4)
};

inline bool operator==(Vertices lhs, Vertices rhs) noexcept
{
    return static_cast<uint32_t>(lhs) == static_cast<uint32_t>(rhs);
}

inline bool operator!=(Vertices lhs, Vertices rhs) noexcept
{
    return not(lhs == rhs);
}

enum Edges : uint32_t {
    E1 = UINT32_C(0),
    E2 = UINT32_C(1),
    E3 = UINT32_C(2),
    E4 = UINT32_C(3),
    E5 = UINT32_C(4),
    E6 = UINT32_C(5),
    E7 = UINT32_C(6),
    E8 = UINT32_C(7),
    E9 = UINT32_C(8)
};

inline bool operator==(Edges lhs, Edges rhs) noexcept
{
    return static_cast<uint32_t>(lhs) == static_cast<uint32_t>(rhs);
}

inline bool operator!=(Edges lhs, Edges rhs) noexcept
{
    return not(lhs == rhs);
}

class DirectedGraphTest : public ::testing::Test {
public:
    using this_type  = DirectedGraphTest;
    using base_type  = ::testing::Test;
    using graph_type = DirectedGraph<Vertices, string, Edges, string>;

protected:
    virtual void SetUp() override
    {
        (void)g.addVertex(V1, "vertex 1");
        (void)g.addVertex(V2, "vertex 2");
        (void)g.addVertex(V3, "vertex 3");
        (void)g.addVertex(V4, "vertex 4");
        (void)g.addVertex(V5, "vertex 5");

        (void)g.addEdge(E1, V1, V1, "edge 1");
        (void)g.addEdge(E2, V1, V2, "edge 2");
        (void)g.addEdge(E3, V2, V1, "edge 3");
        (void)g.addEdge(E4, V2, V3, "edge 4");
        (void)g.addEdge(E5, V3, V4, "edge 5");
        (void)g.addEdge(E6, V4, V5, "edge 6");
        (void)g.addEdge(E7, V5, V2, "edge 7");
        (void)g.addEdge(E8, V5, V1, "edge 8");
        (void)g.addEdge(E9, V5, V5, "edge 9");
    }

    virtual void TearDown() override {}

    graph_type g;

    static const graph_type empty;
};

const DirectedGraph<Vertices, string, Edges, string> DirectedGraphTest::empty;

TEST_F(DirectedGraphTest, fetchVertex)
{
    const tl::optional<const Vertex<Vertices, string>&> opt1{g.vertex(V1)};
    const tl::optional<const Vertex<Vertices, string>&> opt2{g.vertex(V2)};
    const tl::optional<const Vertex<Vertices, string>&> opt3{g.vertex(V3)};
    const tl::optional<const Vertex<Vertices, string>&> opt4{g.vertex(V4)};
    const tl::optional<const Vertex<Vertices, string>&> opt5{g.vertex(V5)};

    ASSERT_TRUE(opt1.has_value());
    ASSERT_TRUE(opt2.has_value());
    ASSERT_TRUE(opt3.has_value());
    ASSERT_TRUE(opt4.has_value());
    ASSERT_TRUE(opt5.has_value());

    EXPECT_EQ(opt1->identifier(), V1);
    EXPECT_EQ(opt2->identifier(), V2);
    EXPECT_EQ(opt3->identifier(), V3);
    EXPECT_EQ(opt4->identifier(), V4);
    EXPECT_EQ(opt5->identifier(), V5);

    EXPECT_EQ(opt1->data(), string("vertex 1"));
    EXPECT_EQ(opt2->data(), string("vertex 2"));
    EXPECT_EQ(opt3->data(), string("vertex 3"));
    EXPECT_EQ(opt4->data(), string("vertex 4"));
    EXPECT_EQ(opt5->data(), string("vertex 5"));
}

TEST_F(DirectedGraphTest, fetchVertexEmpty)
{
    const tl::optional<const Vertex<Vertices, string>&> opt1{empty.vertex(V1)};
    const tl::optional<const Vertex<Vertices, string>&> opt2{empty.vertex(V2)};
    const tl::optional<const Vertex<Vertices, string>&> opt3{empty.vertex(V3)};
    const tl::optional<const Vertex<Vertices, string>&> opt4{empty.vertex(V4)};
    const tl::optional<const Vertex<Vertices, string>&> opt5{empty.vertex(V5)};

    EXPECT_FALSE(opt1.has_value());
    EXPECT_FALSE(opt2.has_value());
    EXPECT_FALSE(opt3.has_value());
    EXPECT_FALSE(opt4.has_value());
    EXPECT_FALSE(opt5.has_value());
}

TEST_F(DirectedGraphTest, fetchEdge)
{
    const tl::optional<const Edge<Edges, string, Vertices>&> opt1{g.edge(E1)};
    const tl::optional<const Edge<Edges, string, Vertices>&> opt2{g.edge(E2)};
    const tl::optional<const Edge<Edges, string, Vertices>&> opt3{g.edge(E3)};
    const tl::optional<const Edge<Edges, string, Vertices>&> opt4{g.edge(E4)};
    const tl::optional<const Edge<Edges, string, Vertices>&> opt5{g.edge(E5)};
    const tl::optional<const Edge<Edges, string, Vertices>&> opt6{g.edge(E6)};
    const tl::optional<const Edge<Edges, string, Vertices>&> opt7{g.edge(E7)};
    const tl::optional<const Edge<Edges, string, Vertices>&> opt8{g.edge(E8)};
    const tl::optional<const Edge<Edges, string, Vertices>&> opt9{g.edge(E9)};

    ASSERT_TRUE(opt1.has_value());
    ASSERT_TRUE(opt2.has_value());
    ASSERT_TRUE(opt3.has_value());
    ASSERT_TRUE(opt4.has_value());
    ASSERT_TRUE(opt5.has_value());
    ASSERT_TRUE(opt6.has_value());
    ASSERT_TRUE(opt7.has_value());
    ASSERT_TRUE(opt8.has_value());
    ASSERT_TRUE(opt9.has_value());

    EXPECT_EQ(opt1->identifier(), E1);
    EXPECT_EQ(opt2->identifier(), E2);
    EXPECT_EQ(opt3->identifier(), E3);
    EXPECT_EQ(opt4->identifier(), E4);
    EXPECT_EQ(opt5->identifier(), E5);
    EXPECT_EQ(opt6->identifier(), E6);
    EXPECT_EQ(opt7->identifier(), E7);
    EXPECT_EQ(opt8->identifier(), E8);
    EXPECT_EQ(opt9->identifier(), E9);

    EXPECT_EQ(opt1->source(), V1);
    EXPECT_EQ(opt2->source(), V1);
    EXPECT_EQ(opt3->source(), V2);
    EXPECT_EQ(opt4->source(), V2);
    EXPECT_EQ(opt5->source(), V3);
    EXPECT_EQ(opt6->source(), V4);
    EXPECT_EQ(opt7->source(), V5);
    EXPECT_EQ(opt8->source(), V5);
    EXPECT_EQ(opt9->source(), V5);

    EXPECT_EQ(opt1->target(), V1);
    EXPECT_EQ(opt2->target(), V2);
    EXPECT_EQ(opt3->target(), V1);
    EXPECT_EQ(opt4->target(), V3);
    EXPECT_EQ(opt5->target(), V4);
    EXPECT_EQ(opt6->target(), V5);
    EXPECT_EQ(opt7->target(), V2);
    EXPECT_EQ(opt8->target(), V1);
    EXPECT_EQ(opt9->target(), V5);

    EXPECT_EQ(opt1->data(), string("edge 1"));
    EXPECT_EQ(opt2->data(), string("edge 2"));
    EXPECT_EQ(opt3->data(), string("edge 3"));
    EXPECT_EQ(opt4->data(), string("edge 4"));
    EXPECT_EQ(opt5->data(), string("edge 5"));
    EXPECT_EQ(opt6->data(), string("edge 6"));
    EXPECT_EQ(opt7->data(), string("edge 7"));
    EXPECT_EQ(opt8->data(), string("edge 8"));
    EXPECT_EQ(opt9->data(), string("edge 9"));
}

TEST_F(DirectedGraphTest, fetchEdgeEmpty)
{
    const tl::optional<const Edge<Edges, string, Vertices>&> opt1{
        empty.edge(E1)};
    const tl::optional<const Edge<Edges, string, Vertices>&> opt2{
        empty.edge(E2)};
    const tl::optional<const Edge<Edges, string, Vertices>&> opt3{
        empty.edge(E3)};
    const tl::optional<const Edge<Edges, string, Vertices>&> opt4{
        empty.edge(E4)};
    const tl::optional<const Edge<Edges, string, Vertices>&> opt5{
        empty.edge(E5)};
    const tl::optional<const Edge<Edges, string, Vertices>&> opt6{
        empty.edge(E6)};
    const tl::optional<const Edge<Edges, string, Vertices>&> opt7{
        empty.edge(E7)};
    const tl::optional<const Edge<Edges, string, Vertices>&> opt8{
        empty.edge(E8)};
    const tl::optional<const Edge<Edges, string, Vertices>&> opt9{
        empty.edge(E9)};

    EXPECT_FALSE(opt1.has_value());
    EXPECT_FALSE(opt2.has_value());
    EXPECT_FALSE(opt3.has_value());
    EXPECT_FALSE(opt4.has_value());
    EXPECT_FALSE(opt5.has_value());
    EXPECT_FALSE(opt6.has_value());
    EXPECT_FALSE(opt7.has_value());
    EXPECT_FALSE(opt8.has_value());
    EXPECT_FALSE(opt9.has_value());
}

TEST_F(DirectedGraphTest, vertexCount)
{
    EXPECT_EQ(g.vertexCount(), 5U);
    EXPECT_EQ(empty.vertexCount(), 0U);
}

TEST_F(DirectedGraphTest, edgeCount)
{
    EXPECT_EQ(g.edgeCount(), 9U);
    EXPECT_EQ(empty.edgeCount(), 0U);
}

TEST_F(DirectedGraphTest, hasVertices)
{
    EXPECT_TRUE(g.hasVertices());
    EXPECT_FALSE(empty.hasVertices());
}

TEST_F(DirectedGraphTest, hasEdges)
{
    EXPECT_TRUE(g.hasEdges());
    EXPECT_FALSE(empty.hasEdges());
}

TEST_F(DirectedGraphTest, hasVertex)
{
    EXPECT_TRUE(g.hasVertex(V1));
    EXPECT_TRUE(g.hasVertex(V2));
    EXPECT_TRUE(g.hasVertex(V3));
    EXPECT_TRUE(g.hasVertex(V4));
    EXPECT_TRUE(g.hasVertex(V5));
}

TEST_F(DirectedGraphTest, hasVertexEmpty)
{
    EXPECT_FALSE(empty.hasVertex(V1));
    EXPECT_FALSE(empty.hasVertex(V2));
    EXPECT_FALSE(empty.hasVertex(V3));
    EXPECT_FALSE(empty.hasVertex(V4));
    EXPECT_FALSE(empty.hasVertex(V5));
}

TEST_F(DirectedGraphTest, hasEdge)
{
    EXPECT_TRUE(g.hasEdge(E1));
    EXPECT_TRUE(g.hasEdge(E2));
    EXPECT_TRUE(g.hasEdge(E3));
    EXPECT_TRUE(g.hasEdge(E4));
    EXPECT_TRUE(g.hasEdge(E5));
    EXPECT_TRUE(g.hasEdge(E6));
    EXPECT_TRUE(g.hasEdge(E7));
    EXPECT_TRUE(g.hasEdge(E8));
    EXPECT_TRUE(g.hasEdge(E9));
}

TEST_F(DirectedGraphTest, hasEdgeEmpty)
{
    EXPECT_FALSE(empty.hasEdge(E1));
    EXPECT_FALSE(empty.hasEdge(E2));
    EXPECT_FALSE(empty.hasEdge(E3));
    EXPECT_FALSE(empty.hasEdge(E4));
    EXPECT_FALSE(empty.hasEdge(E5));
    EXPECT_FALSE(empty.hasEdge(E6));
    EXPECT_FALSE(empty.hasEdge(E7));
    EXPECT_FALSE(empty.hasEdge(E8));
    EXPECT_FALSE(empty.hasEdge(E9));
}

TEST_F(DirectedGraphTest, vertices)
{
    const std::vector<Vertex<Vertices, string>>& v{g.vertices()};
    const std::vector<Vertex<Vertices, string>>  expected{
        Vertex<Vertices, string>{V1, "vertex 1"},
        Vertex<Vertices, string>{V2, "vertex 2"},
        Vertex<Vertices, string>{V3, "vertex 3"},
        Vertex<Vertices, string>{V4, "vertex 4"},
        Vertex<Vertices, string>{V5, "vertex 5"}};
    EXPECT_EQ(v, expected);
}

TEST_F(DirectedGraphTest, verticesEmpty)
{
    EXPECT_TRUE(empty.vertices().empty());
}

TEST_F(DirectedGraphTest, edges)
{
    const std::vector<Edge<Edges, string, Vertices>>& e{g.edges()};
    const std::vector<Edge<Edges, string, Vertices>>  expected{
        Edge<Edges, string, Vertices>{E1, V1, V1, "edge 1"},
        Edge<Edges, string, Vertices>{E2, V1, V2, "edge 2"},
        Edge<Edges, string, Vertices>{E3, V2, V1, "edge 3"},
        Edge<Edges, string, Vertices>{E4, V2, V3, "edge 4"},
        Edge<Edges, string, Vertices>{E5, V3, V4, "edge 5"},
        Edge<Edges, string, Vertices>{E6, V4, V5, "edge 6"},
        Edge<Edges, string, Vertices>{E7, V5, V2, "edge 7"},
        Edge<Edges, string, Vertices>{E8, V5, V1, "edge 8"},
        Edge<Edges, string, Vertices>{E9, V5, V5, "edge 9"},
    };

    ASSERT_EQ(e.size(), expected.size());

    for (size_t i{0U}; i < e.size(); ++i) { EXPECT_EQ(e[i], expected[i]); }
}

TEST_F(DirectedGraphTest, edgesEmpty) { EXPECT_TRUE(empty.edges().empty()); }

template<typename Ty, typename Identifier>
inline bool hasIdentifier(const Ty* ty, Identifier identifier)
{
    return ty->identifier() == identifier;
}

template<typename Cont1, typename Cont2>
inline bool hasIdentifiers(const Cont1& cont1, const Cont2& cont2)
{
    if (cont1.size() != cont2.size()) { return false; }

    for (const auto& identifier : cont2) {
        const bool foundAndOk{pl::algo::count_if(
                                  cont1,
                                  [&identifier](const auto* p) {
                                      return hasIdentifier(p, identifier);
                                  })
                              == 1};

        if (not foundAndOk) { return false; }
    }

    return true;
}

TEST_F(DirectedGraphTest, adjacentVerticesEmpty)
{
    EXPECT_TRUE(empty.adjacentVertices(V1).empty());
    EXPECT_TRUE(empty.adjacentVertices(V2).empty());
    EXPECT_TRUE(empty.adjacentVertices(V3).empty());
    EXPECT_TRUE(empty.adjacentVertices(V4).empty());
    EXPECT_TRUE(empty.adjacentVertices(V5).empty());
}

TEST_F(DirectedGraphTest, adjacentVerticesV1)
{
    const std::vector<const graph_type::vertex_type*> result{
        g.adjacentVertices(V1)};
    const std::vector<graph_type::vertex_identifier> expected{V1, V2, V5};
    EXPECT_TRUE(hasIdentifiers(result, expected));
}

TEST_F(DirectedGraphTest, adjacentVerticesV2)
{
    const std::vector<const graph_type::vertex_type*> result{
        g.adjacentVertices(V2)};
    const std::vector<graph_type::vertex_identifier> expected{V1, V3, V5};
    EXPECT_TRUE(hasIdentifiers(result, expected));
}

TEST_F(DirectedGraphTest, adjacentVerticesV3)
{
    const std::vector<const graph_type::vertex_type*> result{
        g.adjacentVertices(V3)};
    const std::vector<graph_type::vertex_identifier> expected{V2, V4};
    EXPECT_TRUE(hasIdentifiers(result, expected));
}

TEST_F(DirectedGraphTest, adjacentVerticesV4)
{
    const std::vector<const graph_type::vertex_type*> result{
        g.adjacentVertices(V4)};
    const std::vector<graph_type::vertex_identifier> expected{V3, V5};
    EXPECT_TRUE(hasIdentifiers(result, expected));
}

TEST_F(DirectedGraphTest, adjacentVerticesV5)
{
    const std::vector<const graph_type::vertex_type*> result{
        g.adjacentVertices(V5)};
    const std::vector<graph_type::vertex_identifier> expected{V1, V2, V4, V5};
    EXPECT_TRUE(hasIdentifiers(result, expected));
}

TEST_F(DirectedGraphTest, incidentEdgesEmpty)
{
    EXPECT_TRUE(empty.incidentEdges(V1).empty());
    EXPECT_TRUE(empty.incidentEdges(V2).empty());
    EXPECT_TRUE(empty.incidentEdges(V3).empty());
    EXPECT_TRUE(empty.incidentEdges(V4).empty());
    EXPECT_TRUE(empty.incidentEdges(V5).empty());
}

TEST_F(DirectedGraphTest, incidentEdges)
{
    const auto res1 = g.incidentEdges(V1);
    const auto res2 = g.incidentEdges(V2);
    const auto res3 = g.incidentEdges(V3);
    const auto res4 = g.incidentEdges(V4);
    const auto res5 = g.incidentEdges(V5);

    const std::vector<Edges> e1{E1, E2, E3, E8}, e2{E2, E3, E4, E7}, e3{E4, E5},
        e4{E5, E6}, e5{E6, E7, E8, E9};

    EXPECT_TRUE(hasIdentifiers(res1, e1));
    EXPECT_TRUE(hasIdentifiers(res2, e2));
    EXPECT_TRUE(hasIdentifiers(res3, e3));
    EXPECT_TRUE(hasIdentifiers(res4, e4));
    EXPECT_TRUE(hasIdentifiers(res5, e5));
}

TEST_F(DirectedGraphTest, incidentVerticesEmpty)
{
    EXPECT_TRUE(empty.incidentVertices(E1).empty());
    EXPECT_TRUE(empty.incidentVertices(E2).empty());
    EXPECT_TRUE(empty.incidentVertices(E3).empty());
    EXPECT_TRUE(empty.incidentVertices(E4).empty());
    EXPECT_TRUE(empty.incidentVertices(E5).empty());
    EXPECT_TRUE(empty.incidentVertices(E6).empty());
    EXPECT_TRUE(empty.incidentVertices(E7).empty());
    EXPECT_TRUE(empty.incidentVertices(E8).empty());
    EXPECT_TRUE(empty.incidentVertices(E9).empty());
}

TEST_F(DirectedGraphTest, incidentVertices)
{
    const auto res1 = g.incidentVertices(E1);
    const auto res2 = g.incidentVertices(E2);
    const auto res3 = g.incidentVertices(E3);
    const auto res4 = g.incidentVertices(E4);
    const auto res5 = g.incidentVertices(E5);
    const auto res6 = g.incidentVertices(E6);
    const auto res7 = g.incidentVertices(E7);
    const auto res8 = g.incidentVertices(E8);
    const auto res9 = g.incidentVertices(E9);

    const std::vector<Vertices> e1{V1}, e2{V1, V2}, e3{V1, V2}, e4{V2, V3},
        e5{V3, V4}, e6{V4, V5}, e7{V5, V2}, e8{V5, V1}, e9{V5};

    EXPECT_TRUE(hasIdentifiers(res1, e1));
    EXPECT_TRUE(hasIdentifiers(res2, e2));
    EXPECT_TRUE(hasIdentifiers(res3, e3));
    EXPECT_TRUE(hasIdentifiers(res4, e4));
    EXPECT_TRUE(hasIdentifiers(res5, e5));
    EXPECT_TRUE(hasIdentifiers(res6, e6));
    EXPECT_TRUE(hasIdentifiers(res7, e7));
    EXPECT_TRUE(hasIdentifiers(res8, e8));
    EXPECT_TRUE(hasIdentifiers(res9, e9));
}

TEST_F(DirectedGraphTest, sourceEmpty)
{
    EXPECT_FALSE(empty.source(E1).has_value());
    EXPECT_FALSE(empty.source(E2).has_value());
    EXPECT_FALSE(empty.source(E3).has_value());
    EXPECT_FALSE(empty.source(E4).has_value());
    EXPECT_FALSE(empty.source(E5).has_value());
    EXPECT_FALSE(empty.source(E6).has_value());
    EXPECT_FALSE(empty.source(E7).has_value());
    EXPECT_FALSE(empty.source(E8).has_value());
    EXPECT_FALSE(empty.source(E9).has_value());
}

TEST_F(DirectedGraphTest, source)
{
    const tl::optional<graph_type::vertex_identifier> opt1{g.source(E1)};
    const tl::optional<graph_type::vertex_identifier> opt2{g.source(E2)};
    const tl::optional<graph_type::vertex_identifier> opt3{g.source(E3)};
    const tl::optional<graph_type::vertex_identifier> opt4{g.source(E4)};
    const tl::optional<graph_type::vertex_identifier> opt5{g.source(E5)};
    const tl::optional<graph_type::vertex_identifier> opt6{g.source(E6)};
    const tl::optional<graph_type::vertex_identifier> opt7{g.source(E7)};
    const tl::optional<graph_type::vertex_identifier> opt8{g.source(E8)};
    const tl::optional<graph_type::vertex_identifier> opt9{g.source(E9)};

    ASSERT_TRUE(opt1.has_value());
    ASSERT_TRUE(opt2.has_value());
    ASSERT_TRUE(opt3.has_value());
    ASSERT_TRUE(opt4.has_value());
    ASSERT_TRUE(opt5.has_value());
    ASSERT_TRUE(opt6.has_value());
    ASSERT_TRUE(opt7.has_value());
    ASSERT_TRUE(opt8.has_value());
    ASSERT_TRUE(opt9.has_value());

    EXPECT_EQ(*opt1, V1);
    EXPECT_EQ(*opt2, V1);
    EXPECT_EQ(*opt3, V2);
    EXPECT_EQ(*opt4, V2);
    EXPECT_EQ(*opt5, V3);
    EXPECT_EQ(*opt6, V4);
    EXPECT_EQ(*opt7, V5);
    EXPECT_EQ(*opt8, V5);
    EXPECT_EQ(*opt9, V5);
}

TEST_F(DirectedGraphTest, targetEmpty)
{
    EXPECT_FALSE(empty.target(E1).has_value());
    EXPECT_FALSE(empty.target(E2).has_value());
    EXPECT_FALSE(empty.target(E3).has_value());
    EXPECT_FALSE(empty.target(E4).has_value());
    EXPECT_FALSE(empty.target(E5).has_value());
    EXPECT_FALSE(empty.target(E6).has_value());
    EXPECT_FALSE(empty.target(E7).has_value());
    EXPECT_FALSE(empty.target(E8).has_value());
    EXPECT_FALSE(empty.target(E9).has_value());
}

TEST_F(DirectedGraphTest, target)
{
    const tl::optional<graph_type::vertex_identifier> opt1{g.target(E1)};
    const tl::optional<graph_type::vertex_identifier> opt2{g.target(E2)};
    const tl::optional<graph_type::vertex_identifier> opt3{g.target(E3)};
    const tl::optional<graph_type::vertex_identifier> opt4{g.target(E4)};
    const tl::optional<graph_type::vertex_identifier> opt5{g.target(E5)};
    const tl::optional<graph_type::vertex_identifier> opt6{g.target(E6)};
    const tl::optional<graph_type::vertex_identifier> opt7{g.target(E7)};
    const tl::optional<graph_type::vertex_identifier> opt8{g.target(E8)};
    const tl::optional<graph_type::vertex_identifier> opt9{g.target(E9)};

    ASSERT_TRUE(opt1.has_value());
    ASSERT_TRUE(opt2.has_value());
    ASSERT_TRUE(opt3.has_value());
    ASSERT_TRUE(opt4.has_value());
    ASSERT_TRUE(opt5.has_value());
    ASSERT_TRUE(opt6.has_value());
    ASSERT_TRUE(opt7.has_value());
    ASSERT_TRUE(opt8.has_value());
    ASSERT_TRUE(opt9.has_value());

    EXPECT_EQ(*opt1, V1);
    EXPECT_EQ(*opt2, V2);
    EXPECT_EQ(*opt3, V1);
    EXPECT_EQ(*opt4, V3);
    EXPECT_EQ(*opt5, V4);
    EXPECT_EQ(*opt6, V5);
    EXPECT_EQ(*opt7, V2);
    EXPECT_EQ(*opt8, V1);
    EXPECT_EQ(*opt9, V5);
}

TEST_F(DirectedGraphTest, inboundEdgesEmpty)
{
    EXPECT_TRUE(empty.inboundEdges(V1).empty());
    EXPECT_TRUE(empty.inboundEdges(V2).empty());
    EXPECT_TRUE(empty.inboundEdges(V3).empty());
    EXPECT_TRUE(empty.inboundEdges(V4).empty());
    EXPECT_TRUE(empty.inboundEdges(V5).empty());
}

TEST_F(DirectedGraphTest, inboundEdges)
{
    const auto res1 = g.inboundEdges(V1);
    const auto res2 = g.inboundEdges(V2);
    const auto res3 = g.inboundEdges(V3);
    const auto res4 = g.inboundEdges(V4);
    const auto res5 = g.inboundEdges(V5);

    const std::vector<Edges> e1{E1, E3, E8}, e2{E2, E7}, e3{E4}, e4{E5},
        e5{E6, E9};

    EXPECT_TRUE(hasIdentifiers(res1, e1));
    EXPECT_TRUE(hasIdentifiers(res2, e2));
    EXPECT_TRUE(hasIdentifiers(res3, e3));
    EXPECT_TRUE(hasIdentifiers(res4, e4));
    EXPECT_TRUE(hasIdentifiers(res5, e5));
}

TEST_F(DirectedGraphTest, outboundEdgesEmpty)
{
    EXPECT_TRUE(empty.outboundEdges(V1).empty());
    EXPECT_TRUE(empty.outboundEdges(V2).empty());
    EXPECT_TRUE(empty.outboundEdges(V3).empty());
    EXPECT_TRUE(empty.outboundEdges(V4).empty());
    EXPECT_TRUE(empty.outboundEdges(V5).empty());
}

TEST_F(DirectedGraphTest, outboundEdges)
{
    const auto res1 = g.outboundEdges(V1);
    const auto res2 = g.outboundEdges(V2);
    const auto res3 = g.outboundEdges(V3);
    const auto res4 = g.outboundEdges(V4);
    const auto res5 = g.outboundEdges(V5);

    const std::vector<Edges> e1{E1, E2}, e2{E3, E4}, e3{E5}, e4{E6},
        e5{E7, E8, E9};

    EXPECT_TRUE(hasIdentifiers(res1, e1));
    EXPECT_TRUE(hasIdentifiers(res2, e2));
    EXPECT_TRUE(hasIdentifiers(res3, e3));
    EXPECT_TRUE(hasIdentifiers(res4, e4));
    EXPECT_TRUE(hasIdentifiers(res5, e5));
}

TEST_F(DirectedGraphTest, findVerticesEmpty)
{
    EXPECT_TRUE(
        empty.findVertices([](const graph_type::vertex_type&) { return true; })
            .empty());
}

TEST_F(DirectedGraphTest, findVertices)
{
    const std::vector<const graph_type::vertex_type*> result{
        g.findVertices([](const graph_type::vertex_type& currentVertex) {
            const graph_type::vertex_identifier vertexIdentifier{
                currentVertex.identifier()};

            return ((static_cast<
                         std::underlying_type_t<graph_type::vertex_identifier>>(
                         vertexIdentifier)
                     + UINT32_C(1))
                    % UINT32_C(2))
                   == UINT32_C(0);
        })};

    const std::vector<Vertices> expected{V2, V4};

    EXPECT_TRUE(hasIdentifiers(result, expected));
}

TEST_F(DirectedGraphTest, findEdgesEmpty)
{
    EXPECT_TRUE(
        empty.findEdges([](const graph_type::edge_type&) { return true; })
            .empty());
}

TEST_F(DirectedGraphTest, findEdges)
{
    const std::vector<const graph_type::edge_type*> result{
        g.findEdges([](const graph_type::edge_type& currentEdge) {
            const graph_type::edge_identifier edgeIdentifier{
                currentEdge.identifier()};

            return ((static_cast<
                         std::underlying_type_t<graph_type::edge_identifier>>(
                         edgeIdentifier)
                     + UINT32_C(1))
                    % UINT32_C(2))
                   == UINT32_C(1);
        })};

    const std::vector<Edges> expected{E1, E3, E5, E7, E9};

    EXPECT_TRUE(hasIdentifiers(result, expected));
}

TEST_F(DirectedGraphTest, inboundDegreeEmpty)
{
    const size_t val1{empty.inboundDegree(V1)};
    const size_t val2{empty.inboundDegree(V2)};
    const size_t val3{empty.inboundDegree(V3)};
    const size_t val4{empty.inboundDegree(V4)};
    const size_t val5{empty.inboundDegree(V5)};

    EXPECT_EQ(val1, static_cast<size_t>(0U));
    EXPECT_EQ(val2, static_cast<size_t>(0U));
    EXPECT_EQ(val3, static_cast<size_t>(0U));
    EXPECT_EQ(val4, static_cast<size_t>(0U));
    EXPECT_EQ(val5, static_cast<size_t>(0U));
}

TEST_F(DirectedGraphTest, inboundDegree)
{
    const size_t val1{g.inboundDegree(V1)};
    const size_t val2{g.inboundDegree(V2)};
    const size_t val3{g.inboundDegree(V3)};
    const size_t val4{g.inboundDegree(V4)};
    const size_t val5{g.inboundDegree(V5)};

    const size_t expected1{3U};
    const size_t expected2{2U};
    const size_t expected3{1U};
    const size_t expected4{1U};
    const size_t expected5{2U};

    EXPECT_EQ(val1, expected1);
    EXPECT_EQ(val2, expected2);
    EXPECT_EQ(val3, expected3);
    EXPECT_EQ(val4, expected4);
    EXPECT_EQ(val5, expected5);
}

TEST_F(DirectedGraphTest, outboundDegreeEmpty)
{
    const size_t val1{empty.outboundDegree(V1)};
    const size_t val2{empty.outboundDegree(V2)};
    const size_t val3{empty.outboundDegree(V3)};
    const size_t val4{empty.outboundDegree(V4)};
    const size_t val5{empty.outboundDegree(V5)};

    EXPECT_EQ(val1, static_cast<size_t>(0U));
    EXPECT_EQ(val2, static_cast<size_t>(0U));
    EXPECT_EQ(val3, static_cast<size_t>(0U));
    EXPECT_EQ(val4, static_cast<size_t>(0U));
    EXPECT_EQ(val5, static_cast<size_t>(0U));
}

TEST_F(DirectedGraphTest, outboundDegree)
{
    const size_t val1{g.outboundDegree(V1)};
    const size_t val2{g.outboundDegree(V2)};
    const size_t val3{g.outboundDegree(V3)};
    const size_t val4{g.outboundDegree(V4)};
    const size_t val5{g.outboundDegree(V5)};

    const size_t expected1{2U};
    const size_t expected2{2U};
    const size_t expected3{1U};
    const size_t expected4{1U};
    const size_t expected5{3U};

    EXPECT_EQ(val1, expected1);
    EXPECT_EQ(val2, expected2);
    EXPECT_EQ(val3, expected3);
    EXPECT_EQ(val4, expected4);
    EXPECT_EQ(val5, expected5);
}

TEST_F(DirectedGraphTest, degreeEmpty)
{
    const size_t val1{empty.degree(V1)};
    const size_t val2{empty.degree(V2)};
    const size_t val3{empty.degree(V3)};
    const size_t val4{empty.degree(V4)};
    const size_t val5{empty.degree(V5)};

    EXPECT_EQ(val1, static_cast<size_t>(0U));
    EXPECT_EQ(val2, static_cast<size_t>(0U));
    EXPECT_EQ(val3, static_cast<size_t>(0U));
    EXPECT_EQ(val4, static_cast<size_t>(0U));
    EXPECT_EQ(val5, static_cast<size_t>(0U));
}

TEST_F(DirectedGraphTest, degree)
{
    const size_t val1{g.degree(V1)};
    const size_t val2{g.degree(V2)};
    const size_t val3{g.degree(V3)};
    const size_t val4{g.degree(V4)};
    const size_t val5{g.degree(V5)};

    const size_t expected1{5U};
    const size_t expected2{4U};
    const size_t expected3{2U};
    const size_t expected4{2U};
    const size_t expected5{5U};

    EXPECT_EQ(val1, expected1);
    EXPECT_EQ(val2, expected2);
    EXPECT_EQ(val3, expected3);
    EXPECT_EQ(val4, expected4);
    EXPECT_EQ(val5, expected5);
}

TEST_F(DirectedGraphTest, maximumDegreeEmpty)
{
    const graph_type::VertexWithDegree expected{nullptr, 0U};

    const graph_type::VertexWithDegree result{empty.maximumDegree()};

    EXPECT_EQ(expected, result);
}

TEST_F(DirectedGraphTest, maximumDegree)
{
    const tl::optional<const graph_type::vertex_type&> vertex{g.vertex(V1)};

    ASSERT_TRUE(vertex.has_value());

    const graph_type::VertexWithDegree expected{&*vertex, 5U};

    const graph_type::VertexWithDegree result{g.maximumDegree()};

    EXPECT_EQ(expected, result);
}

TEST_F(DirectedGraphTest, minimumDegreeEmpty)
{
    const graph_type::VertexWithDegree expected{nullptr, SIZE_MAX};

    const graph_type::VertexWithDegree result{empty.minimumDegree()};

    EXPECT_EQ(expected, result);
}

TEST_F(DirectedGraphTest, minimumDegree)
{
    const tl::optional<const graph_type::vertex_type&> vertex{g.vertex(V3)};

    ASSERT_TRUE(vertex.has_value());

    const graph_type::VertexWithDegree expected{&*vertex, 2U};

    const graph_type::VertexWithDegree result{g.minimumDegree()};

    EXPECT_EQ(expected, result);
}

TEST_F(DirectedGraphTest, addVertexAlreadyExists)
{
    const bool b1{g.addVertex(V1, "")};
    const bool b2{g.addVertex(V2, "")};
    const bool b3{g.addVertex(V3, "")};
    const bool b4{g.addVertex(V4, "")};
    const bool b5{g.addVertex(V5, "")};

    EXPECT_FALSE(b1);
    EXPECT_FALSE(b2);
    EXPECT_FALSE(b3);
    EXPECT_FALSE(b4);
    EXPECT_FALSE(b5);
}

TEST_F(DirectedGraphTest, addVertex)
{
    graph_type graph;
    EXPECT_FALSE(graph.hasVertices());
    EXPECT_FALSE(graph.hasVertex(V1));

    EXPECT_TRUE(graph.addVertex(V1, "V1"));
    EXPECT_TRUE(graph.hasVertices());
    EXPECT_TRUE(graph.hasVertex(V1));
    const tl::optional<const graph_type::vertex_type&> opt{graph.vertex(V1)};
    ASSERT_TRUE(opt.has_value());
    EXPECT_EQ(opt->identifier(), V1);
    EXPECT_EQ(opt->data(), "V1");

    EXPECT_FALSE(graph.addVertex(V1, ""));
}

TEST_F(DirectedGraphTest, addEdgeAlreadyExists)
{
    EXPECT_FALSE(g.addEdge(E1, V1, V1, ""));
    EXPECT_FALSE(g.addEdge(E2, V1, V1, ""));
    EXPECT_FALSE(g.addEdge(E3, V1, V1, ""));
    EXPECT_FALSE(g.addEdge(E4, V1, V1, ""));
    EXPECT_FALSE(g.addEdge(E5, V1, V1, ""));
    EXPECT_FALSE(g.addEdge(E6, V1, V1, ""));
    EXPECT_FALSE(g.addEdge(E7, V1, V1, ""));
    EXPECT_FALSE(g.addEdge(E8, V1, V1, ""));
    EXPECT_FALSE(g.addEdge(E9, V1, V1, ""));
}

TEST_F(DirectedGraphTest, addEdgeSourceVertexDoesntExist)
{
    graph_type graph{};
    ASSERT_TRUE(graph.addVertex(V2, ""));
    EXPECT_FALSE(graph.addEdge(E1, V1, V2, ""));
}

TEST_F(DirectedGraphTest, addEdgeTargetVertexDoesntExist)
{
    graph_type graph{};
    ASSERT_TRUE(graph.addVertex(V1, ""));
    EXPECT_FALSE(graph.addEdge(E1, V1, V2, ""));
}

TEST_F(DirectedGraphTest, addEdgePositiveTest)
{
    graph_type graph{};
    ASSERT_TRUE(graph.addVertex(V1, "V1"));
    ASSERT_TRUE(graph.addVertex(V2, "V2"));
    EXPECT_TRUE(graph.addEdge(E1, V1, V2, "E1"));
    EXPECT_FALSE(graph.addEdge(E1, V1, V2, "E1"));
    EXPECT_TRUE(graph.hasEdge(E1));
    const tl::optional<const graph_type::edge_type&> opt{graph.edge(E1)};
    ASSERT_TRUE(opt.has_value());
    EXPECT_EQ(opt->identifier(), E1);
    EXPECT_EQ(opt->data(), "E1");
}

TEST_F(DirectedGraphTest, removeVertexVertexToRemoveDoesntExist)
{
    graph_type graph{};
    EXPECT_FALSE(graph.removeVertex(V1));
    EXPECT_FALSE(graph.removeVertex(V2));
    EXPECT_FALSE(graph.removeVertex(V3));
    EXPECT_FALSE(graph.removeVertex(V4));
    EXPECT_FALSE(graph.removeVertex(V5));
}

TEST_F(DirectedGraphTest, removeVertexVertexIsRemoved)
{
    EXPECT_TRUE(g.removeVertex(V1));
    EXPECT_FALSE(g.hasVertex(V1));
}

TEST_F(DirectedGraphTest, removeVertexIncidentEdgesAreRemoved)
{
    ASSERT_TRUE(g.removeVertex(V1));

    EXPECT_FALSE(g.hasEdge(E1));
    EXPECT_FALSE(g.hasEdge(E2));
    EXPECT_FALSE(g.hasEdge(E3));
    EXPECT_TRUE(g.hasEdge(E4));
    EXPECT_TRUE(g.hasEdge(E5));
    EXPECT_TRUE(g.hasEdge(E6));
    EXPECT_TRUE(g.hasEdge(E7));
    EXPECT_FALSE(g.hasEdge(E8));
    EXPECT_TRUE(g.hasEdge(E9));
}

TEST_F(DirectedGraphTest, removeVertexNoIncidentEdges)
{
    graph_type graph{};
    ASSERT_TRUE(graph.addVertex(V1, "V1"));
    ASSERT_TRUE(graph.addVertex(V2, "V2"));
    ASSERT_TRUE(graph.addVertex(V3, "V3"));
    ASSERT_TRUE(graph.addEdge(E1, V2, V3, "E1"));

    EXPECT_TRUE(graph.removeVertex(V1));
    EXPECT_TRUE(graph.hasEdge(E1));
}

TEST_F(DirectedGraphTest, removeEdge)
{
    ASSERT_TRUE(g.hasEdge(E1));
    EXPECT_TRUE(g.removeEdge(E1));
    EXPECT_FALSE(g.removeEdge(E1));
    EXPECT_FALSE(g.hasEdge(E1));
}

TEST_F(DirectedGraphTest, clearTest)
{
    g.clear();

    EXPECT_FALSE(g.hasEdges());
    EXPECT_FALSE(g.hasVertices());
}

TEST_F(DirectedGraphTest, swapTest)
{
    graph_type graph{};
    ASSERT_TRUE(graph.addVertex(V2, "V2"));
    ASSERT_TRUE(graph.addVertex(V3, "V3"));
    ASSERT_TRUE(graph.addEdge(E1, V2, V3, "E1"));

    swap(g, graph);

    EXPECT_FALSE(g.hasVertex(V1));
    EXPECT_TRUE(g.hasVertex(V2));
    EXPECT_TRUE(g.hasVertex(V3));
    EXPECT_FALSE(g.hasVertex(V4));
    EXPECT_FALSE(g.hasVertex(V5));

    EXPECT_TRUE(graph.hasVertex(V1));
    EXPECT_TRUE(graph.hasVertex(V2));
    EXPECT_TRUE(graph.hasVertex(V3));
    EXPECT_TRUE(graph.hasVertex(V4));
    EXPECT_TRUE(graph.hasVertex(V5));

    EXPECT_TRUE(g.hasEdge(E1));
    EXPECT_FALSE(g.hasEdge(E2));
    EXPECT_FALSE(g.hasEdge(E3));
    EXPECT_FALSE(g.hasEdge(E4));
    EXPECT_FALSE(g.hasEdge(E5));
    EXPECT_FALSE(g.hasEdge(E6));
    EXPECT_FALSE(g.hasEdge(E7));
    EXPECT_FALSE(g.hasEdge(E8));
    EXPECT_FALSE(g.hasEdge(E9));

    EXPECT_TRUE(graph.hasEdge(E1));
    EXPECT_TRUE(graph.hasEdge(E2));
    EXPECT_TRUE(graph.hasEdge(E3));
    EXPECT_TRUE(graph.hasEdge(E4));
    EXPECT_TRUE(graph.hasEdge(E5));
    EXPECT_TRUE(graph.hasEdge(E6));
    EXPECT_TRUE(graph.hasEdge(E7));
    EXPECT_TRUE(graph.hasEdge(E8));
    EXPECT_TRUE(graph.hasEdge(E9));
}
