/**
 * @file dijkstra.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief
 * @version 0.5
 * @date 2024-07-13
 * @lastmodify 2024-07-22
 * @copyright Copyright (c) 2024
 *
 */
#include <queue>
#include <vector>

namespace OI::Graph {
template<typename Graph, typename R = Graph::WeightType, R INF = std::numeric_limits<R>::max() / 2, bool UseHeap = true>
struct Dijkstra {
    using WeightType = Graph::WeightType;
    using PointType = Graph::PointType;
    using SizeType = Graph::SizeType;
    using Edge = Graph::Edge;
    using EdgeContainer = Graph::EdgeContainer;
    constexpr static SizeType NONE = std::numeric_limits<SizeType>::max();
    constexpr static R inf() { return INF; }
    std::vector<R> operator()(const Graph& g, PointType source) const {
        SizeType n = g.vertexSize();
        std::vector<R> distances(n, inf());
        std::vector<bool> vis(n);
        distances[g.getIndex(source)] = 0;
        if constexpr (UseHeap) {
            std::priority_queue<std::pair<R, PointType>, std::vector<std::pair<R, PointType>>, std::greater<>> q;
            q.emplace(0, source);
            for (SizeType _ = 0; _ < n; ++_) {
                SizeType u_index = NONE;
                while (!q.empty()) {
                    SizeType i = g.getIndex(q.top().second);
                    q.pop();
                    if (!vis[i]) {
                        u_index = i;
                        break;
                    }
                }
                if (u_index == NONE) break;
                vis[u_index] = true;
                for (auto&& [u, v, w] : g[g.getOriginal(u_index)]) {
                    R dis = distances[u_index] + w;
                    SizeType v_index = g.getIndex(v);
                    if (!vis[v_index] && (distances[v_index] == inf() || distances[v_index] > dis)) {
                        distances[v_index] = dis;
                        q.emplace(dis, v);
                    }
                }
            }
        } else {
            for (SizeType _ = 0; _ < n; ++_) {
                SizeType u_index = NONE;
                R minimum = std::numeric_limits<R>::max();
                for (auto i{0u}; i < n; i += 1) {
                    if (!vis[i] && distances[i] < minimum) {
                        minimum = distances[i];
                        u_index = i;
                    }
                }
                if (u_index == NONE) break;
                vis[u_index] = true;
                for (auto&& [u, v, w] : g[g.getOriginal(u_index)]) {
                    R dis = distances[u_index] + w;
                    SizeType v_index = g.getIndex(v);
                    if (!vis[v_index] && (distances[v_index] == inf() || distances[v_index] > dis)) {
                        distances[v_index] = dis;
                    }
                }
            }
        }
        return distances;
    }
};
} // namespace OI::Graph