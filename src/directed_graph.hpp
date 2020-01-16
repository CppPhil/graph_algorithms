#ifndef INCG_GP_DIRECTED_GRAPH_HPP
#define INCG_GP_DIRECTED_GRAPH_HPP
#include "append.hpp"                      // gp::append
#include "contains.hpp"                    // gp::contains
#include "edge.hpp"                        // gp::Edge
#include "graph_format/data_structure.hpp" // gp::graph_format::DataStructure
#include "vertex.hpp"                      // gp::Vertex
#include <ciso646>                         // not, or, and
#include <cstddef>                         // std::size_t
#include <pl/algo/ranged_algorithms.hpp> // pl::algo::unique, pl::algo::sort, pl::algo::accumulate
#include <pl/annotations.hpp> // PL_NODISCARD
#include <pl/assert.hpp>      // PL_ASSERT
#include <pl/invoke.hpp>      // pl::invoke
#include <pl/size_t.hpp>      // pl::literals::integer_literals::operator""_zu
#include <tl/optional.hpp>    // tl::optional
#include <utility>            // std::swap
#include <vector>             // std::vector

namespace gp {
/*!
 * \brief Represents a directed graph.
 * \tparam VertexIdentifier The type of which instances are used to uniquely
 *                          identify vertices.
 * \tparam VertexData The type of the data stored on a vertex.
 * \tparam EdgeIdentifier The type of which instances are used to uniquely
 *                        identify edges.
 * \tparam EdgeData The type of the data stored on an edge.
 **/
template<
    typename VertexIdentifier,
    typename VertexData,
    typename EdgeIdentifier,
    typename EdgeData>
class DirectedGraph {
public:
    using this_type         = DirectedGraph;
    using vertex_identifier = VertexIdentifier;
    using vertex_data       = VertexData;
    using edge_identifier   = EdgeIdentifier;
    using edge_data         = EdgeData;

    /*!
     * \brief The type of the vertices stored in this directed graph.
     **/
    using vertex_type = Vertex<vertex_identifier, vertex_data>;

    /*!
     * \brief The type of the edges stored in this directed graph.
     **/
    using edge_type = Edge<edge_identifier, edge_data, vertex_identifier>;

    /*!
     * \brief Unsigned integer type guaranteed to be large enough to
     *        be able to represent any 'size'.
     **/
    using size_type = std::size_t;

    /*!
     * \brief A struct holding a pointer to a vertex along with its
     *        associated degree.
     * \warning The pointer may be nullptr.
     **/
    struct VertexWithDegree {
        const vertex_type* vertex; /*!< Pointer to the vertex, may be nullptr */
        size_type          degree; /*!< The degree. */

        /*!
         * \brief Compares two VertexWithDegree structs for equality.
         * \param lhs The left hand side operand.
         * \param rhs The right hand side operand.
         * \return true if the two operands are deemed equal; otherwise false.
         **/
        friend bool operator==(
            VertexWithDegree lhs,
            VertexWithDegree rhs) noexcept
        {
            return (lhs.vertex == rhs.vertex) and (lhs.degree == rhs.degree);
        }

        /*!
         * \brief Compares two VertexWithDegree structs for inequality.
         * \param lhs The left hand side operand.
         * \param rhs The right hand side operand.
         * \return true if the two operands are deemed not equal; otherwise
         *         false.
         **/
        friend bool operator!=(
            VertexWithDegree lhs,
            VertexWithDegree rhs) noexcept
        {
            return not(lhs == rhs);
        }
    };

    /*!
     * \brief Creates an empty directed graph.
     **/
    DirectedGraph() : m_vertices{}, m_edges{} {}

    /*!
     * \brief Fetches a vertex identified by the given identifier.
     * \param identifier The unique identifier of the vertex.
     * \return An optional containing a reference to the vertex
     *         if there is a vertex with the identifier given.
     *         Otherwise a nullopt.
     **/
    PL_NODISCARD tl::optional<const vertex_type&> vertex(
        vertex_identifier identifier) const noexcept
    {
        return fetchElement(m_vertices, identifier);
    }

