/**
 * @file leetcode_494.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/target-sum/description/
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
    int findTargetSumWays(std::vector<int>& nums, int target) {
        // x 表示加号的数字和
        // 那么对应情况下加-号的数字的和为 sum-x
        // 则表达式的值为 x-(sum-x) = target
        // 即找到 2x = target + sum
        target += std::accumulate(nums.begin(), nums.end(), 0);
        if (target < 0 || target % 2) return 0;
        target >>= 1;
        // 寻找能构成target的子序列的个数;
        int n = nums.size();
        std::vector<int> dp(target);
        dp[0] = 1;
        for (int num : nums) {
            for (int x = target; x >= num; --x) {
                dp[x] += dp[x - num];
            }
        }
        return dp[target];
    }
};

/**
 * @file leetcode_494.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/target-sum/description/
 * @version 0.1
 * @date 2024-06-05
 *
 * @copyright Copyright (c) 2024
 *
 */

// #include <algorithm>
// #include <bit>
// #include <numeric>
// #include <vector>
// class Solution {
// public:
//     int findTargetSumWays(std::vector<int>& nums, int target) {
//         int n = nums.size();
//         int sum = std::accumulate(nums.begin(), nums.end(), 0);
//         int S = 1 << n;
//         // dp[s]表示s二进制位为1的数的和(加+号)
//         // 那么对应情况下加-号的数字的和为 sum-dp[s]
//         // 则表达式的值为 dp[s]+(-(sum-dp[s]))
//         std::vector<int> dp(S);
//         dp[0] = 0;
//         for (uint32_t s{1u}; s < S; ++s) {
//             dp[s] = dp[s & (s - 1)] + nums[std::countr_zero(s)];
//         }
//         return std::count_if(dp.begin(), dp.end(), [&](int x) {
//             return x - (sum - x) == target;
//         });
//     }
// };