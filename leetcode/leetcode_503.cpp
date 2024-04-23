/**
 * @file leetcode_503.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/next-greater-element-ii/
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
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n, -1);
        stack<int> s;
        for (int i{0}; i < 2 * n - 1; ++i) {
            int index = i % n;
            while (!s.empty() && nums[s.top()] < nums[index]) {
                ans[s.top()] = nums[index];
                s.pop();
            }
            s.push(i);
        }
        return ans;
    }
};