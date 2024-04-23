/**
 * @file leetcode_1475.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/final-prices-with-a-special-discount-in-a-shop/description/
 * @version 0.1
 * @date 2024-04-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> finalPrices(vector<int>& prices) {
        int n = prices.size();
        vector<int> ans(prices);
        stack<int> s;
        for (int i{0}; i < n; ++i) {
            while (!s.empty() && prices[s.top()] >= prices[i]) {
                ans[s.top()] -= prices[i];
                s.pop();
            }
            s.push(i);
        }
        return ans;
    }
};