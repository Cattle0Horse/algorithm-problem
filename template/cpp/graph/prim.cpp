/**
 * @file prim.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief
 * @version 0.1
 * @date 2024-07-21
 * @lastmodify 2024-07-22
 * @copyright Copyright (c) 2024
 * todo: 参考python中的实现，使用边索引代替from数组
 *
 */
#include <functional>
#include <queue>
namespace OI::Graph {
template<typename Graph, typename T = Graph::WeightType, T INF = std::numeric_limits<T>::max() / 2, bool UseHeap = true>
struct Prim {
    using WeightType = Graph::WeightType;
    using PointType = Graph::PointType;
    using SizeType = Graph::SizeType;
    using Edge = Graph::Edge;
    using EdgeContainer = Graph::EdgeContainer;
    constexpr static SizeType NONE = std::numeric_limits<SizeType>::max();
    constexpr static WeightType inf() { return INF; }
    bool operator()(const Graph& g, PointType source, auto op) const {
        static_assert(std::is_convertible_v<decltype(op), std::function<void(const Edge&)>> || std::is_convertible_v<decltype(op), std::function<void(const PointType&, const PointType&, const WeightType&)>>,
                      "op must work as void(const Edge&) or void(const PointType&, const PointType&, const WeightType&)");
        SizeType n = g.vertexSize();
        std::vector<T> dis(n, inf());
        std::vector<PointType> from(n);
        std::vector<bool> vis(n);
        dis[g.getIndex(source)] = 0;
        if constexpr (UseHeap) {
            std::priority_queue<std::pair<T, PointType>, std::vector<std::pair<T, PointType>>, std::greater<>> q;
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
                if (u_index == NONE) return false;
                vis[u_index] = true;
                auto u{g.getOriginal(u_index)};
                if (u != source) {
                    if constexpr (std::is_convertible_v<decltype(op), std::function<void(const Edge&)>>) {
                        op(Edge(from[u_index], g.getOriginal(u_index), dis[u_index]));
                    } else {
                        op(from[u_index], g.getOriginal(u_index), dis[u_index]);
                    }
                }
                for (auto&& [_u, _v, _w] : g[u]) {
                    SizeType v_index = g.getIndex(_v);
                    if (!vis[v_index] && (dis[v_index] == inf() || dis[v_index] > _w)) {
                        from[v_index] = _u;
                        dis[v_index] = _w;
                        q.emplace(_w, _v);
                    }
                }
            }
        } else {
            for (SizeType _ = 0; _ < n; ++_) {
                SizeType u_index = NONE;
                T minimum = std::numeric_limits<T>::max();
                for (auto i{0}; i < n; i += 1) {
                    if (!vis[i] && dis[i] < minimum) {
                        minimum = dis[i];
                        u_index = i;
                    }
                }
                if (u_index == NONE) return false;
                vis[u_index] = true;
                auto u{g.getOriginal(u_index)};
                if (u != source) {
                    if constexpr (std::is_convertible_v<decltype(op), std::function<void(const Edge&)>>) {
                        op(Edge(from[u_index], g.getOriginal(u_index), dis[u_index]));
                    } else {
                        op(from[u_index], g.getOriginal(u_index), dis[u_index]);
                    }
                }
                for (auto&& [_u, _v, _w] : g[u]) {
                    SizeType v_index = g.getIndex(_v);
                    if (!vis[v_index] && (dis[v_index] == inf() || dis[v_index] > _w)) {
                        from[v_index] = _u;
                        dis[v_index] = _w;
                    }
                }
            }
        }
        return true;
    }
};
} // namespace OI::Graph