    /*!
     * \brief Fetches an edge identified by the given identifier.
     * \param identifier The unique identifier of the edge.
     * \return An optional containing a reference to the edge
     *         if there is an edge with the identifier given.
     *         Otherwise a nullopt.
     **/
    PL_NODISCARD tl::optional<const edge_type&> edge(
        edge_identifier identifier) const noexcept
    {
        return fetchElement(m_edges, identifier);
    }

    /*!
     * \brief Queries the amount of vertices in this directed graph.
     * \return The amount of vertices in this directed graph.
     **/
    PL_NODISCARD size_type vertexCount() const noexcept
    {
        return m_vertices.size();
    }

    /*!
     * \brief Queries the amount of edges in this directed graph.
     * \return The amount of edges in this directed graph.
     **/
    PL_NODISCARD size_type edgeCount() const noexcept { return m_edges.size(); }

    /*!
     * \brief Checks whether this directed graph has any vertices.
     * \return true if this directed graph has any vertices; otherwise false.
     **/
    PL_NODISCARD bool hasVertices() const noexcept
    {
        return not m_vertices.empty();
    }

    /*!
     * \brief Checks whether this directed graph has any edges.
     * \return true if this directed graph has any edges; otherwise false.
     **/
    PL_NODISCARD bool hasEdges() const noexcept { return not m_edges.empty(); }

    /*!
     * \brief Checks whether this directed graph contains a vertex with the
     *        identifier given.
     * \return true if this directed graph contains a vertex with the
     *         identifier given; otherwise false.
     **/
    PL_NODISCARD bool hasVertex(vertex_identifier identifier) const noexcept
    {
        return findVertexByIdentifier(identifier) != vertices().end();
    }

    /*!
     * \brief Checks whether this directed graph contains an edge with the
     *        identifier given.
     * \return true if this directed graph contains an edge with the
     *         identifier given; otherwise false.
     **/
    PL_NODISCARD bool hasEdge(edge_identifier identifier) const noexcept
    {
        return findEdgeByIdentifier(identifier) != edges().end();
    }

    /*!
     * \brief Read accessor for the vertices.
     * \return The vertices.
     **/
    PL_NODISCARD const std::vector<vertex_type>& vertices() const noexcept
    {
        return m_vertices;
    }

    /*!
     * \brief Read accessor for the edges.
     * \return The edges.
     **/
    PL_NODISCARD const std::vector<edge_type>& edges() const noexcept
    {
        return m_edges;
    }

    /*!
     * \brief Fetches the vertices adjacent to a given vertex.
     * \param vertex The vertex to get the adjacent vertices of.
     * \return A vector containing pointers to the vertices adjancent to vertex.
     **/
    PL_NODISCARD std::vector<const vertex_type*> adjacentVertices(
        vertex_identifier vertex) const
    {
        // If we don't have the vertex given -> return an empty vector.
        if (not hasVertex(vertex)) { return {}; }

        // Fetch the pointers to the inbound and outbound edges of the vertex
        // given.
        const std::vector<const edge_type*> inbound{inboundEdges(vertex)};
        const std::vector<const edge_type*> outbound{outboundEdges(vertex)};

        // Accumulator for the return value.
        std::vector<const vertex_type*> result{};

        // Lambda that adds all of the vertices returned by a given member
        // function of the edge type for a given vector of edges.
        const auto addVerticesOf
            = [this, &result](
                  const std::vector<const edge_type*>& vector,
                  const vertex_identifier& (edge_type::*memberFunction)()
                      const noexcept) {
                  for (const edge_type* edge : vector) {
                      const vertex_identifier& identifier{
                          (edge->*memberFunction)()};
                      const tl::optional<const vertex_type&> theVertex{
                          this->vertex(identifier)};

                      // No duplicates!
                      if (not contains(result, &*theVertex)) {
                          result.push_back(&*theVertex);
                      }
                  }
              };

        // Add all of the source vertices of the inbound edges.
        addVerticesOf(inbound, &edge_type::source);

        // Add all of the target vertices of the outbound edges.
        addVerticesOf(outbound, &edge_type::target);

        return result;
    }

