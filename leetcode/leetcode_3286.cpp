// @date 2024/9/15 00:32:43
// @author Cattle_Horse (CattleHorse@duck.com)
// @problem 3286. 穿越网格图的安全路径
// @link https://leetcode.cn/classic/problems/find-a-safe-walk-through-a-grid/description/

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
 * @file dijkstra.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief
 * @version 0.5
 * @date 2024-07-13
 * @lastmodify 2024-07-22
 * @copyright Copyright (c) 2024
 *
 */
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

// left, up, right, down
constexpr int DIRECTIONS[4][2]{
    {0, -1},
    {-1, 0},
    {0, 1},
    {1, 0}};

using namespace OI::Graph;
class Solution {
public:
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        int n = grid.size(), m = grid[0].size();
        using Graph = ForwardStarGraph<int>;
        Graph g(n * m, 8 * n * m);

        for (int x = 0; x < n; ++x) {
            for (int y = 0; y < m; ++y) {
                for (auto&& [ox, oy] : DIRECTIONS) {
                    int nx = x + ox, ny = y + oy;
                    if ((0 <= nx && nx < n) && (0 <= ny && ny < m)) {
                        int u = x * m + y, v = nx * m + ny;
                        g.addEdge(u, v, grid[nx][ny]);
                        g.addEdge(v, u, grid[x][y]);
                    }
                }
            }
        }

        auto distances = g.shortestPath(Dijkstra<Graph>(), 0);
        return distances[n * m - 1] + grid[0][0] < health;
    }
};

// bool Solution::findSafeWalk(vector<vector<int>> grid, int health)

#ifdef Cattle_Horse
int main() {
    std::cout << "*** 3286. 穿越网格图的安全路径 ***" << std::endl
              << std::endl;

    Solution s0;

    {
        std::cout << "Test 1: ";

        vector<vector<int>> grid = {{0, 1, 0, 0, 0}, {0, 1, 0, 1, 0}, {0, 0, 0, 1, 0}};
        int health = 1;
        bool ans0 = s0.findSafeWalk(grid, health);
        bool exp0 = true;

        if (ans0 == exp0) {
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
            std::cout << "  Answer: " << ans0 << std::endl;
            std::cout << "  Expect: " << exp0 << std::endl;
        }
    }

    {
        std::cout << "Test 2: ";

        vector<vector<int>> grid = {{0, 1, 1, 0, 0, 0}, {1, 0, 1, 0, 0, 0}, {0, 1, 1, 1, 0, 1}, {0, 0, 1, 0, 1, 0}};
        int health = 3;
        bool ans1 = s0.findSafeWalk(grid, health);
        bool exp1 = false;

        if (ans1 == exp1) {
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
            std::cout << "  Answer: " << ans1 << std::endl;
            std::cout << "  Expect: " << exp1 << std::endl;
        }
    }

    {
        std::cout << "Test 3: ";

        vector<vector<int>> grid = {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}};
        int health = 5;
        bool ans2 = s0.findSafeWalk(grid, health);
        bool exp2 = true;

        if (ans2 == exp2) {
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
            std::cout << "  Answer: " << ans2 << std::endl;
            std::cout << "  Expect: " << exp2 << std::endl;
        }
    }

    {
        std::cout << "Test 4: ";

        vector<vector<int>> grid = {{1, 1, 1, 1}};
        int health = 4;
        bool ans2 = s0.findSafeWalk(grid, health);
        bool exp2 = false;

        if (ans2 == exp2) {
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
            std::cout << "  Answer: " << ans2 << std::endl;
            std::cout << "  Expect: " << exp2 << std::endl;
        }
    }

    return 0;
}
#endif
