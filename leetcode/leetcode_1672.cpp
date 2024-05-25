/**
 * @file leetcode_1672.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/richest-customer-wealth/
 * @version 0.1
 * @date 2024-05-24
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
#include <numeric>
#include <vector>

class Solution {
public:
    int maximumWealth(std::vector<std::vector<int>>& accounts) {
        int ans = 0;
        for (auto&& assets : accounts) {
            ans = std::max(ans, std::accumulate(assets.begin(), assets.end(), 0));
        }
        return ans;
    }
};