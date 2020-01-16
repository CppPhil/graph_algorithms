#include "heuristic.hpp"
#include "identifiers.hpp" // gp::nm::start, gp::nm::b, gp::nm::c, gp::nm::d, gp::nm::e, gp::nm::goal
#include <cstdint> // SIZE_MAX

namespace gp {
namespace nm {
std::size_t heuristic(const std::string& vertexIdentifier) noexcept
{
    if (vertexIdentifier == start) { return 9; }
    else if (vertexIdentifier == b) {
        return 7;
    }
    else if (vertexIdentifier == c) {
        return 8;
    }
    else if (vertexIdentifier == d) {
        return 1;
    }
    else if (vertexIdentifier == e) {
        return 1;
    }
    else if (vertexIdentifier == goal) {
        return 0;
    }

    return SIZE_MAX;
}
} // namespace nm
} // namespace gp