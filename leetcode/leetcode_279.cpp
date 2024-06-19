/**
 * @file leetcode_279.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/perfect-squares/description/
 * @version 0.1
 * @date 2024-06-17
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <algorithm>
#include <cstring>
#include <iostream>
#include <limits>
#include <vector>

class Solution {
public:
    int numSquares(int n) {
        std::vector<int> dp(n + 1);
        for (int i{1}; i <= n; ++i) {
            dp[i] = std::numeric_limits<int>::max();
            for (int j{1}; j * j <= i; ++j) {
                dp[i] = std::min(dp[i], dp[i - j * j] + 1);
            }
        }
        return dp.back();
    }
};