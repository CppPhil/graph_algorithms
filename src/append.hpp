#ifndef INCG_GP_APPEND_HPP
#define INCG_GP_APPEND_HPP
#include <iterator>           // std::make_move_iterator, std::begin, std::end
#include <pl/annotations.hpp> // PL_NODISCARD

namespace gp {
/*!
 * \brief Appends two containers together.
 * \tparam Container The type of the containers to append.
 * \param lhs The left hand side container.
 * \param rhs The right hand side container.
 * \return The result of appending rhs to lhs.
 **/
template<typename Container>
PL_NODISCARD inline Container append(Container lhs, Container rhs)
{
    lhs.insert(
        std::end(lhs),
        std::make_move_iterator(std::begin(rhs)),
        std::make_move_iterator(std::end(rhs)));
    return lhs;
}
} // namespace gp
#endif // INCG_GP_APPEND_HPP
