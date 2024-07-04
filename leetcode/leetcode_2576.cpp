/**
 * @file leetcode_2576.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/find-the-maximum-number-of-marked-indices/
 * @version 0.1
 * @date 2024-07-03
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
#include <functional>
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
    // bug: 这可能会出现小的和小的那部分相匹配而导致没有全部匹配成功(原本可以是两个小的和两个大的匹配), 逆序同理
    // int maxNumOfMarkedIndices(vector<int>& nums) {
    //     int n = nums.size();
    //     std::ranges::sort(nums, std::greater<>());
    //     std::vector<bool> used(n, false);
    //     // 对每一个j找到与之相匹配的i
    //     for (auto j{0}, i{0}; j < n; ++j) {
    //         if (used[j]) continue;
    //         while (i < n && (used[i] || nums[j] < 2 * nums[i])) ++i;
    //         if (i < n) used[j] = used[i] = true;
    //     }
    //     for (auto&& b : used) {
    //         cout << b << ' ';
    //     }
    //     return std::ranges::count(used, true);
    // }

    // note: 应该是左半部分与右半部分匹配???为什么
    // 从小到大排序后，如果存在 k 对匹配，那么一定可以让最小的 k 个数和最大的 k 个数匹配。
    int maxNumOfMarkedIndices(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int i = 0, n = nums.size();
        for (int j = (n + 1) / 2; j < n; ++j)
            if (nums[i] * 2 <= nums[j])
                ++i;
        return i * 2;
    }
};