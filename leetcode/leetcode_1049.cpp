/**
 * @file leetcode_1049.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/last-stone-weight-ii/description/
 * @version 0.1
 * @date 2024-06-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <cstdlib>
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

class Solution {
public:
    // 分成两堆, 使得两堆差值最小
    int lastStoneWeightII(vector<int>& stones) {
        int sum = std::accumulate(stones.begin(), stones.end(), 0);
        int m = sum >> 1;
        std::vector<int> dp(m + 1);
        dp[0] = true;
        for (auto&& stone : stones) {
            for (auto x{m}; x >= stone; --x) {
                dp[x] |= dp[x - stone];
            }
        }
        for (auto i{m}; i >= 0; --i) {
            if (dp[i]) return sum - 2 * i;
        }
        return -100;
    }
};