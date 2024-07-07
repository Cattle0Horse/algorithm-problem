/**
 * @file leetcode_2294.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/partition-array-such-that-maximum-difference-is-k/description/
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
    // 贪心, 从左向右添加数字, 直到不能添加为止
    int partitionArray(vector<int>& nums, int k) {
        std::ranges::sort(nums);
        int n = nums.size(), ans{0};
        for (int l{0}, r{l}; l < n; l = r) {
            int mx = nums[l];
            while (r < n && (mx = std::max(mx, nums[r])) - nums[l] <= k) {
                ++r;
            }
            ans += 1;
        }
        return ans;
    }
};