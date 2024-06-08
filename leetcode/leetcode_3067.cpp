/**
 * @file leetcode_3067.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/count-pairs-of-connectable-servers-in-a-weighted-tree-network/?envType=daily-question&envId=2024-06-04
 * @version 0.1
 * @date 2024-06-04
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <functional>
#include <utility>
#include <vector>
class Solution {
public:
    std::vector<int> countPairsOfConnectableServers(std::vector<std::vector<int>>& edges, int signalSpeed) {
        int n = edges.size() + 1;
        std::vector<std::vector<std::pair<int, int>>> adj(n);
        for (auto&& edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
        }
        std::function<int(int, int, int)> dfs = [&](int u, int fa, int sum) {
            int cnt = sum % signalSpeed == 0;
            for (auto&& [v, w] : adj[u]) {
                if (v == fa) continue;
                cnt += dfs(v, u, sum + w);
            }
            return cnt;
        };
        std::vector<int> ans(n);
        for (int u{0}; u < n; ++u) {
            // 只算当前节点之前的, 去重
            int sum = 0;
            for (auto&& [v, w] : adj[u]) {
                int cnt = dfs(v, u, w);
                ans[u] += sum * cnt;
                sum += cnt;
            }
        }
        return ans;
    }
};