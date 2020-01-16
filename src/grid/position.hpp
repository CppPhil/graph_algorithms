#ifndef INCG_GP_GRID_POSITION_HPP
#define INCG_GP_GRID_POSITION_HPP
#include "column.hpp"         // gp::grid::Column
#include "row.hpp"            // gp::grid::Row
#include <iosfwd>             // std::ostream
#include <pl/annotations.hpp> // PL_NODISCARD
#include <total_order.hpp>    // GP_TOTAL_ORDER

namespace gp {
namespace grid {
class Position {
public:
    Position(Column column, Row row) noexcept;

    PL_NODISCARD Column column() const noexcept;

    PL_NODISCARD Row row() const noexcept;

private:
    Column m_column;
    Row    m_row;
};

std::ostream& operator<<(std::ostream& os, Position pos);

PL_NODISCARD bool operator<(Position lhs, Position rhs) noexcept;

PL_NODISCARD bool operator==(Position lhs, Position rhs) noexcept;

GP_TOTAL_ORDER(Position)
} // namspace grid
} // namespace gp
#endif // INCG_GP_GRID_POSITION_HPP
