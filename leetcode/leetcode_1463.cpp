/**
 * @file leetcode_1463.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/cherry-pickup-ii/description/?envType=daily-question&envId=2024-05-07
 * @version 0.1
 * @date 2024-05-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
#include <cstring>
#include <functional>
#include <vector>
using namespace std;

class Solution {
private:
    constexpr static int N = 70, NONE = -1;

public:
    int cherryPickup(vector<vector<int>>& grid) {
        int memo[N][N][N];
        // for (int i = 0; i < N; i++) {
        //     for (int j = 0; j < N; j++) {
        //         std::fill(memo[i][j], memo[i][j] + N, NONE);
        //     }
        // }
        memset(memo, NONE, sizeof memo);
        int n = grid.size(), m = grid.front().size();
        std::function<int(int, int, int)> dfs = [&](int r, int c1, int c2) {
            if (r == n) {
                return 0;
            }
            int& me = memo[r][c1][c2];
            if (me != NONE) return me;
            int ans = (c1 == c2 ? grid[r][c1] : grid[r][c1] + grid[r][c2]);
            int mx = 0;
            for (int i = -1; i <= 1; i++) {
                int nc1 = c1 + i;
                if (0 <= nc1 && nc1 < m) {
                    for (int j = -1; j <= 1; j++) {
                        int nc2 = c2 + j;
                        if (0 <= nc2 && nc2 < m) {
                            mx = std::max(mx, dfs(r + 1, nc1, nc2));
                        }
                    }
                }
            }
            // ans += mx;
            // me = ans;
            // return ans;
            return me = ans + mx;
        };
        return dfs(0, 0, m - 1);
    }
};

class Solution2 {
private:
    constexpr static int N = 70, NONE = -1;

public:
    int cherryPickup(vector<vector<int>>& grid) {
        int memo[N][N][N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                std::fill(memo[i][j], memo[i][j] + N, NONE);
            }
        }
        int n = grid.size(), m = grid.front().size();
        std::function<int(int, int, int)> dfs = [&](int r, int c1, int c2) {
            if (r == n) {
                return 0;
            }
            int& me = memo[r][c1][c2];
            if (me != NONE) return me;
            int ans = (c1 == c2 ? grid[r][c1] : grid[r][c1] + grid[r][c2]);
            int mx = 0;
            for (int i = -1; i <= 1; i++) {
                int nc1 = c1 + i;
                if (0 <= nc1 && nc1 < m) {
                    for (int j = -1; j <= 1; j++) {
                        int nc2 = c2 + j;
                        if (0 <= nc2 && nc2 < m) {
                            mx = std::max(mx, dfs(r + 1, nc1, nc2));
                        }
                    }
                }
            }
            ans += mx;
            me = ans;
            return ans;
        };
        return dfs(0, 0, m - 1);
    }
};