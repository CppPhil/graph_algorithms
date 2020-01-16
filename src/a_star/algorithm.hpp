/*!
 * \file algorithm.hpp
 * \brief Exports the A* algorithm.
 **/
#ifndef INCG_GP_A_STAR_ALGORITHM_HPP
#define INCG_GP_A_STAR_ALGORITHM_HPP
#include "../contains.hpp"        // gp::contains
#include "../directed_graph.hpp"  // gp::DirectedGraph
#include "expand.hpp"             // gp::a_star::expand
#include "generate_new_paths.hpp" // gp::a_star::generateNewPaths
#include "insert.hpp"             // gp::a_star::insert
#include "path.hpp"               // gp::a_star::Path
#include <ciso646>                // not, or
#include <pl/invoke.hpp>          // pl::invoke
#include <vector>                 // std::vector

namespace gp {
namespace a_star {
/*!
 * \brief Implementation of the A* algorithm.
 * \tparam VertexIdentifier The type of the objects used to identify vertices in
 *                          the graph.
 * \tparam VertexData The type of the data that is stored on the
 *                    vertices in the graph.
 * \tparam EdgeIdentifier The type of the objects used to
 *                        identify edges in the graph.
 * \tparam EdgeData The type of the data that is
 *                  stored on the edges in the graph.
 * \tparam IsGoal The type of the unary predicate invoked to determine whether
 *                a given VertexIdentifier identifies the goal vertex.
 * \tparam Heuristic The type of the unary invocable invoked to get
 *                   the heuristic (h) value for a given VertexIdentifier.
 * \param graph The directed graph that shall be operated on.
 * \param startVertices The vertices considered to be the start vertices.
 * \param isGoal Unary predicate to determine whether a given VertexIdentifier
 *               identifies the goal vertex.
 * \param heuristic Unary invocable to get the heuristic (h) value of the given
 *                  VertexIdentifier
 * \param useClosedList Whether a closed list shall be used. (Defaults to true)
 *                      Must be set to false to work with non-monotonic
 *                      heuristics.
 * \param return The shortest Path that was found.
 **/
template<
    typename VertexIdentifier,
    typename VertexData,
    typename EdgeIdentifier,
    typename EdgeData,
    typename IsGoal,
    typename Heuristic>
Path<VertexIdentifier> algorithm(
    const DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData>&
                                  graph,
    std::vector<VertexIdentifier> startVertices,
    IsGoal                        isGoal,
    Heuristic                     heuristic,
    bool                          useClosedList = true)
{
    // Contains vertices already visited
    std::vector<VertexIdentifier> closedList{};

    // The open list. Contains paths of which the last vertex isn't yet
    // expanded. This list must always remain sorted by the f values of the
    // paths (f = g + h) in ascending order.
    std::vector<Path<VertexIdentifier>> openList{};

    for (const VertexIdentifier& vertex : startVertices) {
        insert(
            heuristic,
            openList,
            Path<VertexIdentifier>{
                IdentifierWithCost<VertexIdentifier>{vertex, 0}});
    }

    // As long as we have paths to explace
    while (not openList.empty()) {
        // Grab the lowes f path
        const Path<VertexIdentifier> currentPath{openList.front()};

        // Delete it from the open list
        openList.erase(openList.begin());

        // Only handle the vertex if it's not in the closed list
        if (not contains(closedList, currentPath.back().vertexIdentifier())
            or not useClosedList) {
            const VertexIdentifier lastVertexOfPath{
                currentPath.back().vertexIdentifier()};
            closedList.push_back(lastVertexOfPath);

            // If the goal is reached -> we have the path to the goal
            if (pl::invoke(isGoal, lastVertexOfPath)) { return currentPath; }

            // Get all the neighbors of the vertex with their associated g
            // values
            const std::vector<IdentifierWithCost<VertexIdentifier>> neighbors{
                expand(lastVertexOfPath, graph)};

            // Generate new paths with the neighbors.
            const std::vector<Path<VertexIdentifier>> newPaths{
                generateNewPaths(currentPath, neighbors)};

            for (const Path<VertexIdentifier>& path : newPaths) {
                insert(heuristic, openList, path);
            }
        }
    }

    // If the open list is empty but we still haven't found a solution
    // -> there is no solution
    // -> return the empty path.
    return Path<VertexIdentifier>{};
}
} // namespace a_star
} // namespace gp
#endif // INCG_GP_A_STAR_ALGORITHM_HPP