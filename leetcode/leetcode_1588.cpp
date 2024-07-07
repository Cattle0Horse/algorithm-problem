/**
 * @file leetcode_1588.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/sum-of-all-odd-length-subarrays/description/
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
    // 以i结尾的...
    int sumOddLengthSubarrays(vector<int>& arr) {
        int n = arr.size();
        if (n == 1) return arr[0];
        std::vector<int> dp_cnt(n, 1);
        std::vector<int> dp_sum(n);
        dp_sum[0] = arr[0];
        dp_sum[1] = arr[1];
        for (auto i{2}; i < n; ++i) {
            dp_cnt[i] = dp_cnt[i - 2] + 1;
            dp_sum[i] = arr[i] + dp_sum[i - 2] + (arr[i] + arr[i - 1]) * dp_cnt[i - 2];
        }
        return std::accumulate(dp_sum.begin(), dp_sum.end(), 0);
    }
    // int sumOddLengthSubarrays(vector<int>& arr) {
    //     int n = arr.size();
    //     if (n == 1) return arr[0];
    //     std::vector<int> dp_cnt(n, 1);
    //     std::vector<int> dp_sum(n);
    //     dp_sum[0] = arr[0];
    //     dp_sum[1] = arr[1];
    //     int ans = arr[0] + arr[1];
    //     for (auto i{2}; i < n; ++i) {
    //         dp_cnt[i] = dp_cnt[i - 2] + 1;
    //         dp_sum[i] = arr[i] + dp_sum[i - 2] + (arr[i] + arr[i - 1]) * dp_cnt[i - 2];
    //         ans += dp_sum[i];
    //     }
    //     return ans;
    // }
};