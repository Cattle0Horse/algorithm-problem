/**
 * @file leetcode_207.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/course-schedule/description/
 * @version 0.1
 * @date 2024-07-13
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <cassert>
#include <cstdint>
#include <queue>
#ifdef OY_LOCAL
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
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
 * @version 0.1
 * @date 2024-07-13
 *
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
    template<std::integral R = uint32_t>
    std::vector<R> inDegree() {
        std::vector<R> in_degree(m_vertex_size, 0);
        for (auto&& [u, v, w] : m_edges) in_degree[v] += 1;
        return in_degree;
    }
    template<std::integral R = uint32_t>
    std::vector<R> outDegree() {
        std::vector<R> out_degree(m_vertex_size, 0);
        for (auto&& [u, v, w] : m_edges) out_degree[u] += 1;
        return out_degree;
    }
    template<typename Iterator>
    Iterator topology(Iterator result_begin) {
        auto degree{inDegree()};
        Iterator result_end{result_begin};
        for (auto i{0u}; i < m_vertex_size; i += 1) {
            if (degree[i] == 0) {
                *result_end = i;
                ++result_end;
            }
        }
        for (; result_begin != result_end; ++result_begin) {
            for (auto&& [u, v, w] : m_head[*result_begin]) {
                if (--degree[v] == 0) {
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
    bool canFinish(int n, vector<vector<int>>& edges) {
        OI::Graph::ForwardStarGraph g(n);
        for (auto&& edge : edges) {
            g.addEdge(edge[1], edge[0]);
        }
        std::vector<uint32_t> ans(n);
        return g.topology(ans.begin()) == ans.end();
    }
};