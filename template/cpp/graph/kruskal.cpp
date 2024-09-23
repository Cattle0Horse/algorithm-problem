/**
 * @file kruskal.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief
 * @version 0.1
 * @date 2024-07-21
 * @lastmodify 2024-07-22
 * @copyright Copyright (c) 2024
 *
 */
#include <functional>
#include <numeric>
#include <vector>
namespace OI::Graph {
template<typename Graph, bool SORTED_EDGES = false>
struct Kruskal {
    using WeightType = Graph::WeightType;
    using PointType = Graph::PointType;
    using SizeType = Graph::SizeType;
    using Edge = Graph::Edge;
    using EdgeContainer = Graph::EdgeContainer;
    static SizeType find(std::vector<SizeType>& parent, SizeType x) {
        while (x != parent[x]) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }
    bool operator()(Graph& g, auto op) {
        static_assert(std::is_convertible_v<decltype(op), std::function<void(const Edge&)>> || std::is_convertible_v<decltype(op), std::function<void(const PointType&, const PointType&, const WeightType&)>>,
                      "op must work as void(const Edge&) or void(const PointType&, const PointType&, const WeightType&)");
        if constexpr (!SORTED_EDGES) g.sortEdge();
        SizeType n = g.vertexSize();
        std::vector<SizeType> parent(n);
        std::iota(parent.begin(), parent.end(), static_cast<SizeType>(0));
        SizeType chosen = 0;
        for (auto& edge : g.edges()) {
            SizeType ru = find(parent, edge.from), rv = find(parent, edge.to);
            if (ru != rv) {
                parent[rv] = ru;
                if constexpr (std::is_convertible_v<decltype(op), std::function<void(const Edge&)>>) {
                    op(edge);
                } else {
                    op(edge.from, edge.to, edge.weight);
                }
                if (++chosen == n - 1) {
                    return true;
                }
            }
        }
        return false;
    }
};
} // namespace OI::Graph