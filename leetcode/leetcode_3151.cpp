/**
 * @file leetcode_3151.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/special-array-i/
 * @version 0.1
 * @date 2024-05-20
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <algorithm>
#include <vector>
class Solution {
public:
    bool isArraySpecial(std::vector<int>& nums) {
        return std::adjacent_find(nums.begin(), nums.end(),
                                  [&](int a, int b) { return a % 2 == b % 2; }
                                  ) == nums.end();
    }
};