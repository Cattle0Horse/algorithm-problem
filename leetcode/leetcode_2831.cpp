/**
 * @file leetcode_2831.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/find-the-longest-equal-subarray/?envType=daily-question&envId=2024-05-23
 * @version 0.1
 * @date 2024-05-23
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <algorithm>
#include <deque>
#include <unordered_map>
#include <vector>
class Solution {
public:
    int longestEqualSubarray(std::vector<int>& nums, int k) {
        int ans = 0, n = nums.size();
        std::unordered_map<int, std::deque<int>> positions;
        for (int i{0}, j{0}; i < n; ++i) {
            int num = nums[i];
            auto& pos = positions[num];
            if (!pos.empty() && pos.front() == i) {
                pos.pop_front();
            }
            if (i == j) {
                ++j;
            }
            // (i,j]
            while (j < n && (nums[j] == num || (j - i - pos.size() <= k))) {
                positions[nums[j]].push_back(j);
                ++j;
            }
            ans = std::max(ans, static_cast<int>(pos.size()) + 1);
        }
        return ans;
    }
};