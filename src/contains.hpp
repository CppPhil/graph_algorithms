#ifndef INCG_GP_CONTAINS_HPP
#define INCG_GP_CONTAINS_HPP
#include <iterator>                      // std::end
#include <pl/algo/ranged_algorithms.hpp> // pl::algo::find
#include <pl/annotations.hpp>            // PL_NODISCARD
#include <pl/meta/remove_cvref.hpp>      // pl::meta::remove_cvref_t

namespace gp {
/*!
 * \brief Checks whether a given container contains a given element.
 * \tparam Container The type of the container.
 * \param container The container.
 * \param element The element to check for.
 * \return true if container contains element; otherwise false.
 **/
template<typename Container>
PL_NODISCARD inline bool contains(
    const Container& container,
    const typename pl::meta::remove_cvref_t<Container>::value_type&
        element) noexcept
{
    return pl::algo::find(container, element) != std::end(container);
}
} // namespace gp
#endif // INCG_GP_CONTAINS_HPP
