/**
 * @file leetcode_1827.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief
 * @version 0.1
 * @date 2024-07-04
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifdef OY_LOCAL
#include <vector>
#include <iostream>
using namespace std;
#endif

[[maybe_unused]] auto __init_io__ = []() {
    return std::cin.tie(nullptr)->sync_with_stdio(false);
}();

class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size(), pre = nums[0];
        int ans = 0;
        for (auto i{1}; i < n; ++i) {
            if (nums[i] <= pre) {
                ans += pre + 1 - nums[i];
                pre = pre + 1;
            } else {
                pre = nums[i];
            }
        }
        return ans;
    }
};