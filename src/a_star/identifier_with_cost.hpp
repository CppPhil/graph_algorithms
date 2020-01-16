/*!
 * \file identifier_with_cost.hpp
 * \brief Exports the IdentifierWithCost class template.
 **/
#ifndef INCG_GP_A_STAR_IDENTIFIER_WITH_COST_HPP
#define INCG_GP_A_STAR_IDENTIFIER_WITH_COST_HPP
#include <ostream> // std::ostream
#include <sstream> // std::ostringstream

namespace gp {
namespace a_star {
/*!
 * \brief A vertex identifier along with its associated g value.
 * \tparam VertexIdentifier The type of object that identifies a vertex.
 **/
template<typename VertexIdentifier>
class IdentifierWithCost {
public:
    /*!
     * \brief Creates a new IdentifierWithCost object.
     * \param vertexIdentifier The vertex identifier to use.
     * \param g The g value to use.
     **/
    IdentifierWithCost(VertexIdentifier vertexIdentifier, std::size_t g)
        : m_vertexIdentifier(vertexIdentifier), m_g(g)
    {
    }

    /*!
     * \brief Read accessor for the vertex identifier.
     * \return The vertex identifier.
     **/
    VertexIdentifier vertexIdentifier() const { return m_vertexIdentifier; }

    /*!
     * \brief Read accessor for the g value.
     * \return The g value.
     **/
    std::size_t g() const { return m_g; }

private:
    VertexIdentifier m_vertexIdentifier; /*!< The vertex identifier */
    std::size_t      m_g;                /*!< The g value */
};

namespace detail {
/*!
 * \brief Meta function to only surround string vertex identifiers with quotes.
 **/
template<typename VertexIdentifier>
struct prefix_postfix {
    static constexpr const char* str = "";
};

template<>
struct prefix_postfix<std::string> {
    static constexpr const char* str = "\"";
};
} // namespace detail

/*!
 * \brief Writes an IdentifierWithCost to an ostream.
 * \param os The ostream to write to.
 * \param idWithCost The IdentifierWithCost to print.
 * \tparam VertexIdentifier type used to identify a vertex.
 * \return A reference to os.
 **/
template<typename VertexIdentifier>
std::ostream& operator<<(
    std::ostream&                        os,
    IdentifierWithCost<VertexIdentifier> idWithCost)
{
    os << "{\"vertexIdentifier\": "
       << ::gp::a_star::detail::prefix_postfix<VertexIdentifier>::str
       << idWithCost.vertexIdentifier()
       << ::gp::a_star::detail::prefix_postfix<VertexIdentifier>::str << ", "
       << "\"g\": " << idWithCost.g() << '}';

    return os;
}
} // namespace a_star
} // namespace gp
#endif // INCG_GP_A_STAR_IDENTIFIER_WITH_COST_HPP
