#include "manhattan_distance.hpp"
#include <cmath> // std::abs

namespace gp {
namespace grid {
std::uint64_t manhattanDistance(Position pos1, Position pos2)
{
    const std::int64_t x1{static_cast<std::int64_t>(pos1.column().value())};
    const std::int64_t x2{static_cast<std::int64_t>(pos2.column().value())};

    const std::int64_t y1{static_cast<std::int64_t>(pos1.row().value())};
    const std::int64_t y2{static_cast<std::int64_t>(pos2.row().value())};

    return std::abs(x1 - x2) + std::abs(y1 - y2);
}
} // namespace grid
} // namespace gp