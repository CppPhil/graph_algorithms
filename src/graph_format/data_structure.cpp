#include "data_structure.hpp"
#include <algorithm> // std::find
#include <ciso646>   // not
#include <fstream>   // std::ofstream
#include <join.hpp>  // gp::join
#include <utility>   // std::move

namespace gp {
namespace graph_format {
DataStructure::DataStructure() : m_data{}, m_text{} {}

DataStructure& DataStructure::append(
    value_type sourceVertexIdentifier,
    value_type targetVertexIdentifier,
    value_type edgeLabel)
{
    m_data.push_back(sourceVertexIdentifier);
    m_data.push_back(targetVertexIdentifier);
    m_data.push_back(edgeLabel);
    return *this;
}

PL_NODISCARD const DataStructure::container_type& DataStructure::data() const
    noexcept
{
    return m_data;
}

PL_NODISCARD const std::string& DataStructure::text() const noexcept
{
    return m_text;
}

DataStructure& DataStructure::text(pl::string_view text)
{
    m_text.assign(text.begin(), text.end());
    return *this;
}

DataStructure& DataStructure::text(std::string&& text) noexcept
{
    m_text = std::move(text);
    return *this;
}

inline bool writeToTextFile(const std::string& path, pl::string_view string)
{
    std::ofstream ofs{path, std::ios_base::out | std::ios_base::trunc};

    if (not ofs) { return false; }

    ofs << string.data();
    return static_cast<bool>(ofs);
}

inline void replaceExtension(std::string& path, const char* ext)
{
    auto it = std::find(path.rbegin(), path.rend(), '.');

    if (it == path.rend()) { return; }

    path.assign(path.begin(), it.base() - 1);
    path += ext;
}

PL_NODISCARD bool DataStructure::exportToFile(const std::string& path) const
{
    std::ofstream ofs{path, std::ios_base::out | std::ios_base::trunc};

    if (not ofs) { return false; }

    ofs << '[' << join(data(), ",") << ']';

    if (not ofs) { return false; }

    const std::string txtPath{[newPath = path]() mutable {
        replaceExtension(newPath, ".txt");
        return newPath;
    }()};

    return writeToTextFile(txtPath, m_text);
}

void DataStructure::swap(this_type& other) noexcept
{
    using std::swap;

    swap(m_data, other.m_data);
    swap(m_text, other.m_text);
}

void swap(DataStructure& lhs, DataStructure& rhs) noexcept { lhs.swap(rhs); }

PL_NODISCARD bool operator==(
    const DataStructure& lhs,
    const DataStructure& rhs) noexcept
{
    return lhs.data() == rhs.data();
}

PL_NODISCARD bool operator<(
    const DataStructure& lhs,
    const DataStructure& rhs) noexcept
{
    return lhs.data() < rhs.data();
}
} // namespace graph_format
} // namespace gp
