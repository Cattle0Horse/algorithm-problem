/**
 * @file leetcode_3082.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/find-the-sum-of-the-power-of-all-subsequences/
 * @version 0.1
 * @date 2024-06-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifdef OY_LOCAL
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;
#endif

[[maybe_unused]] auto _ = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();

constexpr int MOD = 1e9 + 7;

class Solution {
public:
    int sumOfPower(vector<int>& nums, int k) {
        std::vector<long long> dp(k + 1);
        dp[0] = 1;
        long long ans{0};
        for (int num : nums) {
            for (auto x{k}; x >= num; --x) {
                dp[x] = (dp[x] + dp[x - num]) % MOD;
            }
        }
        return dp[k];
    }
};