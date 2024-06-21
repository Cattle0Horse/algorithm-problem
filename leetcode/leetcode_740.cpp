/**
 * @file leetcode_740.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/delete-and-earn/description/
 * @version 0.1
 * @date 2024-06-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
#include <array>
#ifdef OY_LOCAL
#include <vector>
#include <string>
#include <iostream>
using namespace std;
#endif

[[maybe_unused]] auto _ = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();

constexpr int N = 1e4;

class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        std::array<int, N + 1> dp, cnt;
        dp.fill(0);
        cnt.fill(0);
        for (int num : nums) {
            ++cnt[num];
        }
        dp[1] = 1 * cnt[1];
        for (int i{2}; i <= N; ++i) {
            dp[i] = std::max(dp[i - 1], dp[i - 2] + i * cnt[i]);
        }
        return dp[N];
    }
};