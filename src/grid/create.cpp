#include "create.hpp"

namespace gp {
namespace grid {
DataStructure create()
{
    DataStructure g{Column{15}, Row{15}};

    const auto w = [&g](std::size_t x, std::size_t y) {
        g.at(Position{Column{x}, Row{y}}) = PositionKind::Wall;
    };

    g.at(Position{Column{0}, Row{12}}) = PositionKind::Start;
    g.at(Position{Column{13}, Row{2}}) = PositionKind::Goal;

    // line from [5, 2] to [12, 2]
    for (std::size_t x = 5; x <= 12; ++x) { w(x, 2); }

    // line from [12, 3] to [12, 12]
    for (std::size_t y = 3; y <= 12; ++y) { w(12, y); }

    // line from [2, 12] to [11, 12]
    for (std::size_t x = 2; x <= 11; ++x) { w(x, 12); }

    return g;
}
} // namespace grid
} // namespace gp
