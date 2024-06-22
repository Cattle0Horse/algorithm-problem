/**
 * @file leetcode_322.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/coin-change/description/
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

constexpr int INF = std::numeric_limits<int>::max();

// 二维情况下:
// 1. 完全背包依赖于前一行和当前行的前面一部分, dp[i][v] = op(dp[i-1][v], dp[i][v - num]+1)
// 2. 01背包依赖于前一行, dp[i][v] = op(dp[i-1][v], dp[i-1][v - num])
// 在优化为一维后 就变成了内层循环顺序问题
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // int n = coins.size();
        // std::vector<std::vector<int>> dp(n, std::vector<int>(amount + 1, INF));
        // dp[0][0] = 0;
        // for (auto x{coins[0]}; x <= amount; ++x) {
        //     if (dp[0][x - coins[0]] != INF) {
        //         dp[0][x] = dp[0][x - coins[0]] + 1;
        //     }
        // }
        // for (auto i{1}; i < n; ++i) {
        //     int coin = coins[i];
        //     for (auto x{0}; x <= amount; ++x) {
        //         if (x < coin) {
        //             dp[i][x] = dp[i - 1][x];
        //         } else {
        //             if (dp[i][x - coin] != INF) {
        //                 dp[i][x] = std::min(dp[i - 1][x], dp[i][x - coin] + 1);
        //             } else {
        //                 dp[i][x] = dp[i - 1][x];
        //             }
        //         }
        //     }
        // }
        // int ans = dp[n - 1][amount];
        // return ans == INF ? -1 : ans;

        std::vector<int> dp(amount + 1, INF);
        dp[0] = 0;
        for (int coin : coins) {
            // for (auto x{0}; x <= amount; ++x) {
            //     if (x < coin) {
            //         dp[x] = dp[x];
            //     } else {
            //         dp[x] = std::min(dp[x], dp[x - coin] + 1);
            //     }
            //
            // }
            for (auto x{coin}; x <= amount; ++x) {
                if (dp[x - coin] != INF) {
                    dp[x] = std::min(dp[x], dp[x - coin] + 1);
                }
            }
        }
        return dp[amount] == INF ? -1 : dp[amount];
    }
};