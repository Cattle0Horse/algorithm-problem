/**
 * @file leetcode_2410.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/maximum-matching-of-players-with-trainers/description/
 * @version 0.1
 * @date 2024-07-03
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <algorithm>
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
        // 有向边边数
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
    int matchPlayersAndTrainers(vector<int>& players, vector<int>& trainers) {
        std::ranges::sort(players);
        std::ranges::sort(trainers);
        int i = 0, n = trainers.size();
        int ans = 0;
        for (int v : players) {
            while (i < n && v > trainers[i]) ++i;
            if (i < n) {
                ++ans;
                ++i;
            }
        }
        return ans;
    }
};