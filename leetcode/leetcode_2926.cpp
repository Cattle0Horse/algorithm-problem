/**
 * @file leetcode_2926.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/contest/weekly-contest-370/problems/maximum-balanced-subsequence-sum/
 * @version 0.1
 * @date 2024-06-20
 *
 * @copyright Copyright (c) 2024
 *
 */
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

class Solution {
public:
    // dp[i]: [0,i]平衡子序列的最大和
    // 平衡子序列一定是递增的
    // dp[i]: 以nums[i]结尾的平衡子序列的最大和
    // 如何处理结尾元素???
    // 需要快速找到i之前的满足条件的最大和

    // i < j
    // 找到 nums[j] - nums[i] >= j - i
    // 即num[j] - j >= nums[i] - i

    // 对于 i < j
    // dp[j] = max(dp[...i], num[j]) 其中 i 是 num[j] - j >= nums[i] - i

    // 当遇到i时, num[0...i-1]中的dp小于dp[i]的可以淘汰了
    long long maxBalancedSubsequenceSum(vector<int>& nums) {
        int n = nums.size();
        std::vector<int> arr(n);
        for (int i{0}; i < n; ++i) {
            arr[i] = nums[i] - i;
        }
        
    }
};