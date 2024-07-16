/**
 * @file interview_08_02.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/robot-in-a-grid-lcci/
 * @version 0.1
 * @date 2024-07-15
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifdef Cattle_Horse
#include "leetcode.h" // IWYU pragma: keep
using namespace std;
#else
#define dbg(...) void(114514)
#endif

[[maybe_unused]] auto __init_io__ = []() {
    return std::cin.tie(nullptr)->sync_with_stdio(false);
}();

// todo: leetcode网站出问题, 提交不了 2024-07-15T22:53:08+08:00
class Solution {
public:
    vector<vector<int>> pathWithObstacles(vector<vector<int>>& obstacleGrid) {
        int r = obstacleGrid.size(), c = obstacleGrid[0].size();
        std::vector<std::vector<int>> path;
        std::vector<std::vector<bool>> vis(r, std::vector<bool>(c));
        auto dfs = [&](auto&& self, int x, int y) -> bool {
            path.emplace_back(x, y);
            vis[x][y] = true;
            if (x == r - 1 && y == c - 1) {
                return true;
            }
            for (auto&& [ox, oy] : std::vector<std::pair<int, int>>{{0, 1}, {1, 0}}) {
                int nx = x + ox, ny = y + oy;
                if (nx < r && ny < c && !vis[nx][ny] && self(self, nx, ny)) return true;
            }
            path.pop_back();
            return false;
        };
        // dfs(dfs, 0, 0);
        // return path;
        if (dfs(dfs, 0, 0)) {
            return path;
        }
        return {};
    }
};

#ifdef Cattle_Horse
int main() {
    //
}
#endif