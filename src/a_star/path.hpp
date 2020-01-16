/*!
 * \file path.hpp
 * \brief Exports the Path class template.
 **/
#ifndef INCG_GP_A_STAR_PATH_HPP
#define INCG_GP_A_STAR_PATH_HPP
#include "identifier_with_cost.hpp"      // gp::a_star::IdentifierWithCost
#include <cstddef>                       // std::size_t
#include <initializer_list>              // std::initializer_list
#include <iterator>                      // std::back_inserter
#include <ostream>                       // std::ostream
#include <pl/algo/ranged_algorithms.hpp> // pl::algo::transform
#include <stdexcept>                     // std::out_of_range
#include <vector>                        // std::vector

namespace gp {
namespace a_star {
/*!
 * \brief Type for a path of vertices through a graph.
 * \tparam VertexIdentifier the type of the kind of object used to identify a
 *                          vertex.
 **/
template<typename VertexIdentifier>
class Path {
public:
    // Type aliases
    // See https://www.youtube.com/watch?v=qGxuD9o4GDA for the usage of the
    // typename keyword in this context.
    typedef Path                                              this_type;
    typedef std::vector<IdentifierWithCost<VertexIdentifier>> container_type;
    typedef typename container_type::iterator                 iterator;
    typedef typename container_type::const_iterator           const_iterator;
    typedef typename container_type::reverse_iterator         reverse_iterator;
    typedef
        typename container_type::const_reverse_iterator const_reverse_iterator;

    /*!
     * \brief Creates an empty path.
     **/
    Path() = default;

    /*!
     * \brief Initializer list constructor.
     * \param initList The initializer_list to initialize with.
     **/
    Path(std::initializer_list<IdentifierWithCost<VertexIdentifier>> initList)
        : m_vector(initList.begin(), initList.end())
    {
    }

    /*!
     * \brief Returns an iterator to the first element of the path.
     * \return Iterator to the first element.
     * \note Constant complexity
     * \warning If the path is empty, the returned iterator will be equal to
     *          end().
     **/
    iterator begin() { return m_vector.begin(); }

    /*!
     * \brief Returns an iterator to the first element of the path.
     * \return Iterator to the first element.
     * \note Constant complexity
     * \warning If the path is empty, the returned iterator will be equal to
     *          end().
     **/
    const_iterator begin() const { return m_vector.begin(); }

    /*!
     * \brief Returns an iterator to the first element of the path.
     * \return Iterator to the first element.
     * \note Constant complexity
     * \warning If the path is empty, the returned iterator will be equal to
     *          end().
     **/
    const_iterator cbegin() const { return m_vector.cbegin(); }

    /*!
     * \brief Returns an iterator to the element following the last element of
     *        the path.
     * \return Iterator to the element following the last element.
     * \note Constant complexity
     * \warning The element referred to by the iterator returned acts as a
     *          placeholder; attempting to access it results in
     *          undefined behavior.
     **/
    iterator end() { return m_vector.end(); }

    /*!
     * \brief Returns an iterator to the element following the last element of
     *        the path.
     * \return Iterator to the element following the last element.
     * \note Constant complexity
     * \warning The element referred to by the iterator returned acts as a
     *          placeholder; attempting to access it results in
     *          undefined behavior.
     **/
    const_iterator end() const { return m_vector.end(); }

    /*!
     * \brief Returns an iterator to the element following the last element of
     *        the path.
     * \return Iterator to the element following the last element.
     * \note Constant complexity
     * \warning The element referred to by the iterator returned acts as a
     *          placeholder; attempting to access it results in
     *          undefined behavior.
     **/
    const_iterator cend() const { return m_vector.cend(); }

    /*!
     * \brief Returns a reverse iterator to the first element of the reversed
     *        path.
     * \return Reverse iterator to the first element. \note Constant
     *         complexity
     *
     * Returns a reverse iterator to the first element of the reversed path.
     * It corresponds to the last element of the non-reversed path.
     * If the path is empty, the returned iterator is equal to rend().
     **/
    reverse_iterator rbegin() { return m_vector.rbegin(); }

    /*!
     * \brief Returns a reverse iterator to the first element of the reversed
     *        path.
     * \return Reverse iterator to the first element. \note Constant
     *         complexity
     *
     * Returns a reverse iterator to the first element of the reversed path.
     * It corresponds to the last element of the non-reversed path.
     * If the path is empty, the returned iterator is equal to rend().
     **/
    const_reverse_iterator rbegin() const { return m_vector.rbegin(); }

    /*!
     * \brief Returns a reverse iterator to the first element of the reversed
     *        path.
     * \return Reverse iterator to the first element. \note Constant
     *         complexity
     *
     * Returns a reverse iterator to the first element of the reversed path.
     * It corresponds to the last element of the non-reversed path.
     * If the path is empty, the returned iterator is equal to rend().
     **/
    const_reverse_iterator crbegin() const { return m_vector.crbegin(); }

