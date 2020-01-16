#ifndef INCG_GP_A_START_INSERT_HPP
#define INCG_GP_A_START_INSERT_HPP
#include "path.hpp"                      // gp::a_star::Path
#include <pl/algo/ranged_algorithms.hpp> // pl::algo::lower_bound
#include <pl/invoke.hpp>                 // pl::invoke
#include <vector>                        // std::vector

namespace gp {
namespace a_star {
/*!
 * \brief Insertion routine used by the A* algorithm.
 * \tparam Heuristic The type of the unary heuristic invocable.
 * \tparam VertexIdentifier The type used to identity vertices in the graph.
 * \param heuristic The unary heuristic invocable. Shall return a heuristic
 *                  value of type std::size_t for a given VertexIdentifier.
 * \param openList The open list to instert into.
 * \param pathToInsert The path that shall be inserted into the open list.
 * \warning The open list must be sorted according to the f
 *          values (f = g + h) of the paths it contains in ascending order,
 *          that is the path with the lowest f value comes first, then the
 *          second lowest and so on. If the sorting criterion is not met
 *          then the behaviour of the program is undefined!
 **/
template<typename Heuristic, typename VertexIdentifier>
void insert(
    const Heuristic&                     heuristic,
    std::vector<Path<VertexIdentifier>>& openList,
    const Path<VertexIdentifier>&        pathToInsert)
{
    // Find the first position at which 'pathToInsert' may be inserted
    // without violating the sorting criterion.
    const typename std::vector<Path<VertexIdentifier>>::const_iterator
        insertionPoint{pl::algo::lower_bound(
            openList,
            pathToInsert,
            [&heuristic](const auto& lhs, const auto& rhs) {
                const std::size_t lhsTotalG{lhs.g()};
                const std::size_t lhsH{
                    pl::invoke(heuristic, lhs.back().vertexIdentifier())};

                const std::size_t rhsTotalG{rhs.g()};
                const std::size_t rhsH{
                    pl::invoke(heuristic, rhs.back().vertexIdentifier())};

                return (lhsTotalG + lhsH) < (rhsTotalG + rhsH);
            })};

    openList.insert(insertionPoint, pathToInsert);
}
} // namespace a_star
} // namespace gp
#endif // INCG_GP_A_START_INSERT_HPP
