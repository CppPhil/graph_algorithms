#ifndef INCG_GP_GRID_POSITION_KIND_HPP
#define INCG_GP_GRID_POSITION_KIND_HPP
#include <iosfwd> // std::ostream

namespace gp {
namespace grid {
enum class PositionKind : int {
    Start  = 1,
    Goal   = 2,
    Empty  = 3,
    Wall   = 4,
    OnPath = 5
};

std::ostream& operator<<(std::ostream& os, PositionKind kind);
} // namspace grid
} // namespace gp
#endif // INCG_GP_GRID_POSITION_KIND_HPP
