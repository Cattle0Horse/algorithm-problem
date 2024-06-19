/**
 * @file leetcode_63.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/unique-paths-ii/description/
 * @version 0.1
 * @date 2024-06-16
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifdef OY_LOCAL
#include <vector>
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
    int uniquePathsWithObstacles(vector<vector<int>>& grid) {
        if (grid[0][0] == 1) return 0;
        int n = grid.size(), m = grid.front().size();
        std::vector<std::vector<int>> dp(n, std::vector<int>(m, 0));
        dp[0][0] = 1;
        for (int i{0}; i < n; ++i) {
            for (int j{0}; j < m; ++j) {
                if (grid[i][j] == 1) continue;
                if (j - 1 >= 0) dp[i][j] += dp[i][j - 1];
                if (i - 1 >= 0) dp[i][j] += dp[i - 1][j];
            }
        }
        return dp.back().back();
    }
};