    /*!
     * \brief Fetches all of the edges incident to the vertex given.
     * \param vertex The vertex.
     * \return A vector of pointers to the edges incident to the vertex given.
     **/
    PL_NODISCARD std::vector<const edge_type*> incidentEdges(
        vertex_identifier vertex) const
    {
        // If we don't have the vertex -> return an empty vector.
        if (not hasVertex(vertex)) { return {}; }

        // Get both the inbound and outbound edges.
        std::vector<const edge_type*> result{
            append(inboundEdges(vertex), outboundEdges(vertex))};

        // Sort the result so that it can be uniquified.
        // If it's not sorted invoking unique results in undefined behavior.
        pl::algo::sort(result);

        // Actually uniquify it.
        result.erase(pl::algo::unique(result), result.end());

        return result;
    }

    /*!
     * \brief Fetches the incident vertices of a given edge.
     * \param edgeToGetTheIncidentVerticesOf The edge.
     * \return A vector containing pointers to the vertices incident to the edge
     *         given.
     **/
    PL_NODISCARD std::vector<const vertex_type*> incidentVertices(
        edge_identifier edgeToGetTheIncidentVerticesOf) const
    {
        const tl::optional<const edge_type&> theEdge{
            edge(edgeToGetTheIncidentVerticesOf)};

        // If the edge doesn't exist -> return an empty vector.
        if (not theEdge.has_value()) { return {}; }

        // Get all the vertices which the edge starts with
        // or the edge ends with.
        return findVertices([theEdge, this](const vertex_type& currentVertex) {
            return (theEdge->source() == currentVertex.identifier())
                   or (theEdge->target() == currentVertex.identifier());
        });
    }

    /*!
     * \brief Fetches the source vertex of a given edge.
     * \param edge The edge.
     * \return The source vertex of the edge if the edge exists in the
     *         directed graph; otherwise a nullopt.
     **/
    PL_NODISCARD tl::optional<vertex_identifier> source(
        edge_identifier edge) const noexcept
    {
        return mapWith(
            this->edge(edge), [](const edge_type& e) { return e.source(); });
    }

    /*!
     * \brief Fetches the target vertex of a given edge.
     * \param edge The edge.
     * \return The target vertex of the edge if the edge exists in the
     *         directed graph; otherwise a nullopt.
     **/
    PL_NODISCARD tl::optional<vertex_identifier> target(
        edge_identifier edge) const noexcept
    {
        return mapWith(
            this->edge(edge), [](const edge_type& e) { return e.target(); });
    }

    /*!
     * \brief Fetches the inbound edges of a vertex.
     * \param vertex The vertex.
     * \return A vector of pointers to the inbound edges of vertex.
     **/
    PL_NODISCARD std::vector<const edge_type*> inboundEdges(
        vertex_identifier vertex) const
    {
        return findEdges([vertex](const edge_type& currentEdge) {
            return currentEdge.target() == vertex;
        });
    }

    /*!
     * \brief Fetches the outbound edges of a vertex.
     * \param vertex The vertex.
     * \return A vector of pointers to the outbound edges of vertex.
     **/
    PL_NODISCARD std::vector<const edge_type*> outboundEdges(
        vertex_identifier vertex) const
    {
        return findEdges([vertex](const edge_type& currentEdge) {
            return currentEdge.source() == vertex;
        });
    }

    /*!
     * \brief Finds vertices that satisfy a given predicate.
     * \tparam UnaryPredicate The type of the predicate.
     * \param unaryPredicate The predicate to use. Must accept a single argument
     *                       as a const vertex_type&.
     * \return A vector of pointers to the vertices that satisfy the predicate.
     **/
    template<typename UnaryPredicate>
    PL_NODISCARD std::vector<const vertex_type*> findVertices(
        UnaryPredicate unaryPredicate) const
    {
        return findByUnaryPredicate(vertices(), std::move(unaryPredicate));
    }

    /*!
     * \brief Finds edges that satisfy a given predicate.
     * \tparam UnaryPredicate The type of the predicate.
     * \param unaryPredicate The predicate to use. Must accept a single argument
     *                       as a const edge_type&.
     * \return A vector of pointers to the edges that satisfy the predicate.
     **/
    template<typename UnaryPredicate>
    PL_NODISCARD std::vector<const edge_type*> findEdges(
        UnaryPredicate unaryPredicate) const
    {
        return findByUnaryPredicate(edges(), std::move(unaryPredicate));
    }

