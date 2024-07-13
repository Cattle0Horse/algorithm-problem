/**
 * @file leetcode_2101.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/detonate-the-maximum-bombs/description/
 * @version 0.1
 * @date 2024-07-13
 *
 * @copyright Copyright (c) 2024
 *
 */

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
// 边模板类
template<typename T = Ignore>
struct Edge {
    uint32_t from, to;
    T weight;
    Edge(uint32_t _from, uint32_t _to, const T& _weight = T()): from(_from), to(_to), weight(_weight) {}
};
template<typename T = Ignore>
struct ForwardStarGraph {
    constexpr static int END_INDEX = -1;
    uint32_t m_vertex_size, m_edge_size;
    std::vector<Edge<T>> m_edges;
    std::vector<int> m_next_index;
    std::vector<int> m_head; // 每个节点的第一条边的索引(尾插法)
    ForwardStarGraph(uint32_t vertex_size, uint32_t edge_size = 0): m_vertex_size(vertex_size), m_edge_size(0), m_head(vertex_size, END_INDEX) {
        m_edges.reserve(edge_size);
        m_next_index.reserve(edge_size);
    }
    void addEdge(uint32_t u, uint32_t v, const T& weight = T()) {
        m_edges.emplace_back(u, v, weight);
        m_next_index.push_back(m_head[u]);
        m_head[u] = m_edge_size++;
    }
    void addEdge(const Edge<T>& edge) {
        m_edges.push_back(edge);
        m_next_index.push_back(m_head[edge.from]);
        m_head[edge.from] = m_edge_size++;
    }
    void addEdge2(uint32_t u, uint32_t v, const T& w = T()) { addEdge(u, v, w), addEdge(v, u, w); }
    struct EdgeRange {
        struct EdgeIterator : std::forward_iterator_tag {
            ForwardStarGraph<T>* m_graph;
            int m_index; // 当前边的索引
            EdgeIterator(ForwardStarGraph* graph, int edge_index): m_graph(graph), m_index(edge_index) {}
            EdgeIterator& operator++() { return m_index = m_graph->m_next_index.at(m_index), *this; }
            bool operator!=(const EdgeIterator& other) const { return m_index != other.m_index; }
            bool operator==(const EdgeIterator& other) const { return m_index == other.m_index; }
            Edge<T>& operator*() const { return m_graph->m_edges[m_index]; }
            Edge<T>* operator->() const { return &(m_graph->m_edges[m_index]); }
        };
        // ForwardStarGraph<T>* m_graph;
        EdgeIterator m_begin, m_end;
        EdgeRange(ForwardStarGraph<T>* graph, uint32_t u): m_begin(graph, graph->m_head[u]), m_end(graph, END_INDEX) {}
        const EdgeIterator begin() const { return m_begin; }
        const EdgeIterator end() const { return m_end; }
        EdgeIterator begin() { return m_begin; }
        EdgeIterator end() { return m_end; }
    };
    const EdgeRange& operator[](uint32_t u) const { return EdgeRange(this, u); }
    EdgeRange operator[](uint32_t u) { return EdgeRange(this, u); }
};
} // namespace OI::Graph

class Solution {
public:
    int maximumDetonation(vector<vector<int>>& bombs) {
        int n = bombs.size();
        OI::Graph::ForwardStarGraph g(n, n << 1);
        for (auto i{0}; i < n; i += 1) {
            long long x = bombs[i][0], y = bombs[i][1], r = bombs[i][2];
            for (auto j{0}; j < n; j += 1) {
                long long dx = x - bombs[j][0];
                long long dy = y - bombs[j][1];
                if (j != i && dx * dx + dy * dy <= r * r) {
                    g.addEdge(i, j);
                }
            }
        }
        int ans = 0;
        vector<int> vis(n);
        auto dfs = [&](auto&& dfs, int x) -> int {
            vis[x] = true;
            int cnt = 1;
            for (auto&& [u, v, w] : g[x]) {
                if (!vis[v]) {
                    cnt += dfs(dfs, v);
                }
            }
            return cnt;
        };
        for (int i = 0; i < n; i++) {
            ranges::fill(vis, 0);
            ans = max(ans, dfs(dfs, i));
        }
        return ans;
    }
};