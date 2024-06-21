/**
 * @file leetcode_2925.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/contest/weekly-contest-370/problems/maximum-score-after-applying-operations-on-a-tree/description/
 * @version 0.1
 * @date 2024-06-20
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <functional>
#include <numeric>
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
    long long maximumScoreAfterOperations(vector<vector<int>>& edges, vector<int>& values) {
        int n = values.size();
        std::vector<std::vector<int>> g(n);
        for (auto&& edge : edges) {
            int a{edge[0]}, b{edge[1]};
            g[a].push_back(b);
            g[b].push_back(a);
        }
        // 以u为根, 保持子树健康, 失去的最小分数(选择一个点留下)
        std::function<long long(int, int)> dfs = [&](int u, int f) -> long long {
            // 叶子
            if (u != 0 && g[u].size() == 1) {
                return values[u];
            }
            long long ans = 0;
            for (int v : g[u]) {
                if (v == f) continue;
                ans += dfs(v, u);
            }
            return std::min<long long>(ans, values[u]);
        };
        return std::accumulate(values.begin(), values.end(), 0LL) - dfs(0, -1);
    }
};