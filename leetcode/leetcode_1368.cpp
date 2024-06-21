/**
 * @file leetcode_1368.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/description/
 * @version 0.1
 * @date 2024-06-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <deque>
#include <utility>
#ifdef OY_LOCAL
#include <vector>
#include <string>
#include <iostream>
using namespace std;
#endif

[[maybe_unused]] auto _ = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();

// right, left, down, up
constexpr int DIRECTIONS[4][2]{
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0}};

class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        const int inf = n + m;
        std::vector<std::vector<int>> dp(n, std::vector<int>(m, inf));
        std::deque<std::pair<int, int>> q;
        q.emplace_back(0, 0);
        dp[0][0] = 0;
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop_front();
            for (int i{0}; i < 4; ++i) {
                int nx{x + DIRECTIONS[i][0]}, ny{y + DIRECTIONS[i][1]};
                if ((0 <= nx && nx < n) && (0 <= ny && ny < m)) {
                    int cost = (grid[x][y] - 1 != i);
                    if (dp[x][y] + cost < dp[nx][ny]) {
                        dp[nx][ny] = dp[x][y] + cost;
                        if (cost == 0) {
                            q.emplace_front(nx, ny);
                        } else {
                            q.emplace_back(nx, ny);
                        }
                    }
                }
            }
        }
        return dp[n - 1][m - 1];
    }
};