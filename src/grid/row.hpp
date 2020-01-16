#ifndef INCG_GP_GRID_ROW_HPP
#define INCG_GP_GRID_ROW_HPP
#include <cstddef>            // std::size_t
#include <iosfwd>             // std::ostream
#include <pl/annotations.hpp> // PL_NODISCARD
#include <total_order.hpp>    // GP_TOTAL_ORDER

namespace gp {
namespace grid {
class Row {
public:
    using value_type = std::size_t;

    explicit Row(value_type value) noexcept;

    PL_NODISCARD value_type value() const noexcept;

private:
    value_type m_value;
};

std::ostream& operator<<(std::ostream& os, Row row);

PL_NODISCARD bool operator<(Row lhs, Row rhs) noexcept;

PL_NODISCARD bool operator==(Row lhs, Row rhs) noexcept;

GP_TOTAL_ORDER(Row)
} // namespace grid
} // namespace gp
#endif // INCG_GP_GRID_ROW_HPP