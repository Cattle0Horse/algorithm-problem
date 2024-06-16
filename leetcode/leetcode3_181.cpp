/**
 * @file leetcode3_181.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/maximum-total-reward-using-operations-ii/description/
 * @version 0.1
 * @date 2024-06-16
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <algorithm>
#include <bitset>
#include <vector>
#include <algorithm>
#include <vector>

class Solution {
public:
    int maxTotalReward(std::vector<int>& rewardValues) {
        std::sort(rewardValues.begin(), rewardValues.end());
        rewardValues.resize(std::unique(rewardValues.begin(), rewardValues.end()) - rewardValues.begin());
        int n = rewardValues.size();
        constexpr static int N = 1e5;
        std::bitset<N + 1> set;
        set.set(0);
        for (int v : rewardValues) {
            // 截取低v-1位
            // 也就是高N-v+1位置0
            int k = N - v + 1;
            set |= (set << k >> k) << v;
        }
        for (int i = N; i >= 0; --i)
            if (set.test(i)) return i;
        return -1;
    }
};