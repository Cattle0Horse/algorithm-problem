/**
 * @file leetcode_416.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/partition-equal-subset-sum/description/
 * @version 0.1
 * @date 2024-06-05
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <numeric>
#include <vector>
class Solution {
public:
    bool canPartition(std::vector<int>& nums) {
        int n = nums.size();
        if (n == 1 && nums.front() != 0) {
            return false;
        }
        int sum = std::accumulate(nums.begin(), nums.end(), 0);
        if (sum & 1) return false;
        // 选出一个子序列, 是否值为sum/2;
        int target = sum >> 1;
        std::vector<int> dp(target + 1, false);
        dp[0] = true;
        for (int num : nums) {
            for (int x = target; x >= num; --x) {
                dp[x] |= dp[x - num];
            }
        }
        return dp[target];
    }
};