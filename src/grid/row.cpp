#include "row.hpp"
#include <ostream> // std::ostream

namespace gp {
namespace grid {
Row::Row(value_type value) noexcept : m_value{value} {}

PL_NODISCARD Row::value_type Row::value() const noexcept { return m_value; }

std::ostream& operator<<(std::ostream& os, Row row)
{
    os << "{\"value\": " << row.value() << '}';
    return os;
}

PL_NODISCARD bool operator<(Row lhs, Row rhs) noexcept
{
    return lhs.value() < rhs.value();
}

PL_NODISCARD bool operator==(Row lhs, Row rhs) noexcept
{
    return lhs.value() == rhs.value();
}
} // namespace grid
} // namespace gp
