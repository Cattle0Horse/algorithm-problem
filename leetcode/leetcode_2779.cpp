/**
 * @file leetcode_2779.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/maximum-beauty-of-an-array-after-applying-operation/description/?envType=daily-question&envId=2024-06-15
 * @version 0.1
 * @date 2024-06-15
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
#include <vector>
class Solution {
public:
    // 求的是相等元素的长度, 与顺序无关, 可以排序
    /*
            - -
          -
        -
            - -
          -
        -
    */
    // 滑动窗口求符合条件的最长窗口长度
    int maximumBeauty(std::vector<int>& nums, int k) {
        std::sort(nums.begin(), nums.end());
        int ans{1};
        int n = nums.size();
        for (int l{0}, r{1}; r < n; ++r) {
            // [l, r] all is ...
            while (l < r && nums[r] - k > nums[l] + k) {
                ++l;
            }
            ans = std::max(ans, r - l + 1);
        }
        return ans;
    }
};