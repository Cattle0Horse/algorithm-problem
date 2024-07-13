/**
 * @file leetcode_802.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/find-eventual-safe-states/description/
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

class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& adj) {
        //(0, 1, 2) = (未访问, 已访问, 安全)
        constexpr static int NO_VIS = 0, VIS = 1, SAFE = 2;
        int n = adj.size();
        std::vector<int> color(n, NO_VIS);
        auto dfs = [&](auto&& self, int u) -> bool {
            if (color[u] > 0) return color[u] == SAFE;
            color[u] = VIS;
            for (int v : adj[u]) {
                if (!self(self, v)) {
                    return false;
                }
            }
            color[u] = SAFE;
            return true;
        };

        std::vector<int> ans;
        for (auto i{0}; i < n; i += 1) {
            if (dfs(dfs, i)) ans.push_back(i);
        }
        return ans;
    }
    // vector<int> eventualSafeNodes(vector<vector<int>>& adj) {
    //     int n = adj.size();
    //     std::vector<int> safe(n);
    //     for (auto i{0}; i < n; i += 1) {
    //         safe[i] = adj[i].empty() ? 1 : 0;
    //     }

    //     std::vector<bool> vis(n);
    //     auto dfs = [&](auto&& self, int u) -> bool {
    //         if (safe[u] != 0) return safe[u] == 1;
    //         for (int v : adj[u]) {
    //             if (vis[v]) return false;
    //             vis[v] = true;
    //             if (!self(self, v)) {
    //                 vis[v] = false;
    //                 safe[u] = -1;
    //                 return false;
    //             }
    //             vis[v] = false;
    //         }
    //         return safe[u] = 1;
    //     };

    //     std::vector<int> ans;
    //     for (auto i{0}; i < n; i += 1) {
    //         vis[i] = true;
    //         if (dfs(dfs, i)) ans.push_back(i);
    //         vis[i] = false;
    //     }
    //     return ans;
    // }
};