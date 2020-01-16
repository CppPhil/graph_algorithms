#include "bellman_ford/negative_cycle.hpp"
#include "bellman_ford/negative_edge_graph.hpp"
#include "bellman_ford/positive_cycle.hpp"
#include "config.h"
#include "fleury/algorithm_test_graph.hpp"
#include "fleury/export_graph.hpp"
#include "fleury/is_bridge_test_graph.hpp"
#include "fleury/reachable_test_graph.hpp"
#include "ford_fulkerson/create_graph.hpp"
#include "hierholzer/algorithm_test_graph.hpp"
#include "hierholzer/export_graph.hpp"
#include "nm/create_graph.hpp" // gp::nm::createGraph
#include "nm/identifiers.hpp"
#include <cstdlib>  // EXIT_SUCCESS, EXIT_FAILURE
#include <iostream> // std::cout, std::cerr
#include <sstream>  // std::ostringstream
#include <string>   // std::string

namespace util {
namespace {
bool exportGraph(
    const gp::bellman_ford::PositiveCycle::graph_type& graph,
    const std::string&                                 outputPath)
{
    auto gen = [](const std::string& s) {
        if (s == "a") { return 1; }
        else if (s == "b") {
            return 2;
        }
        else if (s == "c") {
            return 3;
        }
        else if (s == "d") {
            return 4;
        }
        else if (s == "e") {
            return 5;
        }
        else if (s == "f") {
            return 6;
        }

        return INT32_MAX;
    };

    std::ostringstream              oss{};
    gp::graph_format::DataStructure graphFormat{graph.graphFormat(
        [&oss, &gen](const std::string& vertexIdentifier) {
            const std::int32_t returnValue{gen(vertexIdentifier)};
            oss << "vertex: " << vertexIdentifier << " => " << returnValue
                << '\n';
            return returnValue;
        },
        [&oss](const auto& edge) {
            const auto edgeLabel{edge.data().edgeLength()};
            oss << "edge: " << edge.identifier() << " => " << edgeLabel
                << " (label)\n";
            return edgeLabel;
        })};
    graphFormat.text(oss.str());

    if (graphFormat.exportToFile(outputPath)) {
        std::cout << "Successfully exported to \"" << outputPath << "\"\n";
    }
    else {
        std::cerr << "Couldn't export to \"" << outputPath << "\"\n";
        return false;
    }

    return true;
}

bool exportGraph(
    const gp::ford_fulkerson::types::graph_type& graph,
    const std::string&                           outputPath)
{
    std::ostringstream              oss{};
    gp::graph_format::DataStructure graphFormat{graph.graphFormat(
        [&oss](int vertexIdentifier) {
            oss << "vertex: " << vertexIdentifier << " => " << vertexIdentifier
                << '\n';
            return vertexIdentifier;
        },
        [&oss](const auto& edge) {
            const std::int32_t edgeCapacity{edge.data().capacity()};
            oss << "edge: " << edge.identifier() << " => " << edgeCapacity
                << " (label)\n";
            return edgeCapacity;
        })};
    graphFormat.text(oss.str());

    if (graphFormat.exportToFile(outputPath)) {
        std::cout << "Successfully exported to \"" << outputPath << "\"\n";
    }
    else {
        std::cerr << "Couldn't export to \"" << outputPath << "\"\n";
        return false;
    }

    return true;
}
} // anonymous namespace
} // namespace util

int main()
{
    std::cout << "graph_project version " << VERSION_MAJOR << '.'
              << VERSION_MINOR << '.' << VERSION_PATCH << "\nGit revision \""
              << GIT_REVISION << "\"\n";

    if (not util::exportGraph(
            gp::bellman_ford::PositiveCycle::create(),
            "temp/positive_cycle.graph")) {
        return EXIT_FAILURE;
    }

    if (not util::exportGraph(
            gp::bellman_ford::NegativeEdgeGraph::create(),
            "temp/negative_edge.graph")) {
        return EXIT_FAILURE;
    }

    if (not util::exportGraph(
            gp::bellman_ford::NegativeCycle::create(),
            "temp/negative_cycle.graph")) {
        return EXIT_FAILURE;
    }

    if (not util::exportGraph(
            gp::ford_fulkerson::createGraph(), "temp/ford_fulkerson.graph")) {
        return EXIT_FAILURE;
    }

    if (not util::exportGraph(
            gp::ford_fulkerson::createGraph2(), "temp/max_flow.graph")) {
        return EXIT_FAILURE;
    }

    if (not gp::fleury::exportGraph(
            gp::fleury::reachableTestGraph(), "temp/reachable.graph")) {
        return EXIT_FAILURE;
    }

    if (not gp::fleury::exportGraph(
            gp::fleury::isBridgeTestGraph(), "temp/is_bridge.graph")) {
        return EXIT_FAILURE;
    }

    if (not gp::fleury::exportGraph(
            gp::fleury::algorithmTestGraph(), "temp/fleury.graph")) {
        return EXIT_FAILURE;
    }

    if (not gp::hierholzer::exportGraph(
            gp::hierholzer::algorithmTestGraph(),
            {12, 13, 23, 24, 25, 34, 38, 56, 57, 59, 67, 89},
            "temp/hierholzer.graph")) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
