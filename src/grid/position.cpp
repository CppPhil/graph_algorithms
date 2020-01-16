#include "position.hpp"
#include <ostream> // std::ostream
#include <tuple>   // std::tie

namespace gp {
namespace grid {
Position::Position(Column column, Row row) noexcept
    : m_column{column}, m_row{row}
{
}

PL_NODISCARD Column Position::column() const noexcept { return m_column; }

PL_NODISCARD Row Position::row() const noexcept { return m_row; }

std::ostream& operator<<(std::ostream& os, Position pos)
{
    os << "{\"column\": " << pos.column() << ",\"row\": " << pos.row() << '}';
    return os;
}

PL_NODISCARD bool operator<(Position lhs, Position rhs) noexcept
{
    // See: https://en.cppreference.com/w/cpp/utility/tuple/tie
    // These local variables need to be here so that we have lvalues of them.
    // std::tie does not accept rvalues.
    const Column lhsColumn{lhs.column()};
    const Row    lhsRow{lhs.row()};

    const Column rhsColumn{rhs.column()};
    const Row    rhsRow{rhs.row()};

    return std::tie(lhsColumn, lhsRow) < std::tie(rhsColumn, rhsRow);
}

PL_NODISCARD bool operator==(Position lhs, Position rhs) noexcept
{
    const Column lhsColumn{lhs.column()};
    const Row    lhsRow{lhs.row()};

    const Column rhsColumn{rhs.column()};
    const Row    rhsRow{rhs.row()};

    return std::tie(lhsColumn, lhsRow) == std::tie(rhsColumn, rhsRow);
}
} // namespace grid
} // namespace gp
