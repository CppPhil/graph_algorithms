#ifndef INCG_GP_GRID_MANHATTAN_DISTANCE_HPP
#define INCG_GP_GRID_MANHATTAN_DISTANCE_HPP
#include "position.hpp" // gp::grid::Position
#include <cstdint>      // std::uint64_t

namespace gp {
namespace grid {
std::uint64_t manhattanDistance(Position pos1, Position pos2);
} // namespace grid
} // namespace gp
#endif // INCG_GP_GRID_MANHATTAN_DISTANCE_HPP
