#ifndef INCG_GP_ROMANIA_HEURISTIC_HPP
#define INCG_GP_ROMANIA_HEURISTIC_HPP
#include "city.hpp" // gp::romania::City
#include <cstddef>  // std::size_t

namespace gp {
namespace romania {
/*!
 * \brief Implements a heuristic for the Romania example.
 * \param city The city to get the heuristic (h) value for.
 * \return The heuristic (h) value for 'city'.
 *
 * The heuristic is based on the 'straight line' distance
 * from the given city to the goal city of Bucharest.
 **/
std::size_t heuristic(City city);
} // namespace romania
} // namespace gp
#endif // INCG_GP_ROMANIA_HEURISTIC_HPP
