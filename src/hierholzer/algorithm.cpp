#include "algorithm.hpp"

namespace gp {
namespace hierholzer {
namespace detail {
int sourceOf(int edgeIdentifier) { return edgeIdentifier / 10; }

int targetOf(int edgeIdentifier) { return edgeIdentifier % 10; }

int reverseEdgeOf(int edgeIdentifier)
{
    return ((edgeIdentifier % 10) * 10) + (edgeIdentifier / 10);
}
} // namespace detail
} // namespace hierholzer
} // namespace gp
