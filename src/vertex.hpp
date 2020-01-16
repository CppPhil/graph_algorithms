#ifndef INCG_GP_VERTEX_HPP
#define INCG_GP_VERTEX_HPP
#include <ciso646>            // not
#include <pl/annotations.hpp> // PL_NODISCARD
#include <utility>            // std::move, std::swap

namespace gp {
/*!
 * \brief Represents a vertex in a directed graph.
 * \tparam VertexIdentifier The type of which instances are used to uniquely
 *                          identify vertices.
 * \tparam VertexData The type of the data stored on a vertex.
 **/
template<typename VertexIdentifier, typename VertexData>
class Vertex {
public:
    using this_type       = Vertex;
    using identifier_type = VertexIdentifier;
    using data_type       = VertexData;

    /*!
     * \brief Creates a vertex.
     * \param identifier The unique identifier for this vertex.
     * \param data The data to store on this vertex.
     **/
    Vertex(identifier_type identifier, data_type data)
        : m_identifier{std::move(identifier)}, m_data{std::move(data)}
    {
    }

    /*!
     * \brief Read accessor for the unique identifier of this vertex.
     * \return The unique identifier of this vertex.
     **/
    PL_NODISCARD const identifier_type& identifier() const noexcept
    {
        return m_identifier;
    }

    /*!
     * \brief Read accessor for the data stored on this vertex.
     * \return The data stored on this vertex.
     **/
    PL_NODISCARD const data_type& data() const noexcept { return m_data; }

    /*!
     * \brief Compares two vertices for equality.
     * \param lhs The left hand side operand.
     * \param rhs The right hand side operand.
     * \return true if the two vertices have the same identifier; otherwise
     *         false.
     **/
    friend bool operator==(const this_type& lhs, const this_type& rhs) noexcept
    {
        return lhs.identifier() == rhs.identifier();
    }

    /*!
     * \brief Compares two vertices for inequality.
     * \param lhs The left hand side operand.
     * \param rhs The right hand side operand.
     * \return true if the two vertices don't have the same identifier;
     *         otherwise false.
     **/
    friend bool operator!=(const this_type& lhs, const this_type& rhs) noexcept
    {
        return not(lhs == rhs);
    }

    /*!
     * \brief Swaps this vertex with another vertex.
     * \param other The other vertex to swap with.
     **/
    void swap(this_type& other) noexcept
    {
        using std::swap;

        swap(m_identifier, other.m_identifier);
        swap(m_data, other.m_data);
    }

private:
    identifier_type m_identifier;
    data_type       m_data;
};

/*!
 * \brief Swaps two vertices with each other.
 * \tparam VertexIdentifier The type of which instances are used to uniquely
 *                          identify vertices.
 * \tparam VertexData The type of the data stored on a vertex.
 * \param lhs The first operand.
 * \param rhs The second operand.
 * \note Can be found by argument dependent lookup (ADL).
 **/
template<typename VertexIdentifier, typename VertexData>
void swap(
    Vertex<VertexIdentifier, VertexData>& lhs,
    Vertex<VertexIdentifier, VertexData>& rhs) noexcept
{
    lhs.swap(rhs);
}
} // namespace gp
#endif // INCG_GP_VERTEX_HPP
