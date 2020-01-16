#ifndef INCG_GP_NM_HEURISTIC_HPP
#define INCG_GP_NM_HEURISTIC_HPP
#include <cstddef> // std::size_t
#include <string>  // std::string

namespace gp {
namespace nm {
/*!
 * \brief Implements the non-monotonic heuristic.
 * \param vertexIdentifier The vertex to get the heuristic (h) value of.
 * \return The heuristic (h) value of 'vertexIdentifier'.
 **/
std::size_t heuristic(const std::string& vertexIdentifier) noexcept;
} // namespace nm
} // namespace gp
#endif // INCG_GP_NM_HEURISTIC_HPP