/**
 * @file LCP_166.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/li-wu-de-zui-da-jie-zhi-lcof/
 * @version 0.1
 * @date 2024-06-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifdef OY_LOCAL
#include <algorithm>
#include <numeric>
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
    int jewelleryValue(vector<vector<int>>& frame) {
        int n = frame.size(), m = frame[0].size();
        std::vector<std::vector<int>> dp(n, std::vector<int>(m, 0));
        std::partial_sum(frame[0].begin(), frame[0].end(), dp[0].begin());
        for (auto i{1}; i < n; ++i) {
            dp[i][0] = frame[i][0] + dp[i - 1][0];
        }
        for (auto i{1}; i < n; ++i) {
            for (auto j{1}; j < m; ++j) {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]) + frame[i][j];
            }
        }
        return dp[n - 1][m - 1];
    }
};