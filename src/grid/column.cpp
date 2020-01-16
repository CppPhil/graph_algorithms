#include "column.hpp"
#include <ostream> // std::ostream

namespace gp {
namespace grid {
Column::Column(value_type value) noexcept : m_value{value} {}

PL_NODISCARD Column::value_type Column::value() const noexcept
{
    return m_value;
}

std::ostream& operator<<(std::ostream& os, Column column)
{
    os << "{\"value\": " << column.value() << '}';
    return os;
}

PL_NODISCARD bool operator<(Column lhs, Column rhs) noexcept
{
    return lhs.value() < rhs.value();
}

PL_NODISCARD bool operator==(Column lhs, Column rhs) noexcept
{
    return lhs.value() == rhs.value();
}
} // namespace grid
} // namespace gp
