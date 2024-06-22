/**
 * @file leetcode_2915.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/length-of-the-longest-subsequence-that-sums-to-target/
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

class Solution {
public:
    int lengthOfLongestSubsequence(vector<int>& nums, int target) {
        // dp[i][x]: [0, i]物品构成x的最大长度
        // int n = nums.size();
        // std::vector<std::vector<int>> dp(n, std::vector<int>(target + 1, -1));
        // dp[0][0] = 0;
        // if (nums[0] <= target) dp[0][nums[0]] = 1;
        // for (auto i{1}; i < n; ++i) {
        //     int num = nums[i];
        //     for (auto x{0}; x <= target; ++x) {
        //         dp[i][x] = dp[i - 1][x];
        //         if (x >= num && dp[i - 1][x - num] != -1) {
        //             dp[i][x] = std::max(dp[i][x], dp[i - 1][x - num] + 1);
        //         }
        //     }
        // }
        // return dp[n - 1][target];

        std::vector<int> dp(target + 1, -1);
        dp[0] = 0;
        for (int num : nums) {
            for (int x = target; x >= num; --x) {
                if (dp[x - num] != -1) {
                    dp[x] = std::max(dp[x], dp[x - num] + 1);
                }
            }
        }
        return dp[target];
    }
};