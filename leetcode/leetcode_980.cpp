/**
 * @file leetcode_980.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/unique-paths-iii/description/
 * @version 0.1
 * @date 2024-06-16
 *
 * @copyright Copyright (c) 2024
 *
 */
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
// left, up, right, down
constexpr int DIRECTIONS[4][2]{
    {0, -1},
    {-1, 0},
    {0, 1},
    {1, 0}};

class Solution {
public:
    int direction;
    int uniquePathsIII(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        int startX, startY, endX, endY, ans{0}, cnt{n * m};

        auto dfs = [&](auto&& dfs, int x, int y) -> void {
            if (x == endX && y == endY) {
                std::cout << cnt << std::endl;
                if (cnt == 0) ++ans;
                return;
            }
            for (auto&& [ox, oy] : DIRECTIONS) {
                int nx{x + ox}, ny{y + oy};
                if (0 <= nx && nx < n && 0 <= ny && ny < m && grid[nx][ny] != -1) {
                    int temp = grid[nx][ny];
                    grid[nx][ny] = -1;
                    --cnt;
                    dfs(dfs, nx, ny);
                    ++cnt;
                    grid[nx][ny] = temp;
                }
            }
        };

        for (int i{0}; i < n; ++i) {
            for (int j{0}; j < m; ++j) {
                if (grid[i][j] == 1) startX = i, startY = j, --cnt, grid[i][j] = -1;
                else if (grid[i][j] == 2) endX = i, endY = j;
                else if (grid[i][j] == -1) --cnt;
            }
        }

        dfs(dfs, startX, startY);
        return ans;
    }
};

int main() {
    std::vector<std::vector<int>> grid{{1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 2, -1}};
    Solution().uniquePathsIII(grid);
    return 0;
}