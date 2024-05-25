/**
 * @file leetcode_2462.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/total-cost-to-hire-k-workers/?envType=daily-question&envId=2024-05-01
 * @version 0.1
 * @date 2024-05-01
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <functional>
#include <queue>
#include <vector>
class Solution {
public:
    long long totalCost(std::vector<int>& costs, int k, int candidates) {
        auto pop_top = [](auto& que) {
            int top = que.top();
            que.pop();
            return top;
        };
        std::priority_queue<int, std::vector<int>, std::greater<int>> left, right;
        int l = 0, r = costs.size() - 1;
        while (l < candidates) {
            left.push(costs[l++]);
            right.push(costs[r--]);
        }
        long long ans = 0;
        while (k--) {
            if (left.top() <= right.top()) {
                ans += pop_top(left);
                left.push(l++);
            } else {
                ans += pop_top(right);
                right.push(r++);
            }
        }
        return ans;
    }
};