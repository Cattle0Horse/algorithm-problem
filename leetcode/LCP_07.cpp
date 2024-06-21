/**
 * @file LCP_07.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/chuan-di-xin-xi/
 * @version 0.1
 * @date 2024-06-21
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <functional>
#include <queue>
#ifdef OY_LOCAL
#include <vector>
#include <string>
#include <iostream>
using namespace std;
#endif

[[maybe_unused]] auto _ = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();
class Solution {
public:
    int numWays(int n, vector<vector<int>>& relation, int k) {
        std::vector<std::vector<int>> adj(n);
        for (auto&& r : relation) {
            int a{r[0]}, b{r[1]};
            adj[a].push_back(b);
        }
        std::queue<int> q;
        q.push(0);
        int cnt = -1;
        while (!q.empty()) {
            int sz = q.size();
            int ans = 0;
            for (int i{0}; i < sz; ++i) {
                int u = q.front();
                q.pop();
                if (u == n - 1) ++ans;
                for (int v : adj[u]) {
                    q.push(v);
                }
            }
            if (++cnt == k) return ans;
        }
        return 0;
    }
};
class Solution2 {
public:
    int numWays(int n, vector<vector<int>>& relation, int k) {
        // dp[i][j] : 第i轮从0到达j的方案数
        std::vector<std::vector<int>> dp(k + 1, std::vector<int>(n, 0));
        dp[0][0] = 1;
        for (int i{1}; i <= k; ++i) {
            for (auto&& edge : relation) {
                int u{edge[0]}, v{edge[1]};
                dp[i][v] += dp[i - 1][u];
            }
        }
        return dp[k][n - 1];
    }
};