/**
 * @file leetcode_2681.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/power-of-heroes/description/
 * @version 0.1
 * @date 2024-06-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <cstdint>
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
    // 不要求连续
    int sumOfPower(vector<int>& nums) {
        std::ranges::sort(nums);

        // nums[i]作为最大值时, nums[0...i]都可最为最小值
        // nums[k]作为最小值时(0<=k<i), 可与 nums[k+1...i-1]的子集进行组合
        // 则nums[i]作为最大值时的贡献为  nums[i]^3 + nums[i]^2 * sum(nums[k]*(2^(i-k-1)))
        // 设 f(i) = sum(nums[k]*(2^(i-k-1)))
        // 则 f(i+1) = 2*f(i) + nums[i]

        int64_t ans{0};
        int64_t f = 0;
        for (int64_t x : nums) {
            int64_t pf = x * x % MOD;
            ans = (ans + pf % MOD * x % MOD + pf * f % MOD) % MOD;
            f = (2 * f % MOD + x) % MOD;
        }
        return ans;
    }
};