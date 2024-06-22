/**
 * @file leetcode_1774.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/closest-dessert-cost/description/
 * @version 0.1
 * @date 2024-06-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <cstdlib>
#ifdef OY_LOCAL
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
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
    // 对每一个基料进行dp, 由于每种配料可以选择两份, 拷贝一份配料数组即可
    // 转化为01背包
    int closestCost(vector<int>& baseCosts, vector<int>& toppingCosts, int target) {
        int m = toppingCosts.size();
        std::vector<int> cost;
        cost.reserve(m << 1);
        for (auto&& c : toppingCosts) cost.push_back(c), cost.push_back(c);
        int sum = std::accumulate(cost.begin(), cost.end(), 0);
        int ans = baseCosts[0];
        for (auto&& base : baseCosts) {
            if (target <= base) {
                int a = std::abs(ans - target);
                int b = std::abs(base - target);
                if ((b < a) || (b == a && ans > base)) {
                    ans = base;
                }
                continue;
            }
            std::vector<int> dp(sum + 1);
            dp[0] = true;
            for (int c : cost) {
                for (auto x{sum}; x >= c; --x) {
                    dp[x] |= dp[x - c];
                }
            }
            // base + i
            for (auto i{0}; i <= sum; ++i) {
                if (dp[i]) {
                    int cur = base + i;
                    int a = std::abs(ans - target);
                    int b = std::abs(cur - target);
                    if ((b < a) || (b == a && ans > cur)) {
                        ans = cur;
                    }
                }
            }
        }
        return ans;
    }
};
