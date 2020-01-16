#ifndef INCG_GP_GRID_DATA_STRUCTURE_HPP
#define INCG_GP_GRID_DATA_STRUCTURE_HPP
#include "column.hpp"           // gp::grid::Column
#include "position.hpp"         // gp::grid::Position
#include "position_kind.hpp"    // gp::grid::PositionKind
#include "row.hpp"              // gp::grid::Row
#include <a_star/path.hpp>      // gp::a_star::Path
#include <cstddef>              // std::nullptr_t, std::size_t
#include <directed_graph.hpp>   // gp::DirectedGraph
#include <iosfwd>               // std::ostream
#include <length_edge_data.hpp> // gp::LengthEdgeData
#include <string>               // std::string
#include <tl/optional.hpp>      // tl::optional
#include <vector>               // std::vector

namespace gp {
namespace grid {
/*!
 * \brief The type used for the actual grid data structure.
 **/
class DataStructure {
public:
    using this_type  = DataStructure;
    using graph_type = DirectedGraph<
        /* VertexIdentifier */ Position,
        /* VertexData */ std::nullptr_t,
        /* EdgeIdentifier */ int,
        /* EdgeData */ LengthEdgeData<std::size_t>>;

    /*!
     * \brief Creates a grid object.
     * \param columnCount The amount of columns the grid shall have.
     * \param rowCount The amount of rows the grid shall have.
     * \throws std::out_of_range if 'columnCount' or 'rowCount' contain a value
     *                           of 0.
     **/
    DataStructure(Column columnCount, Row rowCount);

    Column columnCount() const;

    Row rowCount() const;

    PositionKind& at(Position position);

    const PositionKind& at(Position position) const;

    graph_type graph() const;

    void insertPath(const a_star::Path<Position>& resultPath);

    bool hasGoal() const;

    tl::optional<Position> goal() const;

    bool hasStart() const;

    tl::optional<Position> start() const;

    std::string asString() const;

    friend std::ostream& operator<<(std::ostream& os, const this_type& grid);

private:
    std::vector<PositionKind>& getColumn(Column value);

    const std::vector<PositionKind>& getColumn(Column value) const;

    tl::optional<Position> find(PositionKind kind) const;

    tl::optional<Position> topNeighbor(Position pos) const;

    tl::optional<Position> bottomNeighbor(Position pos) const;

    tl::optional<Position> leftNeighbor(Position pos) const;

    tl::optional<Position> rightNeighbor(Position pos) const;

    std::vector<Position> neighbors(Position pos) const;

    std::vector<std::vector<PositionKind>> m_data;
};
} // namespace grid
} // namespace gp
#endif // INCG_GP_GRID_DATA_STRUCTURE_HPP
