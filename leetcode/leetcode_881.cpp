/**
 * @file leetcode_881.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/boats-to-save-people/description/?envType=daily-question&envId=2024-06-10
 * @version 0.1
 * @date 2024-06-10
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
#include <vector>
class Solution {
public:
    // 如果当前轻体重的人, 可以和最重的人组合, 那么这个轻的人可以和其他任意一个人组合
    // 让他尽可能的和重的人组合
    int numRescueBoats(std::vector<int>& people, int limit) {
        std::sort(people.begin(), people.end());
        int l = 0, r = people.size() - 1, ans = 0;
        while (l < r) {
            if (people[l] + people[r] <= limit) {
                ++l;
            }
            --r;
            ++ans;
        }
        return ans + (l == r);
    }
};