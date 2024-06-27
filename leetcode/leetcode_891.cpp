/**
 * @file leetcode_891.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/sum-of-subsequence-widths/description/
 * @version 0.1
 * @date 2024-06-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <array>
#include <cstdint>
#ifdef OY_LOCAL
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;
#endif

constexpr int MOD = 1e9 + 7, N = 1e5;

std::array<int, N + 1> p2 = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::array<int, N + 1> p2;
    p2[0] = 1;
    for (auto i{1}; i <= N; ++i) {
        p2[i] = p2[i - 1] * 2 % MOD;
    }
    return p2;
}();

class Solution {
public:
    // 记录每一个位置作为最大值和最小值的次数
    int sumSubseqWidths(vector<int>& nums) {
        std::ranges::sort(nums);
        int64_t ans{0};
        // 统计nums[i]作为最大值最小值的次数
        // 作为最大值的次数是 i之前数的任意组合, 即2^i
        // 作为最小值的次数是 i之后数的任意组合, 即2^(n-i-1)
        for (int i{0}, n = nums.size(); i < n; ++i) {
            ans = (ans + static_cast<int64_t>(p2[i]) * nums[i] % MOD) % MOD;
            ans = (ans - static_cast<int64_t>(p2[n - i - 1]) * nums[i] % MOD + MOD) % MOD;
        }
        return static_cast<int>(ans);
    }
};