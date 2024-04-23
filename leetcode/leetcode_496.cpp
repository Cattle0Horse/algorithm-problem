/**
 * @file leetcode_496.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/next-greater-element-i/
 * @version 0.1
 * @date 2024-04-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;
class Solution {
private:
    vector<int> getNext(const vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n, -1);
        stack<int> s;
        for (int i{0}; i < n; ++i) {
            while (!s.empty() && nums[s.top()] < nums[i]) {
                ans[s.top()] = nums[i];
                s.pop();
            }
            s.push(i);
        }
        return ans;
    }

public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        vector<int> next{getNext(nums2)};
        unordered_map<int, int> index;
        int n = nums2.size();
        for (int i{0}; i < n; ++i) {
            index[nums2[i]] = i;
        }
        int m = nums1.size();
        vector<int> ans(m);
        for (int i{0}; i < m; ++i) {
            ans[i] = next[index[nums1[i]]];
        }
        return ans;
    }
};