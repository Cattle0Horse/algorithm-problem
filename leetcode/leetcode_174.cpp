/**
 * @file leetcode_174.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/dungeon-game/description/
 * @version 0.1
 * @date 2024-06-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <functional>
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
        // 这道题由于有“加血”的过程，只能依赖后面的值判断需要的血量。
        // 所以这里的dp[i][j]表达的意思是：“从（i，j）出发，到达终点需要最少的血量”。
        // 因此，正序的含义为“从起点出发，到达位置（i，j）所需要的最少血量”；
        // 倒序的含义是“从（i，j）出发，到达终点需要最少的血量”。
        // 初始血量本来就是要求的，所以只能倒序dp
        // https://leetcode.cn/problems/dungeon-game/solutions/24493/cong-hui-su-dao-ji-yi-hua-sou-suo-dao-dong-tai-gui/comments/499212
    int calculateMinimumHP(vector<vector<int>>& g) {
        int n = g.size(), m = g[0].size();
        // dp[i][j] : 从 (i,j) 出发 到达终点 的最少消耗的健康点数
        std::vector<std::vector<int>> dp(n, std::vector<int>(m, 0));
        dp[n - 1][m - 1] = std::max(0, -g[n - 1][m - 1]);
        for (auto i{n - 2}; i >= 0; --i) {
            dp[i][m - 1] = std::max(0, dp[i + 1][m - 1] - g[i][m - 1]);
        }
        for (auto j{m - 2}; j >= 0; --j) {
            dp[n - 1][j] = std::max(0, dp[n - 1][j + 1] - g[n - 1][j]);
        }
        for (auto i{n - 2}; i >= 0; --i) {
            for (auto j{m - 2}; j >= 0; --j) {
                dp[i][j] = std::max(0, std::min(dp[i + 1][j], dp[i][j + 1]) - g[i][j]);
            }
        }
        return dp[0][0] + 1;
    }
};