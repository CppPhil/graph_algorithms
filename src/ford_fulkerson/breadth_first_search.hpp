#ifndef INCG_GP_FORD_FULKERSON_BREADTH_FIRST_SEARCH_HPP
#define INCG_GP_FORD_FULKERSON_BREADTH_FIRST_SEARCH_HPP
#include "../directed_graph.hpp"         // gp::DirectedGraph
#include <ciso646>                       // and, not
#include <cstdint>                       // std::int32_t
#include <pl/algo/ranged_algorithms.hpp> // pl::algo::transform
#include <pl/hash.hpp>                   // pl::hash
#include <queue>                         // std::queue
#include <tl/optional.hpp>               // tl::optional
#include <unordered_map>                 // std::unordered_map
#include <utility>                       // std::move

namespace gp {
namespace ford_fulkerson {
enum class Color : int { White = 0, Gray = 1, Black = 2 };

template<typename VertexIdentifier>
struct VertexPair {
    VertexPair(VertexIdentifier p_u, VertexIdentifier p_v)
        : u{std::move(p_u)}, v{std::move(p_v)}
    {
    }

    VertexIdentifier u;
    VertexIdentifier v;
};

template<typename VertexIdentifier>
bool operator==(
    const VertexPair<VertexIdentifier>& lhs,
    const VertexPair<VertexIdentifier>& rhs)
{
    return (lhs.u == rhs.u) and (lhs.v == rhs.v);
}

template<typename VertexIdentifier>
bool operator!=(
    const VertexPair<VertexIdentifier>& lhs,
    const VertexPair<VertexIdentifier>& rhs)
{
    return not(lhs == rhs);
}

template<typename VertexIdentifier>
void enqueue(
    std::queue<VertexIdentifier>&                q,
    const VertexIdentifier&                      x,
    std::unordered_map<VertexIdentifier, Color>& color)
{
    q.push(x);
    color[x] = Color::Gray;
}

template<typename VertexIdentifier>
VertexIdentifier dequeue(
    std::queue<VertexIdentifier>&                q,
    std::unordered_map<VertexIdentifier, Color>& color)
{
    const VertexIdentifier x{q.front()};
    q.pop();
    color[x] = Color::Black;
    return x;
}

template<
    typename VertexIdentifier,
    typename VertexData,
    typename EdgeIdentifier,
    typename EdgeData>
tl::optional<
    std::unordered_map<VertexIdentifier, tl::optional<VertexIdentifier>>>
breadthFirstSearch(
    const DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData>&
                            graph,
    const VertexIdentifier& start,
    const VertexIdentifier& target,
    const std::unordered_map<VertexPair<VertexIdentifier>, std::int32_t>&
                                                                          capacity,
    const std::unordered_map<VertexPair<VertexIdentifier>, std::int32_t>& flow)
{
    using graph_type
        = DirectedGraph<VertexIdentifier, VertexData, EdgeIdentifier, EdgeData>;
    using edge_type = typename graph_type::edge_type;

    std::unordered_map<VertexIdentifier, Color> color{};
    std::unordered_map<VertexIdentifier, tl::optional<VertexIdentifier>> pred{};
    std::queue<VertexIdentifier>                                         q{};

    for (const auto& vertex : graph.vertices()) {
        const VertexIdentifier& u{vertex.identifier()};
        color[u] = Color::White;
        pred[u]  = tl::nullopt;
    }

    enqueue(q, start, color);

    while (not q.empty()) {
        const VertexIdentifier u{dequeue(q, color)};

        // Search all adjacent white nodes v. If the capacity
        // from u to v in the residual network is positive,
        // enqueue v.
        const std::vector<VertexIdentifier> targets{[&graph, &u] {
            const std::vector<const edge_type*> outbounds{
                graph.outboundEdges(u)};
            std::vector<VertexIdentifier> vector(outbounds.size());
            pl::algo::transform(
                outbounds, vector.begin(), [](const edge_type* edge) {
                    return edge->target();
                });
            return vector;
        }()};

        for (const VertexIdentifier& v : targets) {
            if ((color[v] == Color::White)
                and ((
                    capacity.at(VertexPair{u, v}) - flow.at(VertexPair{u, v})
                    > 0))) {
                enqueue(q, v, color);
                pred[v] = u;
            }
        }
    }

    // If the color of the target node is black now,
    // it means that we reached it.
    if (color[target] == Color::Black) { return tl::make_optional(pred); }

    return tl::nullopt;
}
} // namespace ford_fulkerson
} // namespace gp

namespace std {
template<typename VertexIdentifier>
struct hash<::gp::ford_fulkerson::VertexPair<VertexIdentifier>> {
    size_t operator()(const ::gp::ford_fulkerson::VertexPair<VertexIdentifier>&
                          vertexPair) const
    {
        return ::pl::hash(vertexPair.u, vertexPair.v);
    }
};
} // namespace std
#endif // INCG_GP_FORD_FULKERSON_BREADTH_FIRST_SEARCH_HPP
