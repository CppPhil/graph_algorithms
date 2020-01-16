#ifndef INCG_GP_GRID_COLUMN_HPP
#define INCG_GP_GRID_COLUMN_HPP
#include <cstddef>            // std::size_t
#include <iosfwd>             // std::ostream
#include <pl/annotations.hpp> // PL_NODISCARD
#include <total_order.hpp>    // GP_TOTAL_ORDER

namespace gp {
namespace grid {
class Column {
public:
    using value_type = std::size_t;

    explicit Column(value_type value) noexcept;

    PL_NODISCARD value_type value() const noexcept;

private:
    value_type m_value;
};

std::ostream& operator<<(std::ostream& os, Column column);

PL_NODISCARD bool operator<(Column lhs, Column rhs) noexcept;

PL_NODISCARD bool operator==(Column lhs, Column rhs) noexcept;

GP_TOTAL_ORDER(Column)
} // namespace grid
} // namespace gp
#endif // INCG_GP_GRID_COLUMN_HPP
