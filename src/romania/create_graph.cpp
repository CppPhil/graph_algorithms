#include "create_graph.hpp"

namespace gp {
namespace romania {
namespace {
void addVertex(
    DirectedGraph<City, std::nullptr_t, int, LengthEdgeData<std::size_t>>&
         graph,
    City city)
{
    (void)graph.addVertex(city, nullptr);
}

void addEdge(
    DirectedGraph<City, std::nullptr_t, int, LengthEdgeData<std::size_t>>&
                graph,
    int         edge,
    int         reverseEdge,
    City        source,
    City        destination,
    std::size_t edgeLength)
{
    // Add it in a forward manner.
    (void)graph.addEdge(
        edge, source, destination, LengthEdgeData<std::size_t>{edgeLength});

    // Add the reverse edge.
    (void)graph.addEdge(
        reverseEdge,
        destination,
        source,
        LengthEdgeData<std::size_t>{edgeLength});
}

void addAllVertices(
    DirectedGraph<City, std::nullptr_t, int, LengthEdgeData<std::size_t>>&
        graph)
{
#define X(city) addVertex(graph, City::city);
    GP_ROMANIA_CITY_X_MACRO
#undef X
}

void addAllEdges(
    DirectedGraph<City, std::nullptr_t, int, LengthEdgeData<std::size_t>>&
        graph)
{
    // graph, ID, reverse ID, source, destination, edgeLength
    addEdge(graph, 1, 2, City::Oradea, City::Zerind, 71);
    addEdge(graph, 3, 4, City::Zerind, City::Arad, 75);
    addEdge(graph, 5, 6, City::Oradea, City::Sibiu, 151);
    addEdge(graph, 7, 8, City::Arad, City::Sibiu, 140);
    addEdge(graph, 9, 10, City::Arad, City::Timisoara, 118);
    addEdge(graph, 11, 12, City::Timisoara, City::Lugoj, 111);
    addEdge(graph, 13, 14, City::Lugoj, City::Mehadia, 70);
    addEdge(graph, 15, 16, City::Mehadia, City::Dobreta, 75);
    addEdge(graph, 17, 18, City::Dobreta, City::Craiova, 120);
    addEdge(graph, 19, 20, City::RimnicuVilcea, City::Craiova, 146);
    addEdge(graph, 21, 22, City::Craiova, City::Pitesti, 138);
    addEdge(graph, 23, 24, City::RimnicuVilcea, City::Sibiu, 80);
    addEdge(graph, 25, 26, City::Sibiu, City::Fagaras, 99);
    addEdge(graph, 27, 28, City::RimnicuVilcea, City::Pitesti, 97);
    addEdge(graph, 29, 30, City::Pitesti, City::Bucharest, 101);
    addEdge(graph, 31, 32, City::Fagaras, City::Bucharest, 211);
    addEdge(graph, 33, 34, City::Bucharest, City::Giurgiu, 90);
    addEdge(graph, 35, 36, City::Bucharest, City::Urziceni, 85);
    addEdge(graph, 37, 38, City::Urziceni, City::Hirsova, 98);
    addEdge(graph, 39, 40, City::Hirsova, City::Eforie, 86);
    addEdge(graph, 41, 42, City::Urziceni, City::Vaslui, 142);
    addEdge(graph, 43, 44, City::Vaslui, City::Iasi, 92);
    addEdge(graph, 45, 46, City::Iasi, City::Neamt, 87);
}

void initializeGraph(
    DirectedGraph<City, std::nullptr_t, int, LengthEdgeData<std::size_t>>&
        graph)
{
    addAllVertices(graph);
    addAllEdges(graph);
}
} // anonymous namespace

DirectedGraph<City, std::nullptr_t, int, LengthEdgeData<std::size_t>>
createGraph()
{
    DirectedGraph<City, std::nullptr_t, int, LengthEdgeData<std::size_t>>
        graph{};
    initializeGraph(graph);
    return graph;
}
} // namespace romania
} // namespace gp