/**
 * @file leetcode_931.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/minimum-falling-path-sum/description/
 * @version 0.1
 * @date 2024-06-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
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
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();
        std::vector<int> dp(n);
        dp = matrix[0];
        for (int i{1}; i < n; ++i) {
            auto pre{dp};
            for (int j{0}; j < n; ++j) {
                dp[j] = pre[j] + matrix[i][j];
                if (j - 1 >= 0) dp[j] = std::min(dp[j], pre[j - 1] + matrix[i][j]);
                if (j + 1 < n) dp[j] = std::min(dp[j], pre[j + 1] + matrix[i][j]);
            }
        }
        return *std::min_element(dp.begin(), dp.end());
    }
};