/**
 * @file leetcode_851.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/loud-and-rich/description/
 * @version 0.1
 * @date 2024-06-29
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <deque>
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
        edges.emplace_back(to, w, std::exchange(head[from], edges.size()));
        // head[from] = edges.size() - 1;
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
    vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet) {
        int n = quiet.size();
        std::vector<int> degree(n);
        Graph graph(n, richer.size());
        for (auto&& edge : richer) {
            // 有钱的 指向 没钱的
            int big = edge[0], small = edge[1];
            graph.addEdge(big, small);
            ++degree[small];
        }
        std::deque<int> q(n);
        for (auto i{0}; i < n; ++i) {
            if (degree[i] == 0) {
                q.push_back(i);
            }
        }
        std::vector<int> ans(n);
        std::iota(ans.begin(), ans.end(), 0);
        while (!q.empty()) {
            int u = q.back();
            q.pop_back();
            // remove
            degree[u] = -1;
            for (auto it = graph.start(u); it != graph.NONE; it = graph.next(it)) {
                const auto& edge{graph.edges[it]};
                int v = edge.to;
                if (--degree[v] == 0) {
                    q.push_back(v);
                }
                // 如果以u为终点的链上有更安静的，就更新
                if (quiet[ans[v]] > quiet[ans[u]]) {
                    ans[v] = ans[u];
                }
            }
        }
        return ans;
    }
};