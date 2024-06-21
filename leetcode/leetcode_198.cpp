/**
 * @file leetcode_198.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/house-robber/description/
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
    int rob(vector<int>& nums) {
        int n = nums.size();
        std::vector<int> dp(n);
        auto get = [&](int i) {
            return i >= 0 ? dp[i] : 0;
        };
        for (int i{0}; i < n; ++i) {
            dp[i] = std::max(get(i - 1), get(i - 2) + nums[i]);
        }
        return dp[n - 1];
    }
};