/**
 * @file leetcode_2813.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/maximum-elegance-of-a-k-length-subsequence/description/?envType=daily-question&envId=2024-06-13
 * @version 0.1
 * @date 2024-06-13
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
#include <unordered_set>
#include <vector>
class Solution {
public:
    long long findMaximumElegance(std::vector<std::vector<int>>& items, int k) {
        std::sort(items.begin(), items.end(), [](const auto& a, const auto& b) {
            return a[0] > b[0];
        });
        std::vector<int> stack;
        std::unordered_set<int> vis;
        long long ans{0}, total{0};
        for (int i{0}; i < items.size(); ++i) {
            auto& cur{items[i]};
            int profit{cur[0]}, category{cur[1]};
            if (i < k) {
                total += profit;
                if (vis.contains(category)) {
                    stack.push_back(profit);
                } else {
                    vis.insert(category);
                }
            } else if (!stack.empty() && !vis.contains(category)) {
                vis.insert(category);
                total += profit - stack.back();
                stack.pop_back();
            }
            long long sz = vis.size();
            ans = std::max(ans, total + sz * sz);
        }
        return ans;
    }
};