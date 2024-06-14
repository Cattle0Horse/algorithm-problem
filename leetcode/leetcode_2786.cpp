/**
 * @file leetcode_2786.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/visit-array-positions-to-maximize-score/description/?envType=daily-question&envId=2024-06-14
 * @version 0.1
 * @date 2024-06-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
#include <array>
#include <vector>
class Solution {
public:
    long long maxScore(std::vector<int>& nums, int x) {
        int n = nums.size();
        // dp 表示在[0,i]中对应奇偶性结尾的最大得分
        std::array<long long, 2> dp;
        dp[nums[0] & 1] = nums[0];
        dp[(nums[0] & 1) ^ 1] = -(1 << 20);
        for (int i{1}; i < n; ++i) {
            int same = nums[i] & 1;
            dp[same] = std::max(dp[same] + nums[i], dp[same ^ 1] - x + nums[i]);
        }
        return std::max(dp[0], dp[1]);
    }
};