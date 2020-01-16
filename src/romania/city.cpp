#include "city.hpp"

namespace gp {
namespace romania {
std::string asString(City city)
{
    std::string result{};

    switch (city) {
#define X(cityName) \
    case City::cityName: result = #cityName; break;
        GP_ROMANIA_CITY_X_MACRO
#undef X
    }

    if (result == "RimnicuVilcea") { return "Rimnicu Vilcea"; }

    return result;
}

City fromString(pl::string_view string)
{
#define X(cityName) \
    if (asString(City::cityName) == string) { return City::cityName; }
    GP_ROMANIA_CITY_X_MACRO
#undef X

    throw std::logic_error{
        "Invalid string passed to fromString for gp::romania::City"};
}

std::ostream& operator<<(std::ostream& os, City city)
{
    return os << '"' << asString(city) << '"';
}
} // namespace romania
} // namespace gp
