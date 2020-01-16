#ifndef INCG_GP_SHORTEST_PATHS_HPP
#define INCG_GP_SHORTEST_PATHS_HPP
#include <ciso646>            // or
#include <pl/annotations.hpp> // PL_NODISCARD
#include <pl/except.hpp>      // PL_THROW_WITH_SOURCE_INFO
#include <stdexcept>          // std::logic_error
#include <tl/optional.hpp>    // tl::optional
#include <unordered_map>      // std::unordered_map
#include <utility>            // std::move
#include <vector>             // std::vector

namespace gp {
/*!
 * \brief Type for the shortest paths objects.
 * \tparam VertexIdentifier The type of the unique identifiers of the
 *                          vertices in the directed graph.
 * \tparam Length The length type to use.
 **/
template<typename VertexIdentifier, typename Length>
class ShortestPaths {
public:
    using this_type       = ShortestPaths;
    using identifier_type = VertexIdentifier;
    using length_type     = Length;
    using prev_map_type
        = std::unordered_map<identifier_type, tl::optional<identifier_type>>;
    using dist_map_type = std::unordered_map<identifier_type, length_type>;

    /*!
     * \brief Creates a ShortestPaths object.
     * \param source The source vertex.
     * \param prev The 'previous' hash map.
     * \param dist The 'distance' hash map.
     **/
    ShortestPaths(
        identifier_type source,
        prev_map_type   prev,
        dist_map_type   dist)
        : m_source{std::move(source)}
        , m_prev{std::move(prev)}
        , m_dist{std::move(dist)}
    {
    }

    /*!
     * \brief Read accessor for the source vertex.
     * \return A const reference to the source vertex.
     **/
    PL_NODISCARD const identifier_type& source() const noexcept
    {
        return m_source;
    }

    /*!
     * \brief Returns the shortest path to the given target vertex.
     * \param target The vertex to use as the target.
     * \return The shortest path from the source to the given target.
     * \throws std::logic_error if the target given isn't in
     *                          the 'previous' hash map.
     **/
    PL_NODISCARD std::vector<identifier_type> shortestPathTo(
        identifier_type target) const
    {
        // A stack to build up the path in
        std::vector<identifier_type> s{};

        tl::optional<identifier_type> u{target};

        const auto it{m_prev.find(*u)};

        if (it == m_prev.end()) {
            PL_THROW_WITH_SOURCE_INFO(
                std::logic_error, "prev did not contain the given target");
        }

        const tl::optional<identifier_type>& previous{it->second};

        // Build the stack.
        if (previous.has_value() or (*u == m_source)) {
            while (u.has_value()) {
                s.insert(s.begin(), *u);

                const auto iter{m_prev.find(*u)};

                if (iter == m_prev.end()) {
                    PL_THROW_WITH_SOURCE_INFO(
                        std::logic_error, "prev did not contain \"u\"");
                }

                u = iter->second;
            }
        }

        return s;
    }

    /*!
     * \brief Returns the distance (cost) to the given target from
     *        the source vertex.
     * \param target The target vertex to use.
     * \return The distance (cost) from source to the given target vertex.
     * \throws std::logic_error if the target was not found.
     **/
    PL_NODISCARD length_type distanceTo(identifier_type target) const
    {
        const auto it{m_dist.find(target)};

        if (it == m_dist.end()) {
            PL_THROW_WITH_SOURCE_INFO(
                std::logic_error, "dist did not contain the given target");
        }

        const length_type distance{it->second};
        return distance;
    }

private:
    identifier_type m_source;
    prev_map_type   m_prev;
    dist_map_type   m_dist;
};
} // namespace gp
#endif // INCG_GP_SHORTEST_PATHS_HPP
