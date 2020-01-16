#ifndef INCG_GP_JOIN_HPP
#define INCG_GP_JOIN_HPP
#include <algorithm> // std::copy
#include <iterator>  // std::begin, std::end, std::prev, std::ostream_iterator
#include <pl/meta/remove_cvref.hpp> // pl::meta::remove_cvref_t
#include <pl/string_view.hpp>       // pl::string_view
#include <sstream>                  // std::ostringstream
#include <string>                   // std::string

namespace gp {
template<typename Range>
std::string join(const Range& range, pl::string_view delimiter)
{
    std::ostringstream oss{};

    auto       it   = begin(range);
    const auto last = end(range);

    if (it == last) { return ""; }

    const auto secondLast = std::prev(last);

    std::copy(
        it,
        secondLast,
        std::ostream_iterator<pl::meta::remove_cvref_t<decltype(*it)>>{
            oss, delimiter.data()});
    oss << *secondLast;

    return oss.str();
}
} // namespace gp
#endif // INCG_GP_JOIN_HPP
