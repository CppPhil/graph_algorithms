#ifndef INCG_GP_LENGTH_EDGE_DATA_HPP
#define INCG_GP_LENGTH_EDGE_DATA_HPP
#include <pl/annotations.hpp> // PL_NODISCARD

namespace gp {
/*!
 * \brief Type that may be used as edge data in a graph.
 * \tparam Length The type used for the length value.
 *
 * Contains the length of the associated edge.
 **/
template<typename Length>
class LengthEdgeData {
public:
    using this_type   = LengthEdgeData;
    using length_type = Length;

    /*!
     * \brief Creates a new object with 'edgeLength'.
     * \param edgeLength The edge length value to use.
     **/
    explicit LengthEdgeData(length_type edgeLength) noexcept
        : m_edgeLength{edgeLength}
    {
    }

    /*!
     * \brief Read accessor for the edge length value.
     * \return The edge length value.
     **/
    PL_NODISCARD length_type edgeLength() const noexcept
    {
        return m_edgeLength;
    }

private:
    length_type m_edgeLength;
};
} // namespace gp
#endif // INCG_GP_LENGTH_EDGE_DATA_HPP
