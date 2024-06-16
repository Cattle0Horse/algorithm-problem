/**
 * @file leetcode_3180.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/maximum-total-reward-using-operations-i/description/
 * @version 0.1
 * @date 2024-06-16
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
#include <set>
#include <vector>

#include <algorithm>
#include <vector>

class Solution {
public:
    int maxTotalReward(std::vector<int>& rewardValues) {
        std::sort(rewardValues.begin(), rewardValues.end());
        rewardValues.resize(std::unique(rewardValues.begin(), rewardValues.end()) - rewardValues.begin());
        int n = rewardValues.size(), ans = rewardValues.front();
        std::set<int> dp;
        dp.insert(rewardValues.front());
        dp.insert(0);
        for (int i{1}; i < n; ++i) {
            int num = rewardValues[i];
            auto it = dp.begin();
            for (; it != dp.end() && *it < num; ++it) {
                dp.insert((*it) + num);
                ans = std::max(ans, (*it) + num);
            }
        }
        return ans;
    }
};