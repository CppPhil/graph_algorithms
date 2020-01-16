#include "data_structure.hpp"
#include <algorithm>                     // std::remove_if
#include <ciso646>                       // not
#include <cstddef>                       // std::size_t
#include <iterator>                      // std::distance
#include <ostream>                       // std::ostream
#include <pl/algo/ranged_algorithms.hpp> // pl::algo::find, pl::algo::transform
#include <pl/except.hpp>                 // PL_THROW_WITH_SOURCE_INFO
#include <sstream>                       // std::ostringstream
#include <stdexcept>                     // std::out_of_range, std::logic_error

namespace gp {
namespace grid {
DataStructure::DataStructure(Column columnCount, Row rowCount) : m_data{}
{
    if (columnCount.value() == 0) {
        throw std::out_of_range{
            "columnCount was 0 in gp::grid::DataStructure constructor!"};
    }

    if (rowCount.value() == 0) {
        throw std::out_of_range{
            "rowCount was 0 in gp::grid::DataStructure constructor!"};
    }

    m_data = std::vector<std::vector<PositionKind>>(
        columnCount.value(),
        std::vector<PositionKind>(rowCount.value(), PositionKind::Empty));
}

Column DataStructure::columnCount() const { return Column{m_data.size()}; }

Row DataStructure::rowCount() const { return Row{m_data.at(0).size()}; }

PositionKind& DataStructure::at(Position position)
{
    return m_data.at(position.column().value()).at(position.row().value());
}

const PositionKind& DataStructure::at(Position position) const
{
    return const_cast<this_type*>(this)->at(position);
}

DataStructure::graph_type DataStructure::graph() const
{
    graph_type resultGraph{};

    const std::size_t costValue{1};

    int edgeId{1};

    for (std::size_t currentColumnIdx{0};
         currentColumnIdx < columnCount().value();
         ++currentColumnIdx) {
        for (std::size_t currentRowIdx{0}; currentRowIdx < rowCount().value();
             ++currentRowIdx) {
            const Position currentPosition{Column{currentColumnIdx},
                                           Row{currentRowIdx}};

            std::vector<Position> currentNeighbors{neighbors(currentPosition)};

            for (Position currentNeighbor : currentNeighbors) {
                // Put the current position connected to the current neighbor
                // into the graph, if neither of them is a wall.
                if ((at(currentPosition) != PositionKind::Wall)
                    and (at(currentNeighbor) != PositionKind::Wall)) {
                    // Add the current position if it's not already in there.
                    if (not resultGraph.hasVertex(currentPosition)) {
                        if (not resultGraph.addVertex(
                                /* identifier */ currentPosition,
                                /* data */ nullptr)) {
                            PL_THROW_WITH_SOURCE_INFO(
                                std::logic_error,
                                "Couldn't add vertex to graph!");
                        }
                    }

                    // Add the current neighbor if it's not already in there.
                    if (not resultGraph.hasVertex(currentNeighbor)) {
                        if (not resultGraph.addVertex(
                                /* identifier */ currentNeighbor,
                                /* data */ nullptr)) {
                            PL_THROW_WITH_SOURCE_INFO(
                                std::logic_error,
                                "Couldn't add vertex to graph!");
                        }
                    }

                    // Add the connecting edge.
                    if (not resultGraph.addEdge(
                            /* identifier */ edgeId,
                            /* source */ currentPosition,
                            /* target */ currentNeighbor,
                            /* data */
                            LengthEdgeData<std::size_t>{costValue})) {
                        PL_THROW_WITH_SOURCE_INFO(
                            std::logic_error, "Couldn't add edge to graph!");
                    }

                    ++edgeId;

                    // Add the reverse edge.
                    if (not resultGraph.addEdge(
                            /* identifier */ edgeId,
                            /* source */ currentNeighbor,
                            /* target */ currentPosition,
                            /* data */
                            LengthEdgeData<std::size_t>{costValue})) {
                        PL_THROW_WITH_SOURCE_INFO(
                            std::logic_error, "Couldn't add edge to graph!");
                    }

                    ++edgeId;
                }
            }
        }
    }

    return resultGraph;
}

void DataStructure::insertPath(const a_star::Path<Position>& resultPath)
{
    for (const a_star::IdentifierWithCost<Position>& idWithCost : resultPath) {
        PositionKind& currentPositionKind{at(idWithCost.vertexIdentifier())};

        // Only overwrite if the position kind is empty.
        if (currentPositionKind == PositionKind::Empty) {
            at(idWithCost.vertexIdentifier()) = PositionKind::OnPath;
        }
    }
}

bool DataStructure::hasGoal() const { return goal().has_value(); }

tl::optional<Position> DataStructure::goal() const
{
    return find(PositionKind::Goal);
}

bool DataStructure::hasStart() const { return start().has_value(); }

tl::optional<Position> DataStructure::start() const
{
    return find(PositionKind::Start);
}

std::string DataStructure::asString() const
{
    const std::size_t columns{columnCount().value()};
    const std::size_t rows{rowCount().value()};

    std::vector<std::string> columnWiseStrings{};

    std::ostringstream oss{};

    for (std::size_t curColIdx{0}; curColIdx < columns; ++curColIdx) {
        for (std::size_t curRowIdx{0}; curRowIdx < rows; ++curRowIdx) {
            const Column curColumn{curColIdx};
            const Row    curRow{curRowIdx};

            oss << at(Position{curColumn, curRow});
        }

        columnWiseStrings.push_back(oss.str());
        oss.str("");
    }

    // Since a terminal is line oriented we actually have to print the stuff row
    // wise.
    std::string buf{};

    for (std::size_t curRowIdx{0}; curRowIdx < rows; ++curRowIdx) {
        for (std::size_t curColIdx{0}; curColIdx < columns; ++curColIdx) {
            // Grab the string at the current column.
            // The strings actually contain column wise data rather than row
            // wise data.
            const std::string& curString{columnWiseStrings.at(curColIdx)};

            // Append the characters located at the current row of all the
            // strings to the buffer. THis way we make the buffer be row wise.
            buf += curString.at(curRowIdx);
        }

        buf += '\n';
    }

    // Explanation of the glyphs used for the visualization.
    oss << PositionKind::Start << ": start\n"
        << PositionKind::Goal << ": goal\n"
        << PositionKind::Empty << ": empty\n"
        << PositionKind::Wall << ": wall\n"
        << PositionKind::OnPath << ": on path";

    buf += oss.str();

    return buf;
}

std::ostream& operator<<(std::ostream& os, const DataStructure& grid)
{
    return os << grid.asString();
}

std::vector<PositionKind>& DataStructure::getColumn(Column value)
{
    return m_data.at(value.value());
}

const std::vector<PositionKind>& DataStructure::getColumn(Column value) const
{
    return const_cast<this_type*>(this)->getColumn(value);
}

tl::optional<Position> DataStructure::find(PositionKind kind) const
{
    for (std::size_t currentColumnIdx{0};
         currentColumnIdx < columnCount().value();
         ++currentColumnIdx) {
        const std::vector<PositionKind>& currentColumn{
            getColumn(Column{currentColumnIdx})};

        // Try to find it in the current column vector.
        const std::vector<PositionKind>::const_iterator it{
            pl::algo::find(currentColumn, kind)};

        // If it was found -> exit early.
        // We use std::distance from the begin iterator to the iterator
        // at which the position kind was found to convert to an index.
        if (it != currentColumn.end()) {
            return Position{Column{currentColumnIdx},
                            Row{static_cast<std::size_t>(
                                std::distance(currentColumn.begin(), it))}};
        }
    }

    // Not found.
    return tl::nullopt;
}

constexpr std::size_t neighborOffset{1};

tl::optional<Position> DataStructure::topNeighbor(Position pos) const
{
    // There's nothing above row 0.
    if (pos.row().value() == 0) { return tl::nullopt; }

    return tl::make_optional(
        Position{pos.column(), Row{pos.row().value() - neighborOffset}});
}

tl::optional<Position> DataStructure::bottomNeighbor(Position pos) const
{
    const std::size_t maxRow{rowCount().value() - 1};

    // There's nothing below the last row.
    if (pos.row().value() >= maxRow) { return tl::nullopt; }

    return tl::make_optional(
        Position{pos.column(), Row{pos.row().value() + neighborOffset}});
}

tl::optional<Position> DataStructure::leftNeighbor(Position pos) const
{
    // There's nothing to the left of column 0.
    if (pos.column().value() == 0) { return tl::nullopt; }

    return tl::make_optional(
        Position{Column{pos.column().value() - neighborOffset}, pos.row()});
}

tl::optional<Position> DataStructure::rightNeighbor(Position pos) const
{
    const std::size_t maxColumn{columnCount().value() - 1};

    // There's nothing to the right of the last column.
    if (pos.column().value() >= maxColumn) { return tl::nullopt; }

    return tl::make_optional(
        Position{Column{pos.column().value() + neighborOffset}, pos.row()});
}

std::vector<Position> DataStructure::neighbors(Position pos) const
{
    std::vector<tl::optional<Position>> optionalPositions{topNeighbor(pos),
                                                          bottomNeighbor(pos),
                                                          leftNeighbor(pos),
                                                          rightNeighbor(pos)};

    optionalPositions.erase(
        std::remove_if(
            optionalPositions.begin(),
            optionalPositions.end(),
            [](const tl::optional<Position>& opt) {
                return not opt.has_value();
            }),
        optionalPositions.end());

    std::vector<Position> result(
        optionalPositions.size(), Position{Column{0}, Row{0}});

    pl::algo::transform(
        optionalPositions,
        result.begin(),
        [](const tl::optional<Position>& opt) { return *opt; });

    return result;
}
} // namespace grid
} // namespace gp
