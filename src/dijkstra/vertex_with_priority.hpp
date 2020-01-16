#ifndef INCG_GP_DIJKSTRA_VERTEX_WITH_PRIORITY_HPP
#define INCG_GP_DIJKSTRA_VERTEX_WITH_PRIORITY_HPP
#include <cstddef>            // std::size_t
#include <pl/annotations.hpp> // PL_NODISCARD
#include <utility>            // std::move

namespace gp {
namespace dijkstra {
/*!
 * \brief Used by Dijkstra's algorithm.
 * \tparam VertexIdentifier The type of the unique identifiers used
 *                          for vertices in the directed graph.
 **/
template<typename VertexIdentifier>
class VertexWithPriority {
public:
    using this_type       = VertexWithPriority;
    using identifier_type = VertexIdentifier;

    /*!
     * \brief Creates a VertexWithPriority.
     * \param vertex The vertex to use.
     * \param priority The priority to associate the given vertex with.
     **/
    VertexWithPriority(identifier_type vertex, std::size_t priority)
        : m_vertex{std::move(vertex)}, m_priority{priority}
    {
    }

    /*!
     * \brief Read accessor for the vertex.
     * \return A const reference to the vertex.
     **/
    PL_NODISCARD const identifier_type& vertex() const noexcept
    {
        return m_vertex;
    }

    /*!
     * \brief Read accessor for the priority value.
     * \return A copy of the priority value.
     **/
    PL_NODISCARD std::size_t priority() const noexcept { return m_priority; }

private:
    identifier_type m_vertex;
    std::size_t     m_priority;
};
} // namespace dijkstra
} // namespace gp
#endif // INCG_GP_DIJKSTRA_VERTEX_WITH_PRIORITY_HPP