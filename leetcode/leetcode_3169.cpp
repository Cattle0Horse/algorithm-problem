/**
 * @file leetcode_3169.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/count-days-without-meetings/description/
 * @version 0.1
 * @date 2024-06-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <algorithm>
#include <functional>
#include <vector>
class Solution {
public:
    int countDays(int days, std::vector<std::vector<int>>& meetings) {
        std::function<void(std::vector<std::vector<int>>&)> mergeRange{[](std::vector<std::vector<int>>& intervals) {
            std::sort(intervals.begin(), intervals.end());
            int index{0};
            for (int i{0}, n{static_cast<int>(intervals.size())}; i < n;) {
                intervals[index][0] = intervals[i][0];
                int right{intervals[i][1]};
                // i 走到第一个不能合并的区间
                for (; i < n && intervals[i][0] <= right; ++i) {
                    right = std::max(right, intervals[i][1]);
                }
                intervals[index][1] = right;
                ++index;
            }
            intervals.resize(index);
        }};
        mergeRange(meetings);
        for (auto&& meeting : meetings) {
            days -= meeting[1] - meeting[0] + 1;
        }
        return days;
    }
};