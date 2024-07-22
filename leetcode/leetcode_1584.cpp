/**
 * @file leetcode_1584.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/min-cost-to-connect-all-points/
 * @version 0.1
 * @date 2024-07-22
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

[[maybe_unused]] int __init_io__ = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cout << std::fixed << std::setprecision(20);
    return 0;
}();

/**
 * @file forward_star_graph.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief 链式前向星存图(一维静态链表)
 * @version 0.5
 * @date 2024-07-13
 * @lastmodify 2024-07-22
 * @copyright Copyright (c) 2024
 *
 */
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
            mutable ForwardStarGraph<WeightType>* m_graph;
            int val;
            EdgeIterator(ForwardStarGraph* graph, int edge_index): m_graph(graph), val(edge_index) {}
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
        EdgeRange(ForwardStarGraph<WeightType>* graph): m_begin(graph, END_INDEX), m_end(graph->END_ITERATOR) {}
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
} // namespace OI::Graph

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

class Solution {
public:
    int dis(int x1, int y1, int x2, int y2) {
        return abs(x1 - x2) + abs(y1 - y2);
    }
    int minCostConnectPoints(vector<vector<int>>& points) {
        using Graph = OI::Graph::ForwardStarGraph<int>;
        int n = points.size();
        Graph g(n, n * (n - 1));
        for (auto i{0}; i < n; i += 1) {
            for (auto j{0}; j < n; j += 1) {
                if (i != j) {
                    g.addEdge(i, j, dis(points[i][0], points[i][1], points[j][0], points[j][1]));
                }
            }
        }
        int sum = 0;
        auto op = [&](const Graph::Edge& edge) -> void {
            sum += edge.weight;
        };
        g.minSpanTree(OI::Graph::Kruskal<Graph>(), op);
        return sum;
    }
};

#ifdef Cattle_Horse
int main() {
    //
}
#endif