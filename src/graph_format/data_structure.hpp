#ifndef INCG_GP_GRAPH_FORMAT_DATA_STRUCTURE_HPP
#define INCG_GP_GRAPH_FORMAT_DATA_STRUCTURE_HPP
#include "../total_order.hpp" // GP_TOTAL_ORDER
#include <cstdint>            // std::int32_t
#include <pl/annotations.hpp> // PL_NODISCARD
#include <pl/string_view.hpp> // pl::string_view
#include <string>             // std::string
#include <vector>             // std::vector

namespace gp {
namespace graph_format {
class DataStructure {
public:
    using this_type      = DataStructure;
    using value_type     = std::int32_t;
    using container_type = std::vector<value_type>;

    DataStructure();

    this_type& append(
        value_type sourceVertexIdentifier,
        value_type targetVertexIdentifier,
        value_type edgeLabel);

    PL_NODISCARD const container_type& data() const noexcept;

    PL_NODISCARD const std::string& text() const noexcept;

    this_type& text(pl::string_view text);

    this_type& text(std::string&& text) noexcept;

    PL_NODISCARD bool exportToFile(const std::string& path) const;

    void swap(this_type& other) noexcept;

private:
    container_type m_data;
    std::string    m_text;
};

void swap(DataStructure& lhs, DataStructure& rhs) noexcept;

PL_NODISCARD bool operator==(
    const DataStructure& lhs,
    const DataStructure& rhs) noexcept;

PL_NODISCARD bool operator<(
    const DataStructure& lhs,
    const DataStructure& rhs) noexcept;

GP_TOTAL_ORDER(DataStructure)
} // namespace graph_format
} // namespace gp
#endif // INCG_GP_GRAPH_FORMAT_DATA_STRUCTURE_HPP
