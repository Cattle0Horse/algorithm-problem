/**
 * @file leetcode_3179.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/find-the-n-th-value-after-k-seconds/description/
 * @version 0.1
 * @date 2024-06-16
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <vector>
class Solution {
public:
    int valueAfterKSeconds(int n, int k) {
        constexpr int mod = 1e9 + 7;
        std::vector<int> preSum(n, 1);
        for (int i = 1; i <= k; ++i) {
            for (int j = 1; j < n; ++j) {
                preSum[j] += preSum[j - 1];
                preSum[j] %= mod;
            }
        }
        return preSum[n - 1];
    }
};