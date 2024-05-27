/**
 * @file leetcode_2028.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/find-missing-observations/?envType=daily-question&envId=2024-05-27
 * @version 0.1
 * @date 2024-05-27
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <numeric>
#include <vector>
class Solution {
public:
    std::vector<int> missingRolls(std::vector<int>& rolls, int mean, int n) {
        int sum = std::accumulate(rolls.begin(), rolls.end(), 0);
        int rest = mean * (n + rolls.size()) - sum;
        if (rest < n || rest > 6 * n) {
            return {};
        }
        std::vector<int> ans(n, 1);
        rest -= n;
        int index = 0;
        while (rest >= 5) {
            ans[index++] += 5;
            rest -= 5;
        }
        if (rest > 0) {
            ans[index] += rest;
        }
        return ans;
    }
};