/**
 * @file leetcode_1019.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/next-greater-node-in-linked-list/
 * @version 0.1
 * @date 2024-04-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int val = 0, ListNode* next = nullptr): val(val), next(next) {}
};

class Solution {
public:
    vector<int> nextLargerNodes(ListNode* head) {
        vector<int> ans;
        stack<int> s;
        int cnt = 0;
        for (ListNode* ptr{head}; ptr != nullptr; ptr = ptr->next) {
            while (!s.empty() && ans[s.top()] < ptr->val) {
                ans[s.top()] = ptr->val;
                s.pop();
            }
            ans.push_back(ptr->val);
            s.push(cnt++);
        }
        // 剩余元素均无下一个更大值
        for (; !s.empty(); s.pop()) {
            ans[s.top()] = 0;
        }
        return ans;
    }
};