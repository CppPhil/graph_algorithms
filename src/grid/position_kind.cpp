#include "position_kind.hpp"
#include <ostream> // std::ostream

namespace gp {
namespace grid {
std::ostream& operator<<(std::ostream& os, PositionKind kind)
{
    switch (kind) {
    case PositionKind::Start: os << 'S'; break;
    case PositionKind::Goal: os << 'G'; break;
    case PositionKind::Empty: os << 'E'; break;
    case PositionKind::Wall: os << 'W'; break;
    case PositionKind::OnPath: os << 'P'; break;
    }

    return os;
}
} // namespace grid
} // namespace gp
