/**
 * @file leetcode_2492.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/minimum-score-of-a-path-between-two-cities/description/
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
    int minScore(int n, vector<vector<int>>& roads) {
        OI::Graph::ForwardStarGraph<int> g(n, roads.size() << 1);
        for (auto&& road : roads) {
            g.addEdge2(road[0] - 1, road[1] - 1, road[2]);
        }

        // std::queue<int> q;
        // std::vector<bool> vis(n);
        // vis[0] = true;
        // q.push(0);
        // int ans = 0x3f3f3f3f;
        // while (!q.empty()) {
        //     int u = q.front();
        //     q.pop();
        //     for (auto&& [_, v, w] : g[u]) {
        //         if (vis[v]) continue;
        //         q.push(v);
        //         ans = std::min(ans, w);
        //     }
        // }

        int ans = 0x3f3f3f3f;
        std::vector<bool> vis(n);
        auto dfs = [&](auto&& self, int u) -> void {
            vis[u] = true;
            for (auto&& [_, v, w] : g[u]) {
                ans = std::min(ans, w);
                if (!vis[v]) self(self, v);
            }
        };
        dfs(dfs, 0);
        return ans;
    }
};

/**
 * @file union_find_v2.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief 支持带权的并查集
 * @version 0.1
 * @date 2024-07-13
 *
 * @copyright Copyright (c) 2024
 * fork from https://github.com/old-yan/CP-template
 * 若要使用带权并查集, 请定义一个拥有默认构造函数与unite合并两个节点的对象
 * struct Node {
 *     size_t vertex_size = 1, edge_size = 0;
 *     void unite(const Node& o) {
 *         vertex_size += o.vertex_size;
 *         edge_size += o.edge_size + 1;
 *     }
 * };
 **/
#include <algorithm>
#include <cstdint>
#include <numeric>
#include <vector>

namespace OI::DataStructure {
namespace DSU {
struct Ignore {};
using size_type = uint32_t;
template<bool MaintainGroupSize, typename ValueType = Ignore>
struct Table {
    mutable std::vector<size_type> m_father, m_group_size;
    mutable std::vector<ValueType> m_value;
    size_type m_init_size, m_cur_size, m_group_cnt;
    explicit Table(size_type n = 0, const ValueType& value = ValueType()) { resize(n, value); }
    void resize(size_type n, const ValueType& value = ValueType()) {
        if (!(m_init_size = m_cur_size = m_group_cnt = n)) return;
        m_father.resize(m_cur_size);
        if constexpr (MaintainGroupSize) m_group_size.resize(m_cur_size, 1);
        if constexpr (!std::is_same<ValueType, Ignore>::value) m_value.resize(m_cur_size, value);
        std::iota(m_father.begin(), m_father.end(), 0);
    }
    [[nodiscard]] size_type find(size_type i) const { return m_father[i] == i ? i : m_father[i] = find(m_father[i]); }
    template<bool IsHead = false>
    [[nodiscard]] size_type size(size_type i) const {
        static_assert(MaintainGroupSize, "MaintainGroupSize Must Be True");
        if constexpr (IsHead) return m_group_size[i];
        else return m_group_size[find(i)];
    }
    template<bool IsHead = false>
    [[nodiscard]] ValueType& value(size_type i) const {
        static_assert(!std::is_same<ValueType, Ignore>::value, "MaintainGroupSize Must Be True");
        if constexpr (IsHead) return m_value[i];
        else return m_value[find(i)];
    }
    void unite_to(size_type head_from, size_type head_to) {
        if (head_from == head_to) return;
        m_father[head_from] = head_to;
        if constexpr (MaintainGroupSize) m_group_size[head_to] += m_group_size[head_from];
        if constexpr (!std::is_same<ValueType, Ignore>::value) m_value[head_to].unite(m_value[head_from]);
        m_group_cnt--;
    }
    bool unite_by_size(size_type a, size_type b) {
        static_assert(MaintainGroupSize, "MaintainGroupSize Must Be True");
        a = find(a), b = find(b);
        if (a == b) return false;
        if (m_group_size[a] > m_group_size[b]) std::swap(a, b);
        unite_to(a, b);
        return true;
    }
    bool unite_by_id(size_type a, size_type b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (a < b) std::swap(a, b);
        unite_to(a, b);
        return true;
    }
    [[nodiscard]] bool in_same_group(size_type a, size_type b) const { return find(a) == find(b); }
    [[nodiscard]] bool is_head(size_type i) const { return i == m_father[i]; }
    std::vector<size_type> heads() const {
        std::vector<size_type> ret;
        ret.reserve(m_group_cnt);
        for (size_type i = 0; i != m_cur_size; i++)
            if (is_head(i)) ret.push_back(i);
        return ret;
    }
    std::vector<std::vector<size_type>> groups() const {
        if constexpr (MaintainGroupSize) {
            std::vector<std::vector<size_type>> ret(m_group_cnt);
            std::vector<size_type> index(m_cur_size);
            for (size_type i = 0, j = 0; i != m_cur_size; i++)
                if (is_head(i)) ret[j].reserve(m_group_size[i]), index[i] = j++;
            for (size_type i = 0; i != m_cur_size; i++) ret[index[find(i)]].push_back(i);
            return ret;
        } else {
            std::vector<std::vector<size_type>> ret(m_group_cnt);
            std::vector<size_type> index(m_cur_size), cnt(m_group_cnt);
            for (size_type i = 0, j = 0; i != m_cur_size; i++)
                if (is_head(i)) index[i] = j++;
            for (size_type i = 0; i != m_cur_size; i++) cnt[index[find(i)]]++;
            for (size_type i = 0; i != m_group_cnt; i++) ret[i].reserve(cnt[i]);
            for (size_type i = 0; i != m_cur_size; i++) ret[index[find(i)]].push_back(i);
            return ret;
        }
    }
};
template<typename Ostream, bool MaintainGroupSize, typename ValueType>
Ostream& operator<<(Ostream& out, const Table<MaintainGroupSize, ValueType>& x) {
    out << "[";
    for (size_type i = 0; i != x.m_cur_size; i++) {
        if (i) out << ", ";
        out << x.m_father[i];
    }
    return out << "]";
}
} // namespace DSU
template<bool MaintainGroupSize, typename ValueType = DSU::Ignore>
using DSUTable = DSU::Table<MaintainGroupSize, ValueType>;
} // namespace OI::DataStructure

class Solution2 {
public:
    int minScore(int n, vector<vector<int>>& roads) {
        std::vector<int> val(n, 0x3f3f3f3f);
        OI::DataStructure::DSUTable<false> dsu(n);
        for (auto&& road : roads) {
            int u = road[0], v = road[1], w = road[2];
            dsu.unite_by_id(u, v);
            int root = dsu.find(u);
            val[root] = std::min(val[root], w);
        }
        return std::ranges::min(val);
    }
};