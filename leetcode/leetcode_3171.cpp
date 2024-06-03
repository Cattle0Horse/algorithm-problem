/**
 * @file leetcode_3171.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/find-subarray-with-bitwise-and-closest-to-k/description/
 * @version 0.1
 * @date 2024-06-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <algorithm>
#include <cstdlib>
#include <limits>
#include <vector>
class Solution {
public:
    int minimumDifference(std::vector<int>& nums, int k) {
        int ans = std::numeric_limits<int>::max();
        int n = nums.size();
        for (int i{0}; i < n; ++i) {
            // 此时 nums[j] 为 [j, i] 的区间&
            // 如果 nums[j] 是 nums[i] 的子集, 则nums[0... j-1]也是nums[i]的子集, 无需继续遍历
            int num = nums[i];
            for (int j = i - 1; j >= 0 && (nums[j] | num) != num; --j) {
                nums[j] &= num;
                ans = std::min(ans, std::abs(k - nums[j]));
            }
            ans = std::min(ans, std::abs(k - num));
        }
        return ans;
    }
};