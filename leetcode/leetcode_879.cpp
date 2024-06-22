/**
 * @file leetcode_879.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/profitable-schemes/description/
 * @version 0.1
 * @date 2024-06-22
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

[[maybe_unused]] auto _ = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();
constexpr int MOD = 1e9 + 7;
class Solution {
public:
    // 二维费用01背包
    // dp[i][j][x] : [0,i] 用不超过 j 个人 获得大于等于 x 利润 的方案数
    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(minProfit + 1, 0));
        for (auto i{0}; i <= n; ++i) dp[i][0] = 1;

        int m = group.size();
        for (auto i{0}; i < m; ++i) {
            int g = group[i], p = profit[i];
            for (auto j{n}; j >= g; --j) {
                for (auto x{minProfit}; x >= 0; --x) {
                    dp[j][x] += dp[j - g][std::max(0, x - p)];
                    dp[j][x] %= MOD;
                }
            }
        }
        return dp[n][minProfit];
    }
};