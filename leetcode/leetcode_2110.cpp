/**
 * @file leetcode_2110.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/number-of-smooth-descent-periods-of-a-stock/
 * @version 0.1
 * @date 2024-07-07
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

[[maybe_unused]] auto __init_io__ = []() {
    return std::cin.tie(nullptr)->sync_with_stdio(false);
}();

class Solution {
public:
    long long getDescentPeriods(vector<int>& prices) {
        int n = prices.size();
        // pre : 以前一个数字结尾的平滑下降阶段个数
        int pre = 1;
        long long ans = 1;
        for (auto i{1}; i < n; ++i) {
            if (prices[i - 1] == prices[i] + 1) {
                pre += 1;
            } else {
                pre = 1;
            }
            ans += pre;
        }
        return ans;
    }
    // long long getDescentPeriods(vector<int>& prices) {
    //     int n = prices.size();
    //     // dp[i] : 以prices[i]结尾的平滑下降阶段个数
    //     std::vector<int> dp(n);
    //     long long ans = dp[0] = 1;
    //     for (auto i{1}; i < n; ++i) {
    //         if (prices[i - 1] == prices[i] + 1) {
    //             dp[i] = dp[i - 1] + 1;
    //         } else {
    //             dp[i] = 1;
    //         }
    //         ans += dp[i];
    //     }
    //     return ans;
    // }
};