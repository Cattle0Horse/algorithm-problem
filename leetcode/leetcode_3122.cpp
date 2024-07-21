/**
 * @file leetcode_3122.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/minimum-time-to-visit-disappearing-nodes/description/?envType=daily-question&envId=2024-07-18
 * @version 0.1
 * @date 2024-07-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifdef Cattle_Horse
#include "leetcode.h" // IWYU pragma: keep
using namespace std;
#else
#define dbg(...) void(114514)
#endif

[[maybe_unused]] auto __init_io__ = []() {
    return std::cin.tie(nullptr)->sync_with_stdio(false);
}();

/**
 * @file forward_star_graph.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief 链式前向星存图(一维静态链表)
 * @version 0.2
 * @date 2024-07-13
 * @lastmodify 2024-07-18
 * @copyright Copyright (c) 2024
 *
 */
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
template<typename T = Ignore, typename OffsetType = int64_t>
struct ForwardStarGraph {
    constexpr static int END_INDEX = std::numeric_limits<int>::min();
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
    OffsetType m_start;
    std::vector<Edge<T>> m_edges;
    std::vector<int> m_next;
    std::vector<EdgeRange> m_head; // 尾插法, 每次更新尾节点索引

    const EdgeRange& operator[](uint32_t u) const { return m_head[u - m_start]; }
    EdgeRange operator[](uint32_t u) { return m_head[u - m_start]; }

    ForwardStarGraph(OffsetType start, uint32_t vertex_size, uint32_t edge_size)
        : END_ITERATOR(this, END_INDEX), m_vertex_size(vertex_size), m_edge_size(0), m_start(start), m_head(vertex_size, EdgeRange(this)) {
        m_edges.reserve(edge_size);
        m_next.reserve(edge_size);
    }
    ForwardStarGraph(uint32_t vertex_size, uint32_t edge_size): ForwardStarGraph(0, vertex_size, edge_size) {}
    void addEdge(uint32_t u, uint32_t v, const T& weight = T()) {
        m_edges.emplace_back(u, v, weight);
        m_next.push_back(std::exchange(m_head[u - m_start].m_begin.val, m_edge_size++));
    }
    void addEdge(const Edge<T>& edge) {
        m_edges.push_back(edge);
        m_next.push_back(std::exchange(m_head[edge.from - m_start].m_begin.val, m_edge_size++));
    }
    void addEdge2(uint32_t u, uint32_t v, const T& w = T()) { addEdge(u, v, w), addEdge(v, u, w); }
    template<std::integral R = uint32_t>
    std::vector<R> inDegree() {
        std::vector<R> in_degree(m_vertex_size, 0);
        for (auto&& [u, v, w] : m_edges) in_degree[v - m_start] += 1;
        return in_degree;
    }
    template<std::integral R = uint32_t>
    std::vector<R> outDegree() {
        std::vector<R> out_degree(m_vertex_size, 0);
        for (auto&& [u, v, w] : m_edges) out_degree[u - m_start] += 1;
        return out_degree;
    }
    template<typename Iterator>
    Iterator topology(Iterator result_begin) {
        auto degree{inDegree()};
        Iterator result_end{result_begin};
        for (auto i{0u}; i < m_vertex_size; i += 1) {
            if (degree[i] == 0) {
                *result_end = static_cast<OffsetType>(i) + m_start;
                ++result_end;
            }
        }
        for (; result_begin != result_end; ++result_begin) {
            for (auto&& [u, v, w] : m_head[*result_begin - m_start]) {
                if (--degree[static_cast<OffsetType>(v) - m_start] == 0) {
                    *result_end = v;
                    ++result_end;
                }
            }
        }
        return result_end;
    }
};
} // namespace OI::Graph

class Solution {
public:
    vector<int> minimumTime(int n, vector<vector<int>>& edges, vector<int>& disappear) {
        OI::Graph::ForwardStarGraph<int> graph(n, edges.size());
        for (auto&& edge : edges) {
            graph.addEdge2(edge[0], edge[1], edge[2]);
        }
        std::vector<int> distances(n, -1);
        std::vector<bool> vis(n);
        distances[0] = 0;
        std::priority_queue<std::pair<int, int>, vector<pair<int, int>>, greater<>> q;
        q.emplace(0, 0);
        for (int _ = 1; _ < n; ++_) {
            int u = -1;
            while (!q.empty()) {
                int x = q.top().second;
                q.pop();
                if (!vis[x]) {
                    u = x;
                    break;
                }
            }
            if (u == -1) break;
            vis[u] = true;
            for (auto&& [_, v, w] : graph[u]) {
                int dis = distances[u] + w;
                // 要在消失之前到达该点
                if (!vis[v] && (distances[v] == -1 || distances[v] > dis) && disappear[v] > dis) {
                    distances[v] = dis;
                    q.emplace(dis, v);
                }
            }
        }
        return distances;
    }
};

#ifdef Cattle_Horse
int main() {
    //
}
#endif