/**
 * @file leetcode_53.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/maximum-subarray/description/
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
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        // dp[i] : 以nums[i]结尾的最大子数组和;
        // std::vector<int> dp(n);
        // dp[0]= nums[0];
        // 只用到前一个
        int pre = nums[0], ans = pre;
        for (int i{1}; i < n; ++i) {
            pre = std::max(pre + nums[i], nums[i]);
            ans = std::max(ans, pre);
        }
        return ans;
    }
};