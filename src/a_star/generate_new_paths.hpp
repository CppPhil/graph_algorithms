#ifndef INCG_GP_A_STAR_GENERATE_NEW_PATHS_HPP
#define INCG_GP_A_STAR_GENERATE_NEW_PATHS_HPP
#include "path.hpp" // gp::a_star::Path
#include <vector>   // std::vector

namespace gp {
namespace a_star {
/*!
 * \brief Generates new paths from the result of expanding a vertex.
 * \tparam VertexIdentifier The type used to identify vertices.
 * \param oldPath The old path that shall be used to generate new paths.
 * \param neighbors The neighboring vertices previously acquired through
 *                  vertex expansion.
 * \return A vector of the newly generated Paths.
 **/
template<typename VertexIdentifier>
std::vector<Path<VertexIdentifier>> generateNewPaths(
    const Path<VertexIdentifier>&                            oldPath,
    const std::vector<IdentifierWithCost<VertexIdentifier>>& neighbors)
{
    std::vector<Path<VertexIdentifier>> result{};

    for (const auto& e : neighbors) {
        Path<VertexIdentifier> copy{oldPath};

        copy.append(e);

        result.push_back(copy);
    }

    return result;
}
} // namespace a_star
} // namespace gp
#endif // INCG_GP_A_STAR_GENERATE_NEW_PATHS_HPP
