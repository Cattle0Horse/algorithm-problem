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

class Solution2 {
public:
    constexpr static int INF = std::numeric_limits<int>::max();
    // 完全背包
    int numSquares(int n) {
        std::vector<int> dp(n + 1, INF);
        dp[0] = 0;
        for (int i = 1; i * i <= n; ++i) {
            int num = i * i;
            for (auto x{num}; x <= n; ++x) {
                if (dp[x - num] != INF) {
                    dp[x] = std::min(dp[x], dp[x - num] + 1);
                }
            }
        }
        return dp[n];
    }
};

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