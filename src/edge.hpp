#ifndef INCG_GP_EDGE_HPP
#define INCG_GP_EDGE_HPP
#include "vertex.hpp"         // gp::Vertex
#include <ciso646>            // not
#include <pl/annotations.hpp> // PL_NODISCARD
#include <utility>            // std::move, std::swap

namespace gp {
/*!
 * \brief Represents an edge in a directed graph.
 * \tparam EdgeIdentifier The type of which instances are used to uniquely
 *                        identify edges.
 * \tparam EdgeData The type of the data stored on the edge.
 * \tparam VertexIdentifier The type of which instances are used to uniquely
 *                          identify vertices.
 **/
template<typename EdgeIdentifier, typename EdgeData, typename VertexIdentifier>
class Edge {
public:
    using this_type        = Edge;
    using vertex_identifer = VertexIdentifier;
    using identifier_type  = EdgeIdentifier;
    using data_type        = EdgeData;

    /*!
     * \brief Creates an edge.
     * \param identifier The unique identifier of this edge.
     * \param source The source vertex.
     * \param target The target vertex.
     * \param data The data stored on this edge.
     **/
    Edge(
        identifier_type  identifier,
        vertex_identifer source,
        vertex_identifer target,
        data_type        data)
        : m_identifier{std::move(identifier)}
        , m_source{std::move(source)}
        , m_target{std::move(target)}
        , m_data{std::move(data)}
    {
    }

    /*!
     * \brief Read accessor for the unique identifier.
     * \return The unique identifier.
     **/
    PL_NODISCARD const identifier_type& identifier() const noexcept
    {
        return m_identifier;
    }

    /*!
     * \brief Read accessor for the source vertex.
     * \return The source vertex.
     **/
    PL_NODISCARD const vertex_identifer& source() const noexcept
    {
        return m_source;
    }

    /*!
     * \brief Read accessor for the target vertex.
     * \return The target vertex.
     **/
    PL_NODISCARD const vertex_identifer& target() const noexcept
    {
        return m_target;
    }

    /*!
     * \brief Read accessor for the edge data.
     * \return The edge data.
     **/
    PL_NODISCARD const data_type& data() const noexcept { return m_data; }

    /*!
     * \brief Compares two edges for equality.
     * \param lhs The first operand.
     * \param rhs The second operand.
     * \return true if the two edges have the same unique identifier; otherwise
     *         false.
     **/
    friend bool operator==(const this_type& lhs, const this_type& rhs) noexcept
    {
        return lhs.identifier() == rhs.identifier();
    }

    /*!
     * \brief Compares two edges for inequality.
     * \param lhs The first operand.
     * \param rhs The second operand.
     * \return true if the two edges don't have the same unique identifier;
     *         otherwise false.
     **/
    friend bool operator!=(const this_type& lhs, const this_type& rhs) noexcept
    {
        return not(lhs == rhs);
    }

    /*!
     * \brief Swaps this edge with another edge given.
     * \param other The other edge to swap with.
     **/
    void swap(this_type& other) noexcept
    {
        using std::swap;

        swap(m_identifier, other.m_identifier);
        swap(m_source, other.m_source);
        swap(m_target, other.m_target);
        swap(m_data, other.m_data);
    }

private:
    identifier_type  m_identifier;
    vertex_identifer m_source;
    vertex_identifer m_target;
    data_type        m_data;
};

/*!
 * \brief Swaps two edges with each other.
 * \tparam EdgeIdentifier The type of which instances are used to uniquely
 *                        identify edges.
 * \tparam EdgeData The type of the data stored on the edge.
 * \tparam VertexIdentifier The type of which instances are used to uniquely
 *                          identify vertices.
 * \param lhs The left hand side operand.
 * \param rhs The right hand side operand.
 * \note Can be found by argument dependent lookup (ADL).
 **/
template<typename EdgeIdentifier, typename EdgeData, typename VertexIdentifier>
void swap(
    Edge<EdgeIdentifier, EdgeData, VertexIdentifier>& lhs,
    Edge<EdgeIdentifier, EdgeData, VertexIdentifier>& rhs) noexcept
{
    lhs.swap(rhs);
}
} // namespace gp
#endif // INCG_GP_EDGE_HPP
