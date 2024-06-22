/**
 * @file leetcode_1301.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/number-of-paths-with-max-score/description/
 * @version 0.1
 * @date 2024-06-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <cctype>
#include <limits>
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

constexpr int mod = 1e9 + 7, inf = std::numeric_limits<int>::min();

class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        int n = board.size();
        board[0][0] = board[n - 1][n - 1] = '0';
        std::vector<std::vector<std::pair<int, int>>> dp(n, std::vector<std::pair<int, int>>(n, {inf, 0}));
        dp[n - 1][n - 1] = {0, 1};
        auto get = [&](int x, int y) -> std::pair<int, int> {
            if ((0 <= x && x < n) && (0 <= y && y < n)) return dp[x][y];
            return {inf, inf};
        };
        auto update = [&](int x, int y, int i, int j) {
            auto other = get(i, j);
            if (other.first < 0) return;
            if (dp[x][y].first < other.first) {
                dp[x][y] = other;
            } else if (dp[x][y].first == other.first) {
                dp[x][y].second = (dp[x][y].second + other.second) % mod;
            }
        };
        for (int i = n - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                if (i == n - 1 && j == n - 1) continue;
                if (board[i][j] == 'X') continue;
                update(i, j, i + 1, j + 1);
                update(i, j, i + 1, j);
                update(i, j, i, j + 1);
                dp[i][j].first += board[i][j] - '0';
            }
        }
        auto [val, cnt] = dp[0][0];
        if (val < 0) return {0, 0};
        return {val, cnt};
    }
};