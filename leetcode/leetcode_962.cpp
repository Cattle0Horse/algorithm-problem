/**
 * @file leetcode_962.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/maximum-width-ramp/
 * @version 0.1
 * @date 2024-04-23
 *
 * @copyright Copyright (c) 2024
 *
 * 题意：对每一个元素找它的最后一个更大元素，返回它们之间的下标差
 *
 *
 * trick1: 所维护的栈的单调性是结果，而不是原因，根本是为了跳过没有价值的元素
 * trick2: 使用vector表示栈 可以 在栈上实现二分
 */

#include <bits/stdc++.h>
using namespace std;

/*
            .                       .
        .       .               .
    .               .       .
.                       .
*/
class Solution {
public:
    // 正序遍历无法 确定 当前元素是否是栈中元素的answer
    // 逆序遍历，每遍历一个数，它后面比它小的数也有可能成为answer

    // 换种思路思考：
    // 左边的元素越小且越靠左越好，而在它右边且比它大的 对answer已经没有价值了
    // 同理，右边的元素越大且越靠右越好
    // 跳过这些没有价值的元素

    // Solution1:
    // 单调栈上二分
    // 时间复杂度瓶颈取决于上升序列的个数（对应调用二分查找的次数）
    /*
    int maxWidthRamp(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        vector<int> s;
        for (int i{0}; i < n; ++i) {
            if (s.empty() || nums[s.back()] > nums[i]) {
                s.push_back(i);
            } else {
                // 此时在栈中找到一个距离当前位置最靠左的更小元素
                // 而这个栈是单调递减的，可以用二分查找优化
                // 这个分支保证了至少有一个的更小元素
                // (-1, l] 均为大于nums[i]
                int l = -1, r = s.size();
                while (l + 1 < r) {
                    int mid = (l + r) >> 1;
                    if (nums[s[mid]] > nums[i]) {
                        l = mid;
                    } else {
                        r = mid;
                    }
                }
                ans = max(ans, i - s[r]);
            }
        }
        return ans;
    }
    */

    // Solution2:
    // 额外的一次逆序遍历，确定对于当前遍历到的元素所对应的最宽的坡
    // 时间复杂度：O(n)
    int maxWidthRamp(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        vector<int> s;
        for (int i{0}; i < n; ++i) {
            if (s.empty() || nums[s.back()] > nums[i]) {
                s.push_back(i);
            }
        }
        for (int i = n - 1; i >= 0 && !s.empty(); --i) {
            while (!s.empty() && nums[s.back()] <= nums[i]) {
                ans = max(ans, i - s.back());
                s.pop_back();
            }
        }
        return ans;
    }
};

int main() {
    vector<int> nums{9, 8, 1, 0, 1, 9, 4, 0, 4, 1};
    std::cout << Solution().maxWidthRamp(nums);
}