/**
 * @file forward_star_graph.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief 链式前向星存图(一维静态链表)
 * @version 0.5
 * @date 2024-07-13
 * @lastmodify 2024-08-11
 * @copyright Copyright (c) 2024
 *
 */
#include <algorithm>
#include <functional>
#include <vector>
#include <cstdint> // uint32_t
#include <utility> // std::exchange
namespace OI::Graph {
struct Ignore {};
template<typename T = Ignore, typename U = int>
struct Edge {
    using PointType = U;
    using WeightType = T;
    PointType from, to;
    WeightType weight;
    Edge(PointType _from, PointType _to, const WeightType& _weight = WeightType()): from(_from), to(_to), weight(_weight) {}
    bool operator<(const Edge<WeightType>& o) const {
        static_assert(!std::is_same<WeightType, Ignore>::value, "Must be not Ignore");
        return weight < o.weight;
    }
};
template<typename T = Ignore, typename U = int>
struct ForwardStarGraph {
    using SizeType = uint32_t;
    using PointType = U;
    using WeightType = T;
    using Edge = Edge<WeightType, PointType>;
    using EdgeContainer = std::vector<Edge>;
    using Graph = ForwardStarGraph<WeightType, PointType>;
    constexpr static int END_INDEX = std::numeric_limits<int>::min();
    struct EdgeRange {
        struct EdgeIterator {
            mutable Graph* m_graph;
            int val;
            EdgeIterator(Graph* graph, int edge_index): m_graph(graph), val(edge_index) {}
            EdgeIterator& operator++() { return val = m_graph->m_next.at(val), *this; }
            bool operator!=(const EdgeIterator& other) const { return val != other.val; }
            bool operator==(const EdgeIterator& other) const { return val == other.val; }
            Edge& operator*() const { return m_graph->m_edges[val]; }
            Edge* operator->() const { return m_graph->m_edges.data() + val; }
            Edge& operator*() { return m_graph->m_edges[val]; }
            Edge* operator->() { return m_graph->m_edges.data() + val; }
        };
        EdgeIterator m_begin;
        const EdgeIterator& m_end;
        EdgeRange(Graph* graph): m_begin(graph, END_INDEX), m_end(graph->END_ITERATOR) {}
        const EdgeIterator& begin() const { return m_begin; }
        const EdgeIterator& end() const { return m_end; }
        EdgeIterator begin() { return m_begin; }
        const EdgeIterator& end() { return m_end; }
    };

private:
    const EdgeRange::EdgeIterator END_ITERATOR;

public:
    SizeType m_vertex_size, m_edge_size;
    PointType m_start;
    mutable EdgeContainer m_edges;
    std::vector<int> m_next;
    std::vector<EdgeRange> m_head; // 尾插法, 每次更新尾节点索引

public:
    SizeType getIndex(PointType u) const { return u - m_start; }
    PointType getOriginal(SizeType i) const { return static_cast<PointType>(i) + m_start; }
    const EdgeRange& operator[](PointType u) const { return m_head[getIndex(u)]; }
    EdgeRange operator[](PointType u) { return m_head[getIndex(u)]; }
    SizeType vertexSize() const { return m_vertex_size; }
    SizeType edgeSize() const { return m_edge_size; }
    EdgeContainer& edges() { return m_edges; }
    const EdgeContainer& edges() const { return m_edges; }
    ForwardStarGraph(PointType start, SizeType vertex_size, SizeType edge_size)
        : END_ITERATOR(this, END_INDEX), m_vertex_size(vertex_size), m_edge_size(0), m_start(start), m_head(vertex_size, EdgeRange(this)) {
        m_edges.reserve(edge_size);
        m_next.reserve(edge_size);
    }
    ForwardStarGraph(SizeType vertex_size, SizeType edge_size): ForwardStarGraph(0, vertex_size, edge_size) {}
    void addEdge(PointType u, PointType v, const WeightType& weight = WeightType()) {
        m_edges.emplace_back(u, v, weight);
        m_next.push_back(std::exchange(m_head[getIndex(u)].m_begin.val, m_edge_size++));
    }
    void addEdge(const Edge& edge) {
        m_edges.push_back(edge);
        m_next.push_back(std::exchange(m_head[getIndex(edge.from)].m_begin.val, m_edge_size++));
    }
    void addEdge2(PointType u, PointType v, const WeightType& w = WeightType()) { addEdge(u, v, w), addEdge(v, u, w); }
    template<typename R = SizeType>
    std::vector<R> inDegree() const {
        std::vector<R> in_degree(m_vertex_size, 0);
        for (auto&& [u, v, w] : m_edges) in_degree[getIndex(v)] += 1;
        return in_degree;
    }
    template<typename R = SizeType>
    std::vector<R> outDegree() const {
        std::vector<R> out_degree(m_vertex_size, 0);
        for (auto&& [u, v, w] : m_edges) out_degree[getIndex(u)] += 1;
        return out_degree;
    }
    template<typename Iterator>
    Iterator topology(Iterator result_begin) const {
        auto degree{inDegree()};
        Iterator result_end{result_begin};
        for (auto i{0u}; i < m_vertex_size; i += 1) {
            if (degree[i] == 0) {
                *result_end = getOriginal(i);
                ++result_end;
            }
        }
        for (; result_begin != result_end; ++result_begin) {
            for (auto&& [u, v, w] : m_head[getIndex(*result_begin)]) {
                if (--degree[getIndex(v)] == 0) {
                    *result_end = v;
                    ++result_end;
                }
            }
        }
        return result_end;
    }
    void sortEdge() {
        std::sort(m_edges.begin(), m_edges.end());
        for (auto& edge_range : m_head) {
            edge_range.m_begin.val = END_INDEX;
        }
        for (SizeType edge_size = m_edge_size; edge_size != 0; edge_size -= 1) {
            SizeType index = edge_size - 1;
            m_next[index] = std::exchange(m_head[getIndex(m_edges[index].from)].m_begin.val, index);
        }
    }
    template<typename Strategy>
    auto shortestPath(Strategy strategy, PointType source) const {
        return strategy(*this, source);
    }
    template<typename Strategy, typename Op>
    bool minSpanTree(Strategy strategy, Op op) {
        static_assert(std::is_convertible_v<Op, std::function<void(const Edge&)>> || std::is_convertible_v<Op, std::function<void(const PointType&, const PointType&, const WeightType&)>>,
                      "op must work as void(const Edge&) or void(const PointType&, const PointType&, const WeightType&)");
        static_assert(std::is_convertible_v<Strategy, std::function<bool(const Graph&, PointType, Op)>> || std::is_convertible_v<Strategy, std::function<bool(Graph&, Op)>>,
                      "op must work as bool(const Graph&, PointType, Op) or bool(Graph&, Op)>");
        if constexpr (std::is_convertible_v<Strategy, std::function<bool(const Graph&, PointType, Op)>>) {
            return strategy(*this, 0, op);
        } else {
            return strategy(*this, op);
        }
    }
};
template<typename T = Ignore, typename U = int>
struct Tree : public ForwardStarGraph<T, U> {
public:
    using SizeType = uint32_t;
    using PointType = U;
    using WeightType = T;
    using Edge = Edge<WeightType, PointType>;
    using EdgeContainer = std::vector<Edge>;
    using Graph = ForwardStarGraph<WeightType, PointType>;
    // todo: 确定节点数与边数的关系
    Tree(SizeType vertex_size, SizeType edge_size): Graph(vertex_size, edge_size) {}
    Tree(PointType start, SizeType vertex_size, SizeType edge_size): Graph(start, vertex_size, edge_size) {}
    std::vector<int> getSubtreeSize(PointType root, PointType father) const {
        std::vector<int> subtree_size(this->m_vertex_size, 1);
        auto dfs = [&](auto&& self, PointType u, PointType f) -> void {
            auto ui = this->getIndex(u);
            for (auto&& [_, v, w] : this->m_head[ui]) {
                if (v != f) {
                    self(self, v, u);
                    subtree_size[ui] += subtree_size[this->getIndex(v)];
                }
            }
        };
        dfs(dfs, root, father);
        return subtree_size;
    }
};
} // namespace OI::Graph
