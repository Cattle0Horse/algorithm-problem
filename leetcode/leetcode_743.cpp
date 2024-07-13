/**
 * @file leetcode_743.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/network-delay-time/
 * @version 0.1
 * @date 2024-07-13
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <utility>
#ifdef OY_LOCAL
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;
#endif

[[maybe_unused]] auto __init_io__ = []() {
    return std::cin.tie(nullptr)->sync_with_stdio(false);
}();

#include <vector>
namespace OI::Graph {
struct Ignore {};
template<typename T = Ignore>
struct Edge {
    uint32_t from, to;
    T weight;
    Edge(uint32_t _from, uint32_t _to, const T& _weight = T()): from(_from), to(_to), weight(_weight) {}
    bool operator<(const Edge<T>& o) const {
        static_assert(!std::is_same<T, Ignore>::value, "Must be not Ignore");
        return weight < o.weight;
    }
};
template<typename T = Ignore>
struct ForwardStarGraph {
    constexpr static int END_INDEX = -1;
    struct EdgeRange {
        struct EdgeIterator : std::forward_iterator_tag {
            ForwardStarGraph<T>* m_graph;
            int val;
            EdgeIterator(ForwardStarGraph* graph, int edge_index): m_graph(graph), val(edge_index) {}
            EdgeIterator& operator++() { return val = m_graph->m_next.at(val), *this; }
            bool operator!=(const EdgeIterator& other) const { return val != other.val; }
            bool operator==(const EdgeIterator& other) const { return val == other.val; }
            const Edge<T>& operator*() const { return m_graph->m_edges[val]; }
            const Edge<T>* operator->() const { return m_graph->m_edges.data() + val; }
            Edge<T>& operator*() { return m_graph->m_edges[val]; }
            Edge<T>* operator->() { return m_graph->m_edges.data() + val; }
        };
        // ForwardStarGraph<T>* m_graph;
        EdgeIterator m_begin;
        const EdgeIterator& m_end;
        EdgeRange(ForwardStarGraph<T>* graph): m_begin(graph, END_INDEX), m_end(graph->END_ITERATOR) {}
        const EdgeIterator& begin() const { return m_begin; }
        const EdgeIterator& end() const { return m_end; }
        EdgeIterator begin() { return m_begin; }
        const EdgeIterator& end() { return m_end; }
    };

private:
    const EdgeRange::EdgeIterator END_ITERATOR;

public:
    uint32_t m_vertex_size, m_edge_size;
    std::vector<Edge<T>> m_edges;
    std::vector<int> m_next;
    std::vector<EdgeRange> m_head; // 尾插法, 每次更新尾节点索引

    const EdgeRange& operator[](uint32_t u) const { return m_head[u]; }
    EdgeRange operator[](uint32_t u) { return m_head[u]; }

    ForwardStarGraph(uint32_t vertex_size, uint32_t edge_size = 0): END_ITERATOR(this, END_INDEX), m_vertex_size(vertex_size), m_edge_size(0), m_head(vertex_size, EdgeRange(this)) {
        m_edges.reserve(edge_size);
        m_next.reserve(edge_size);
    }
    void addEdge(uint32_t u, uint32_t v, const T& weight = T()) {
        m_edges.emplace_back(u, v, weight);
        m_next.push_back(std::exchange(m_head[u].m_begin.val, m_edge_size++));
    }
    void addEdge(const Edge<T>& edge) {
        m_edges.push_back(edge);
        m_next.push_back(std::exchange(m_head[edge.from].m_begin.val, m_edge_size++));
    }
    void addEdge2(uint32_t u, uint32_t v, const T& w = T()) { addEdge(u, v, w), addEdge(v, u, w); }
};
} // namespace OI::Graph
template<typename R, R INF = std::numeric_limits<R>::max() / 2, typename Graph>
std::vector<R> heap_dijkstra(const Graph& g, uint32_t start) {
    auto cmp = [](const std::pair<uint32_t, R>& a, const std::pair<uint32_t, R>& b) {
        return a.second > b.second;
    };
    std::priority_queue<std::pair<uint32_t, R>, std::vector<std::pair<uint32_t, R>>, decltype(cmp)> q(cmp);
    std::vector<int> dis(g.m_vertex_size, INF);
    std::vector<bool> vis(g.m_vertex_size);
    int newest = start;
    dis[newest] = 0;
    vis[newest] = true;
    // find the n-1 vertices
    for (auto i{1u}; i < g.m_vertex_size; i += 1) {
        // 1. update
        for (auto&& [_, v, w] : g[newest]) {
            if (vis[v]) continue;
            if (dis[v] > dis[newest] + w) {
                q.emplace(v, dis[v] = dis[newest] + w);
            }
        }
        // 2. scan: find the min dis
        newest = -1;
        while (!q.empty()) {
            uint32_t v = q.top().first;
            q.pop();
            if (!vis[v]) {
                // 3. add: choose the vertex
                newest = v;
                break;
            }
        }
        if (newest == -1) break;
        vis[newest] = true;
    }
    return dis;
}

template<typename R, R INF = std::numeric_limits<R>::max() / 2, typename Graph>
std::vector<R> dijkstra(const Graph& g, uint32_t start) {
    std::vector<int> dis(g.m_vertex_size, INF);
    std::vector<bool> vis(g.m_vertex_size);
    int newest = start;
    dis[newest] = 0;
    vis[newest] = true;
    // find the n-1 vertices
    for (auto k{1u}; k < g.m_vertex_size; k += 1) {
        // 1. update
        for (auto&& [_, v, w] : g[newest]) {
            if (vis[v]) continue;
            if (dis[v] > dis[newest] + w) {
                dis[v] = dis[newest] + w;
            }
        }
        // 2. scan: find the min dis
        newest = -1;
        R minimum = std::numeric_limits<R>::max();
        for (auto i{0u}; i < g.m_vertex_size; i += 1) {
            if (!vis[i] && dis[i] < minimum) {
                minimum = dis[i];
                newest = i;
            }
        }
        if (newest == -1) break;
        // 3. add: choose the vertex
        vis[newest] = true;
    }
    return dis;
}
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        OI::Graph::ForwardStarGraph<int> g(n, times.size());
        for (auto&& time : times) {
            int u = time[0] - 1, v = time[1] - 1, w = time[2];
            g.addEdge(u, v, w);
        }
        int ans = std::ranges::max(heap_dijkstra<int, 0x3f3f3f3f>(g, k - 1));
        return ans == 0x3f3f3f3f ? -1 : ans;
    }
};