    /*!
     * \brief Returns the inbound degree of a given vertex.
     * \param vertex The vertex.
     * \return The inbound degree of vertex.
     **/
    PL_NODISCARD size_type inboundDegree(vertex_identifier vertex) const
    {
        return inboundEdges(vertex).size();
    }

    /*!
     * \brief Returns the outbound degree of a given vertex.
     * \param vertex The vertex.
     * \return The outbound degree of vertex.
     **/
    PL_NODISCARD size_type outboundDegree(vertex_identifier vertex) const
    {
        return outboundEdges(vertex).size();
    }

    /*!
     * \brief Returns the degree of a given vertex.
     * \param vertex The vertex.
     * \return The degree of vertex.
     **/
    PL_NODISCARD size_type degree(vertex_identifier vertex) const
    {
        return inboundDegree(vertex) + outboundDegree(vertex);
    }

    /*!
     * \brief Determines the vertex with the maximum degree.
     * \return The vertex with the maximum degree along with its degree.
     * \warning The pointer in the struct returned may be nullptr!
     **/
    PL_NODISCARD VertexWithDegree maximumDegree() const
    {
        using namespace pl::literals::integer_literals;

        return degreeByComparator<0_zu>(std::greater{});
    }

    /*!
     * \brief Determines the vertex with the minimum degree.
     * \return The vertex with the minimum degree along with its degree.
     * \warning The pointer in the struct returned may be nullptr!
     **/
    PL_NODISCARD VertexWithDegree minimumDegree() const
    {
        return degreeByComparator<SIZE_MAX>(std::less{});
    }

    /*!
     * \brief Adds a vertex to the directed graph.
     * \param identifier The unique identifier for the vertex.
     * \param data The data to store on the vertex.
     * \return true if adding the vertex succeeded; otherwise false.
     **/
    PL_NODISCARD bool addVertex(vertex_identifier identifier, vertex_data data)
    {
        // You can't add the same vertex more than once.
        if (hasVertex(identifier)) { return false; }

        m_vertices.emplace_back(std::move(identifier), std::move(data));
        return true;
    }

    /*!
     * \brief Adds an edge to the graph.
     * \param identifier The unique identifier to use for the edge.
     * \param source The source vertex.
     * \param target The target vertex.
     * \param data The data to store on the edge.
     * \return true if adding the edge succeeded; otherwise false.
     */
    PL_NODISCARD bool addEdge(
        edge_identifier   identifier,
        vertex_identifier source,
        vertex_identifier target,
        edge_data         data)
    {
        // If the edge is already there       -> Error.
        // If the source vertex doesn't exist -> Error.
        // If the target vertex doesn't exist -> Error.
        if (hasEdge(identifier) or not hasVertex(source)
            or not hasVertex(target)) {
            return false;
        }

        m_edges.emplace_back(
            std::move(identifier),
            std::move(source),
            std::move(target),
            std::move(data));

        return true;
    }

    /*!
     * \brief Removes the vertex given from the graph.
     * \param vertex The vertex to remove.
     * \return true if the vertex was successfully removed; otherwise false.
     * \note Also removes the incident edges of the vertex.
     **/
    PL_NODISCARD bool removeVertex(vertex_identifier vertex)
    {
        const typename std::vector<vertex_type>::const_iterator
            vertexToRemoveIterator{findVertexByIdentifier(vertex)};

        // If the vertex doesn't exist -> error.
        if (vertexToRemoveIterator == vertices().end()) { return false; }

        // Get the incident edges.
        const std::vector<const edge_type*> incidents{incidentEdges(vertex)};

        // Allocate memory for the identifiers of the incident edges.
        std::vector<edge_identifier> identifiers(incidents.size());

        // 'Map' the edge identifiers of the incident edges into the vector.
        pl::algo::transform(
            incidents, identifiers.begin(), [](const edge_type* const curEdge) {
                return curEdge->identifier();
            });

        for (const edge_identifier& currentEdgeIdentifier : identifiers) {
            // Remove the curent edge from the graph.
            if (not removeEdge(currentEdgeIdentifier)) {
                // This should never fail, because it can only fail if the edge
                // to remove doesn't exist in the graph at all.
                PL_ASSERT(false);
                return false;
            }
        }
        // We're done erasing the incident edges now.

        // Remove the vertex.
        m_vertices.erase(vertexToRemoveIterator);

        return true;
    }

