#ifndef INCG_GP_DIJKSTRA_INSERT_HPP
#define INCG_GP_DIJKSTRA_INSERT_HPP
#include "vertex_with_priority.hpp"      // gp::dijkstra::VertexWithPriority
#include <pl/algo/ranged_algorithms.hpp> // pl::algo::lower_bound
#include <utility>                       // std::move
#include <vector>                        // std::vector

namespace gp {
namespace dijkstra {
/*!
 * \brief Insertion routine used by Dijkstra's algorithm.
 * \tparam VertexIdentifier The type of the unique identifiers
 *                          used in the directed graph for the
 *                          vertices.
 * \param q The queue to insert into.
 * \param toInsert The vertex with priority to insert into the queue.
 * \warning The program is ill-formed if the 'q' given is not sorted
 *          in ascending order of the priority values!
 **/
template<typename VertexIdentifier>
void insert(
    std::vector<VertexWithPriority<VertexIdentifier>>& q,
    VertexWithPriority<VertexIdentifier>               toInsert)
{
    // Assuming the queue is already sorted according to the criterion
    // find the insertion point for 'toInsert'.
    // The insertion point will be the position where 'toInsert'
    // can be inserted without invalidating the sorting.
    // Inserting at that position will 'bump' all the elements
    // to the 'right' of it one place to the 'right' keeping
    // the sorting invariant.
    // The algorithm is called lower_bound as it returns an
    // iterator to the first element whose position could
    // serve as a proper insertion point.
    // In a range [1, 3, 3, 3, 5, 7] (sorted in ascending order (operator<))
    // the iterator would point to the first occurrence of 3 (assuming another
    // 3 was to be inserted.)

    const auto insertionPoint{pl::algo::lower_bound(
        q,
        toInsert,
        [](const VertexWithPriority<VertexIdentifier>& lhs,
           const VertexWithPriority<VertexIdentifier>& rhs) {
            return lhs.priority() < rhs.priority();
        })};

    q.insert(insertionPoint, std::move(toInsert));
}
} // namespace dijkstra
} // namespace gp
#endif // INCG_GP_DIJKSTRA_INSERT_HPP