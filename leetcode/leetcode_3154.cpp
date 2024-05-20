/**
 * @file leetcode_3154.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/find-number-of-ways-to-reach-the-k-th-stair/
 * @version 0.1
 * @date 2024-05-20
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <array>
#include <unordered_map>
#include <functional>
class Solution {
public:
    int waysToReachStair(int k) {
        std::array<std::array<std::unordered_map<int, int>, 32>, 2> dp;
        std::function<int(bool, int, int)> dfs = [&](bool limit, int jump, int i) {
            if (i > k + 1) {
                return 0;
            }
            if (dp[limit][jump].contains(i)) {
                return dp[limit][jump][i];
            }
            int ans = i == k;
            if (i != 0 && !limit) {
                ans += dfs(true, jump, i - 1);
            }
            ans += dfs(false, jump + 1, i + (1 << jump));
            return dp[limit][jump][i] = ans;
        };
        return dfs(false, 0, 1);
    }
};