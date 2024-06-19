/**
 * @file leetcode_2466.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/count-ways-to-build-good-strings/description/
 * @version 0.1
 * @date 2024-06-19
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <numeric>
#include <vector>
class Solution {
private:
    constexpr static int mod = 1e9 + 7;

public:
    int countGoodStrings(int low, int high, int zero, int one) {
        std::vector<int> dp(high + 1);
        dp[0] = 1;
        // dp[i] = dp[i-zero] + dp[i-one]
        auto get = [&](int i, int x) {
            if (i - x >= 0) return dp[i - x];
            return 0;
        };
        int ans = 0;
        for (int i{1}; i <= high; ++i) {
            dp[i] = (get(i, one) + get(i, zero)) % mod;
            if (i >= low) ans = (ans + dp[i]) % mod;
        }
        return ans;
    }
};