    /*!
     * \brief Returns a reverse iterator to the element following the last
     *        element of the reversed path.
     * \return Reverse iterator to the element
     *         following the last element.
     * \note Constant complexity
     * \warning Dereferencing the iterator returned results in
     *          undefined behavior.
     *
     * Returns a reverse iterator to the element following the last element of
     * the reversed path. It corresponds to the element preceding the first
     * element of the non-reversed path.
     **/
    reverse_iterator rend() { return m_vector.rend(); }

    /*!
     * \brief Returns a reverse iterator to the element following the last
     *        element of the reversed path.
     * \return Reverse iterator to the element
     *         following the last element.
     * \note Constant complexity
     * \warning Dereferencing the iterator returned results in
     *          undefined behavior.
     *
     * Returns a reverse iterator to the element following the last element of
     * the reversed path. It corresponds to the element preceding the first
     * element of the non-reversed path.
     **/
    const_reverse_iterator rend() const { return m_vector.rend(); }

    /*!
     * \brief Returns a reverse iterator to the element following the last
     *        element of the reversed path.
     * \return Reverse iterator to the element
     *         following the last element.
     * \note Constant complexity
     * \warning Dereferencing the iterator returned results in
     *          undefined behavior.
     *
     * Returns a reverse iterator to the element following the last element of
     * the reversed path. It corresponds to the element preceding the first
     * element of the non-reversed path.
     **/
    const_reverse_iterator crend() const { return m_vector.crend(); }

    /*!
     * \brief Appends a new VertexIdentifier along with its g value to this
     *        path.
     * \param identifier The VertexIdentifier to append.
     * \param g The g value associated with identifier.
     **/
    this_type& append(VertexIdentifier identifier, std::size_t g)
    {
        m_vector.emplace_back(identifier, g);
        return *this;
    }

    /*!
     * \brief Appends an IdentifierWithCost to this path.
     * \param identifier The IdentifierWithCost to append.
     **/
    this_type& append(IdentifierWithCost<VertexIdentifier> identifier)
    {
        m_vector.push_back(identifier);
        return *this;
    }

    /*!
     * \brief Queries for the size of this path.
     * \return The amount of vertices in this path.
     **/
    std::size_t size() const { return m_vector.size(); }

    /*!
     * \brief Queries this path for emptiness.
     * \return true if this path contains no vertices; otherwise false.
     **/
    bool isEmpty() const { return m_vector.empty(); }

    /*!
     * \brief Returns a reference to the first element.
     * \throws out_of_range if this path is empty.
     **/
    IdentifierWithCost<VertexIdentifier>& front()
    {
        if (isEmpty()) {
            throw std::out_of_range(
                "front may not be called on an empty path.");
        }

        return m_vector.front();
    }

    /*!
     * \brief Returns a const reference to the first element.
     * \throws out_of_range if this path is empty.
     * \note This is the const overload.
     **/
    const IdentifierWithCost<VertexIdentifier>& front() const
    {
        return const_cast<this_type*>(this)->front();
    }

    /*!
     * \brief Returns a reference to the last element.
     * \throws out_of_range if this path is empty.
     **/
    IdentifierWithCost<VertexIdentifier>& back()
    {
        if (isEmpty()) {
            throw std::out_of_range("back may not be called on an empty path.");
        }

        return m_vector.back();
    }

    /*!
     * \brief Returns a const reference to the last element.
     * \throws out_of_range if this path is empty.
     * \note This is the const overload.
     **/
    const IdentifierWithCost<VertexIdentifier>& back() const
    {
        return const_cast<this_type*>(this)->back();
    }

    /*!
     * \brief Calculates the g cost of this entire path.
     * \return The g value for this path.
     **/
    std::size_t g() const
    {
        // Start out as 0.
        std::size_t theCost{0};

        // Iterate over all the elements.
        for (const IdentifierWithCost<VertexIdentifier>& identifier :
             m_vector) {
            // Accumulate the g value of the current element
            theCost += identifier.g();
        }

        return theCost;
    }

    /*!
     * \brief Returns the 'raw' path representation of this Path.
     * \return A vector containing just the vertex identifiers on the path.
     **/
    std::vector<VertexIdentifier> rawPath() const
    {
        std::vector<VertexIdentifier> result{};

        pl::algo::transform(
            m_vector, std::back_inserter(result), [](const auto& e) {
                return e.vertexIdentifier();
            });

        return result;
    }

private:
    std::vector<IdentifierWithCost<VertexIdentifier>>
        m_vector; /*!< The underlying container */
};

/*!
 * \brief Prints a path.
 * \param os The ostream to print to.
 * \param thePath The path to print.
 * \tparam VertexIdentifier The type used to identify a vertex.
 * \return A reference to os.
 **/
template<typename VertexIdentifier>
std::ostream& operator<<(
    std::ostream&                 os,
    const Path<VertexIdentifier>& thePath)
{
    os << '[';

    for (typename Path<VertexIdentifier>::const_iterator it{thePath.begin()},
         end{thePath.end()};
         it != end;
         ++it) {
        os << *it;

        if (it != end - 1) { os << ",\n"; }
    }

    os << ']';
    return os;
}
} // namespace a_star
} // namespace gp
#endif // INCG_GP_A_STAR_PATH_HPP