    /*!
     * \brief Removes a given edge from the graph.
     * \param edge The edge to remove.
     * \return true if the edge was successfully removed; otherwise false.
     **/
    PL_NODISCARD bool removeEdge(edge_identifier edge)
    {
        const typename std::vector<edge_type>::const_iterator it{
            findEdgeByIdentifier(edge)};

        // If the edge doesn't exist -> Error.
        if (it == edges().end()) { return false; }

        // Remove the edge.
        m_edges.erase(it);

        return true;
    }

    /*!
     * \brief Clears this directed graph so that it is empty,
     *        that is it contains no edges and no vertices.
     * \return A reference to this object.
     **/
    this_type& clear()
    {
        m_edges.clear();
        m_vertices.clear();

        return *this;
    }

    /*!
     * \brief Swaps this directed graph with another one.
     * \param other The other directed graph to swap with.
     **/
    void swap(this_type& other) noexcept
    {
        using std::swap;

        swap(m_vertices, other.m_vertices);
        swap(m_edges, other.m_edges);
    }

    template<typename VertexIdentifierMapper, typename LabelExtractor>
    graph_format::DataStructure graphFormat(
        VertexIdentifierMapper&& vertexIdentifierMapper,
        LabelExtractor&&         labelExtractor) const
    {
        graph_format::DataStructure result{};

        for (const edge_type& edge : edges()) {
            result.append(
                pl::invoke(vertexIdentifierMapper, edge.source()),
                pl::invoke(vertexIdentifierMapper, edge.target()),
                pl::invoke(labelExtractor, edge));
        }

        return result;
    }

private:
    /*!
     * \brief Maps an optional with a given unary invocable.
     * \tparam Ty The type of the element possibly stored in the optional.
     * \tparam UnaryInvocable The type of the unary invocable to map with.
     * \param optional The optional to map.
     * \param unaryInvocable The unary invocable to map with.
     * \return An optional containing the result of invoking unaryInvocable
     *         with the element of the optional given if the optional contains
     *         a value; otherwise a nullopt.
     **/
    template<typename Ty, typename UnaryInvocable>
    PL_NODISCARD static auto mapWith(
        const tl::optional<Ty>& optional,
        UnaryInvocable&&        unaryInvocable) noexcept
    {
        return optional.map(
            [invocable = std::forward<UnaryInvocable>(unaryInvocable)](
                const Ty& element) { return pl::invoke(invocable, element); });
    }

    /*!
     * \brief Finds an element of a vector by a given identifier.
     * \tparam ElementType The type of the elements in the vector.
     * \param haystack The vector to search in.
     * \param needle The identifier to search with.
     * \return An iterator to the element in the vector with the
     *         identifier needle or the vector's end iterator
     *         if there's no such element.
     **/
    template<typename ElementType>
    PL_NODISCARD static typename std::vector<ElementType>::const_iterator
    findElementByIdentifier(
        const std::vector<ElementType>&       haystack,
        typename ElementType::identifier_type needle) noexcept
    {
        return pl::algo::find_if(
            haystack, [&needle](const ElementType& element) {
                return element.identifier() == needle;
            });
    }

    /*!
     * \brief Fetches an element from a vector.
     * \tparam ElementType The type of the elements in the vector.
     * \param container The vector to fetch an element from.
     * \param identifier The identifier of the element to fetch.
     * \return An optional containing a reference to the element
     *         if the vector given contains an element with the
     *         identifier given; otherwise a nullopt.
     **/
    template<typename ElementType>
    PL_NODISCARD static tl::optional<const ElementType&> fetchElement(
        const std::vector<ElementType>&       container,
        typename ElementType::identifier_type identifier) noexcept
    {
        const typename std::vector<ElementType>::const_iterator it{
            findElementByIdentifier(container, identifier)};

        // If the element couldn't be found -> return a nullopt.
        if (it == container.end()) { return tl::nullopt; }

        return tl::optional<const ElementType&>(*it);
    }

