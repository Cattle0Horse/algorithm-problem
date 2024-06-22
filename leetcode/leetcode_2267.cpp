/**
 * @file leetcode_2267.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/check-if-there-is-a-valid-parentheses-string-path/
 * @version 0.1
 * @date 2024-06-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bitset>
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

// 100位即可, 最多是100个左括号和100个右括号组合才能使得结果为true
constexpr int N = 100;

class Solution {
public:
    using BS = std::bitset<N + 1>;
    bool hasValidPath(vector<vector<char>>& grid) {
        if (grid[0][0] == ')') return false;
        int n = grid.size(), m = grid[0].size();
        // 路径上左右括号抵消后的左括号个数, 若右括号大于左括号, 则跳过
        std::vector<std::vector<BS>> dp(n, std::vector<BS>(m));
        dp[0][0].set(1);
        for (auto i{1}; i < n; ++i) {
            if (grid[i][0] == ')') {
                dp[i][0] = dp[i - 1][0] >> 1;
            } else {
                dp[i][0] = dp[i - 1][0] << 1;
            }
        }
        for (auto j{1}; j < m; ++j) {
            if (grid[0][j] == ')') {
                dp[0][j] = dp[0][j - 1] >> 1;
            } else {
                dp[0][j] = dp[0][j - 1] << 1;
            }
        }
        for (auto i{1}; i < n; ++i) {
            for (auto j{1}; j < m; ++j) {
                if (grid[i][j] == ')') {
                    dp[i][j] = (dp[i][j - 1] >> 1) | (dp[i - 1][j] >> 1);
                } else {
                    dp[i][j] = (dp[i][j - 1] << 1) | (dp[i - 1][j] << 1);
                }
            }
        }
        return dp[n - 1][m - 1].test(0);
    }
};