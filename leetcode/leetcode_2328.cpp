/**
 * @file leetcode_2328.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/number-of-increasing-paths-in-a-grid/description/
 * @version 0.1
 * @date 2024-06-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <map>
#include <utility>
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

// left, up, right, down
constexpr int DIRECTIONS[4][2]{
    {0, -1},
    {-1, 0},
    {0, 1},
    {1, 0}};

constexpr int MOD = 1e9 + 7;

class Solution {
public:
    // 递增路径dp可以先根据值排序, 再进行dp
    // 也可以以每一个点作为起点进行记忆化搜索
    int countPaths(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        std::map<int, std::vector<std::pair<int, int>>> nums;
        for (auto i{0}; i < n; ++i) {
            for (auto j{0}; j < m; ++j) {
                nums[grid[i][j]].emplace_back(i, j);
            }
        }
        // 到达(x,y)的方案数
        std::vector<std::vector<int>> dp(n, std::vector<int>(m, 1));
        for (auto&& [num, arr] : nums) {
            for (auto&& [x, y] : arr) {
                // dp[x][y] = 1;
                for (auto&& [ox, oy] : DIRECTIONS) {
                    int nx = x + ox, ny = y + oy;
                    if ((0 <= nx && nx < n) && (0 <= ny && ny < m) && grid[nx][ny] < grid[x][y]) {
                        dp[x][y] += dp[nx][ny];
                        dp[x][y] %= MOD;
                    }
                }
            }
        }
        int ans = 0;
        for (auto&& vals : dp) {
            for (int v : vals) {
                ans = (ans + v) % MOD;
            }
        }
        return ans;
    }
};

int main() {
    std::vector<std::vector<int>> grid{{1}, {2}};
    std::cout << Solution().countPaths(grid);
}