    /*!
     * \brief Find elements that satisfy a given unary predicate.
     * \tparam ElementType The type of the elements in the vector to search in.
     * \tparam UnaryPredicate The type of the unary predicate.
     * \param haystack The vector to search in.
     * \param unaryPredicate The unary predicate to use.
     * \return A vector containing pointers to the elements that satisfy
     *         the predicate.
     **/
    template<typename ElementType, typename UnaryPredicate>
    PL_NODISCARD static std::vector<const ElementType*> findByUnaryPredicate(
        const std::vector<ElementType>& haystack,
        UnaryPredicate                  unaryPredicate)
    {
        // There's no such thing as transform_if in the standard library.

        std::vector<const ElementType*> result{};

        // Add all the elements which satisfy the predicate.
        for (const ElementType& element : haystack) {
            if (pl::invoke(unaryPredicate, element)) {
                // No duplicates!
                if (not contains(result, &element)) {
                    result.push_back(&element);
                }
            }
        }

        return result;
    }

    /*!
     * \brief Returns an iterator to the vertex with the identifier given.
     * \param vertexToFind The identifier.
     * \return The iterator to the vertex with the given identifier or
     *         the vertices vector's end iterator if no such vertex exists.
     **/
    PL_NODISCARD typename std::vector<vertex_type>::const_iterator
    findVertexByIdentifier(vertex_identifier vertexToFind) const noexcept
    {
        return findElementByIdentifier(m_vertices, vertexToFind);
    }

    /*!
     * \brief Returns an iterator to the edge with the identifier given.
     * \param edgeToFind The identifier.
     * \return The iterator to the edge with the given identifier or
     *         the edges vector's end iterator if no such edge exists.
     **/
    PL_NODISCARD typename std::vector<edge_type>::const_iterator
    findEdgeByIdentifier(edge_identifier edgeToFind) const noexcept
    {
        return findElementByIdentifier(m_edges, edgeToFind);
    }

    /*!
     * \brief Finds the vertex with the 'maximum' degree according to
     *        a given comparator.
     * \tparam InitialDegree The initial degree value to use for the
     *                       accumulator.
     * \tparam BinaryComparator The type of the binary comparator.
     * \param binaryComparator The binary comparator.
     * \return The resulting VertexWithDegree struct.
     * \warning The pointer in the struct returned may be nullptr!
     **/
    template<std::size_t InitialDegree, typename BinaryComparator>
    PL_NODISCARD VertexWithDegree
    degreeByComparator(BinaryComparator binaryComparator) const
    {
        return pl::algo::accumulate(
            m_vertices,
            VertexWithDegree{nullptr, InitialDegree},
            [this, &binaryComparator](
                VertexWithDegree accumulator, const vertex_type& rhs) {
                const size_type rhsDegree{degree(rhs.identifier())};

                // If rhs is 'greater' according to the comparator -> update the
                // accumulator to be rhs.
                if (pl::invoke(
                        binaryComparator, rhsDegree, accumulator.degree)) {
                    return VertexWithDegree{&rhs, rhsDegree};
                }

                // Otherwise keep the same accumulator as before.
                return accumulator;
            });
    }

    std::vector<vertex_type> m_vertices; /*!< The vertices */
    std::vector<edge_type>   m_edges;    /*!< The edges */
};

/*!
 * \brief Swaps two directed graphs with each other.
 * \tparam VertexIdentifier The type of which instances are used to uniquely
 *                          identify vertices.
 * \tparam VertexData The type of the data stored on a vertex.
 * \tparam EdgeIdentifier The type of which instances are used to uniquely
 *                        identify edges.
 * \tparam EdgeData The type of the data stored on an edge.
 * \param lhs The first operand.
 * \param rhs The second operand.
 * \note Can be found by argument dependent lookup (ADL).
 **/
template<
    typename VertexIdentifier,
    typename VertexData,
    typename EdgeIdentifier,
    typename EdgeData>
void swap(
    DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData>& lhs,
    DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData>&
        rhs) noexcept
{
    lhs.swap(rhs);
}
} // namespace gp
#endif // INCG_GP_DIRECTED_GRAPH_HPP
