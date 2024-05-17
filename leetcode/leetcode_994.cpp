/**
 * @file leetcode_994.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/rotting-oranges/description/?envType=daily-question&envId=2024-05-13
 * @version 0.1
 * @date 2024-05-13
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <queue>
#include <utility>
#include <vector>
using namespace std;
class Solution {
private:
    constexpr static int dx[4]{0, -1, 0, 1}, dy[4]{-1, 0, 1, 0};

public:
    int orangesRotting(vector<vector<int>>& grid) {
        queue<pair<int, int>> q;
        int m = grid.size(), n = grid.front().size(), ans = 0, cnt = 0;
        // vector<vector<bool>> vis(m, vector<bool>(n));
        for (int i{0}; i < m; ++i) {
            for (int j{0}; j < n; ++j) {
                if (grid[i][j] == 2) {
                    q.push({i, j});
                } else if (grid[i][j] == 1) {
                    ++cnt;
                }
            }
        }
        if (cnt == 0) return 0;
        while (!q.empty() || cnt == 0) {
            ++ans;
            for (int k = q.size(); k > 0; k--) {
                auto [x, y] = q.front();
                q.pop();
                for (int i{0}; i < 4; ++i) {
                    int nx = x + dx[i], ny = y + dy[i];
                    if (nx < 0 || nx >= m || ny < 0 || ny >= n || grid[nx][ny] != 1) {
                        continue;
                    }
                    grid[nx][ny] = 2;
                    q.push({nx, ny});
                    --cnt;
                }
            }
        }
        return cnt == 0 ? ans : -1;
    }
};

int main() {
    vector<vector<int>> grid{
        {2, 1, 1},
        {1, 1, 0},
        {0, 1, 1}};
    Solution().orangesRotting(grid);
    return 0;
}