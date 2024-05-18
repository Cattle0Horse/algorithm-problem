/**
 * @file leetcode_2644.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/find-the-maximum-divisibility-score/description/?envType=daily-question&envId=2024-05-18
 * @version 0.1
 * @date 2024-05-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
#include <vector>
class Solution {
public:
    int maxDivScore(std::vector<int>& nums, std::vector<int>& divisors) {
        int ansVal = -1, ansCnt = -1;
        for (int divisor : divisors) {
            int cnt = std::count_if(nums.begin(), nums.end(), [&](int num) {
                return num % divisor == 0;
            });
            if (cnt > ansCnt || (cnt == ansCnt && divisor < ansVal)) {
                ansVal = divisor;
                ansCnt = cnt;
            }
        }
        return ansVal;
    }
};