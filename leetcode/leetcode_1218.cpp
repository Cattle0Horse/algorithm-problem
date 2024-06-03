/**
 * @file leetcode_1218.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/longest-arithmetic-subsequence-of-given-difference/description/
 * @version 0.1
 * @date 2024-05-31
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <iostream>
[[maybe_unused]] auto _ = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();
class Solution {
public:
    int longestSubsequence(std::vector<int>& arr, int difference) {
        int ans = 1;
        std::unordered_map<int, int> dp;
        for (int num : arr) {
            // num可以接在num-difference后
            ans = std::max(ans, dp[num] = dp[num - difference] + 1);
        }
        return ans;
    }
};