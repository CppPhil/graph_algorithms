#ifndef INCG_GP_ROMANIA_CITY_HPP
#define INCG_GP_ROMANIA_CITY_HPP
#include <cstdint>            // std::int32_t
#include <iosfwd>             // std::ostream
#include <pl/string_view.hpp> // pl::string_view
#include <stdexcept>          // std::logic_error
#include <string>             // std::string

namespace gp {
namespace romania {
/*!
 * \def GP_ROMANIA_CITY_X_MACRO
 * \brief X-Macro for the cities of Romania.
 **/
#define GP_ROMANIA_CITY_X_MACRO \
    X(Arad)                     \
    X(Bucharest)                \
    X(Craiova)                  \
    X(Dobreta)                  \
    X(Eforie)                   \
    X(Fagaras)                  \
    X(Giurgiu)                  \
    X(Hirsova)                  \
    X(Iasi)                     \
    X(Lugoj)                    \
    X(Mehadia)                  \
    X(Neamt)                    \
    X(Oradea)                   \
    X(Pitesti)                  \
    X(RimnicuVilcea)            \
    X(Sibiu)                    \
    X(Timisoara)                \
    X(Urziceni)                 \
    X(Vaslui)                   \
    X(Zerind)

/*!
 * \brief Scoped enumerator for the Romanian cities.
 **/
enum class City : std::int32_t {
#define X(CityName) CityName,
    GP_ROMANIA_CITY_X_MACRO
#undef X
};

/*!
 * \brief Turns a given Romanian city enumerator into its string representation.
 * \param city The city to get a string for.
 * \return The resulting string.
 **/
std::string asString(City city);

/*!
 * \brief Converts a string back to a City enumerator.
 * \param string The string to use.
 * \return The corresponding City enumerator.
 * \throws std::logic_error if the string given is invalid.
 **/
City fromString(pl::string_view string);

/*!
 * \brief Prints a City to an ostream.
 * \param os The ostream to print to.
 * \param city The City to print.
 * \return A reference to 'os'.
 **/
std::ostream& operator<<(std::ostream& os, City city);
} // namespace romania
} // namespace gp
#endif // INCG_GP_ROMANIA_CITY_HPP
