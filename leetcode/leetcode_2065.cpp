/**
 * @file leetcode_2065.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/maximum-path-quality-of-a-graph/description/?envType=daily-question&envId=2024-07-01
 * @version 0.1
 * @date 2024-07-01
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifdef OY_LOCAL
#include <vector>
#include <iostream>
using namespace std;
#endif

[[maybe_unused]] auto __init_io__ = []() {
    return std::cin.tie(nullptr)->sync_with_stdio(false);
}();

template<typename T = int>
struct Edge {
    size_t to;
    T weight;
    int next;
};
template<typename T = int>
struct Graph {
    constexpr static int NONE = -1;
    vector<Edge<T>> edges;
    vector<int> head;
    Graph(size_t node_size, size_t edge_size = 0): head(node_size, NONE) {
        edges.reserve(edge_size);
    }
    void addEdge(size_t from, size_t to, T w = T()) {
        edges.emplace_back(to, w, head[from]);
        head[from] = edges.size() - 1;
    }
    void addEdge2(size_t from, size_t to, T w = T()) {
        addEdge(from, to, w);
        addEdge(to, from, w);
    }
    auto start(size_t u) {
        return head[u];
    }
    auto next(int i) {
        return edges[i].next;
    }
    // 遍历节点 u 的所有邻接边
    template<typename Func_Type>
    void traverse(size_t u, Func_Type func) {
        for (auto it = head[u]; it != NONE; it = edges[it].next) {
            func(edges[it]);
        }
        // for (auto it = start(u); it != NONE; it = next(it)) {
        //     func(edges[it]);
        // }
    }
};

class Solution {
public:
    // 图可能存在环, 因此不能边权*2求解
    // maxTime最大为100, time最少为10, 因此, 递归深度最大为10
    // 进入下一个点前可以判断其与0的最短距离, 如果大于剩余时间则跳过, 求解最短路径可以用dijkstra
    int maximalPathQuality(vector<int>& values, vector<vector<int>>& edges, int maxTime) {
        int n = values.size();
        Graph<int> g(n, edges.size());
        for (auto&& edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            g.addEdge2(u, v, w);
        }
        std::vector<bool> vis(n);
        auto dfs = [&](auto&& self, int u, int sum, int time) -> int {
            int ans = 0;
            if (u == 0) ans = sum;
            for (auto it = g.start(u); it != g.NONE; it = g.next(it)) {
                const auto& edge{g.edges[it]};
                int v = edge.to, cost = edge.weight;
                int rest_time = time - cost;
                if (rest_time < 0) continue;
                if (vis[v]) {
                    ans = std::max(ans, self(self, v, sum, rest_time));
                } else {
                    vis[v] = true;
                    ans = std::max(ans, self(self, v, sum + values[v], rest_time));
                    vis[v] = false;
                }
                // bool original = vis[v];
                // if (!original) vis[v] = true;
                // ans = std::max(ans, self(self, v, sum + (original ? 0 : values[v]), rest_time));
                // if (!original) vis[v] = false;
            }
            return ans;
        };
        vis[0] = true;
        return dfs(dfs, 0, values[0], maxTime);
    }
};