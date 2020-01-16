#ifndef INCG_GP_TOTAL_ORDER_HPP
#define INCG_GP_TOTAL_ORDER_HPP
#include <ciso646> // not

/*!
 * \def GP_TOTAL_ORDER
 * \brief Defines a total ordering for the type given.
 * \warning There must be a correct operator< and operator== already defined for
 *          type.
 **/
#define GP_TOTAL_ORDER(type)                                 \
                                                             \
    inline bool operator!=(const type& lhs, const type& rhs) \
    {                                                        \
        return not(lhs == rhs);                              \
    }                                                        \
                                                             \
    inline bool operator>(const type& lhs, const type& rhs)  \
    {                                                        \
        return rhs < lhs;                                    \
    }                                                        \
                                                             \
    inline bool operator<=(const type& lhs, const type& rhs) \
    {                                                        \
        return not(lhs > rhs);                               \
    }                                                        \
                                                             \
    inline bool operator>=(const type& lhs, const type& rhs) \
    {                                                        \
        return not(lhs < rhs);                               \
    }
#endif // INCG_GP_TOTAL_ORDER_HPP
