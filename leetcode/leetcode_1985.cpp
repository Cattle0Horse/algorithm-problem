/**
 * @file leetcode_1985.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/find-the-kth-largest-integer-in-the-array/
 * @version 0.1
 * @date 2024-07-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <string>
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
    string kthLargestNumber(vector<string>& nums, int k) {
        k = nums.size() - k;
        std::nth_element(nums.begin(), nums.begin() + k, nums.end(), [](const std::string& a, const std::string& b) {
            if (a.length() != b.length()) return a.length() < b.length();
            return a < b;
        });
        return nums[k];
    }
};