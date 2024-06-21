/**
 * @file LCP_56.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/6UEx57/
 * @version 0.1
 * @date 2024-06-21
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <cstdlib>
#include <deque>
#include <functional>
#include <queue>
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

// left, up, right, down
constexpr int DIRECTIONS[4][2]{
    {0, -1},
    {-1, 0},
    {0, 1},
    {1, 0}};

// left, up, right, down
constexpr char ID_CHAR[4]{'<', '^', '>', 'v'};

class Solution {
public:
    int conveyorBelt(vector<string>& matrix, vector<int>& start, vector<int>& end) {
        int sx{start[0]}, sy{start[1]};
        int ex{end[0]}, ey{end[1]};
        int n = matrix.size(), m = matrix[0].size();
        const int inf = n * m;
        std::vector<std::vector<int>> dp(n, std::vector<int>(m, inf));
        // 双端队列 根据入队头和入队尾 可以减少对节点扩展的次数
        // std::deque<std::pair<int, int>> q;
        // q.push_back({sx, sy});
        // dp[sx][sy] = 0;
        // while (!q.empty()) {
        //     auto [x, y] = q.front();
        //     q.pop_front();
        //     for (int i{0}; i < 4; ++i) {
        //         int nx{x + DIRECTIONS[i][0]}, ny{y + DIRECTIONS[i][1]};
        //         if ((0 <= nx && nx < n) && (0 <= ny && ny < m)) {
        //             int cost = (ID_CHAR[i] != matrix[x][y]);
        //             if (dp[x][y] + cost < dp[nx][ny]) {
        //                 dp[nx][ny] = dp[x][y] + cost;
        //                 if (cost == 0) {
        //                     q.push_front({nx, ny});
        //                 } else {
        //                     q.push_back({nx, ny});
        //                 }
        //             }
        //         }
        //     }
        // }
        // return dp[ex][ey];

        std::queue<std::pair<int, int>> q;
        q.push({sx, sy});
        dp[sx][sy] = 0;
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            for (int i{0}; i < 4; ++i) {
                int nx{x + DIRECTIONS[i][0]}, ny{y + DIRECTIONS[i][1]};
                if ((0 <= nx && nx < n) && (0 <= ny && ny < m)) {
                    int cost = (ID_CHAR[i] != matrix[x][y]);
                    if (dp[x][y] + cost < dp[nx][ny]) {
                        dp[nx][ny] = dp[x][y] + cost;
                        q.push({nx, ny});
                    }
                }
            }
        }
        return dp[ex][ey];

        // // 最多可以操作cnt次传送带, 是否可以到达终点
        // auto check = [&](int cnt) -> bool {

        // };
        // int l = -1, r = std::abs(ex - sx) + std::abs(ey - sy);
        // while (l + 1 < r) {
        //     int mid = (l + r) >> 1;
        //     if (check(mid)) {
        //         r = mid;
        //     } else {
        //         l = mid;
        //     }
        // }
        // return r;
    }
};