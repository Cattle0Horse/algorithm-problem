/**
 * @file leetcode_1493.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/longest-subarray-of-1s-after-deleting-one-element/?envType=problem-list-v2&envId=CpHNyXsu
 * @version 0.1
 * @date 2024-07-07
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

[[maybe_unused]] auto __init_io__ = []() {
    return std::cin.tie(nullptr)->sync_with_stdio(false);
}();

class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int n = nums.size(), ans = 0, pre_zero_index = nums[0] == 0 ? 0 : -1;
        // 以nums[i]结尾
        std::vector<int> dp(n);
        dp[0] = nums[0] == 1;
        for (auto i{1}; i < n; ++i) {
            if (nums[i] == 0) {
                pre_zero_index = i;
                // 删
                ans = std::max(ans, dp[i - 1]);
                dp[i] = 0;
            } else {
                dp[i] = dp[i - 1] + 1;
                if (pre_zero_index == -1) {
                    ans = std::max(ans, dp[i] - 1);
                } else {
                    ans = std::max(ans, dp[i] + (pre_zero_index - 1 < 0 ? 0 : dp[pre_zero_index - 1]));
                }
            }
        }
        return ans;
    }
};

int main() {
    std::vector<int> nums{0, 1, 1, 1, 1, 1};
    Solution().longestSubarray(nums);
}