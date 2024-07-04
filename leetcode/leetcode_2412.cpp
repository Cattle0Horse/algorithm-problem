/**
 * @file leetcode_2412.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/minimum-money-required-before-transactions/
 * @version 0.1
 * @date 2024-07-01
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
#ifdef OY_LOCAL
#include <vector>
#include <iostream>
using namespace std;
#endif

[[maybe_unused]] auto __init_io__ = []() {
    return std::cin.tie(nullptr)->sync_with_stdio(false);
}();

class Solution {
public:
    // 题目要求任意情况下都要能够交易完所有 的最少钱
    // 那么按照最坏情况, 永远先亏钱
    // 一个关键点是获得的cashback要很小, 即让最大的cashback在尽可能靠后
    // 另一个是 消费的小的cost靠后
    long long minimumMoney(vector<vector<int>>& arr) {
        long long lose = 0;
        long long mx = 0;
        for (auto&& pairs : arr) {
            int cost = pairs[0], cashback = pairs[1];
            


        }
        return lose;

        // 这是求的以某一种顺序下交易完所有的最少钱
        // long long cur = 0;
        // long long hand = 0;
        // long long sum = 0;
        // for (auto&& num : arr) {
        //     int cost = num[0], cashback = num[1];
        //     // 到当前位置的时候手里至少要有cost块钱
        //     // 且是在初始的手里+cost
        //     if (cur < cost) hand += cost - cur;
        //     sum += -cost + cashback;
        //     cur = hand + sum;
        // }
        // return hand;
    }
};