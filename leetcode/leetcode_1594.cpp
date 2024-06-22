/**
 * @file leetcode_1594.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/maximum-non-negative-product-in-a-matrix/description/
 * @version 0.1
 * @date 2024-06-21
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <algorithm>
#include <array>
#include <limits>
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

constexpr int mod = 1e9 + 7;

class Solution {
public:
    int maxProductPath(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        std::vector<std::vector<long long>> mx(m, std::vector<long long>(n));
        std::vector<std::vector<long long>> mn(m, std::vector<long long>(n));
        mx[0][0] = mn[0][0] = grid[0][0];
        for (int i{1}; i < m; ++i) {
            mx[i][0] = mn[i][0] = mn[i - 1][0] * grid[i][0];
        }
        for (int j{1}; j < n; ++j) {
            mx[0][j] = mn[0][j] = mn[0][j - 1] * grid[0][j];
        }
        for (int i{1}; i < m; ++i) {
            for (int j{1}; j < n; ++j) {
                int cur = grid[i][j];
                std::array<long long, 4> vals{mx[i - 1][j] * cur, mn[i - 1][j] * cur, mx[i][j - 1] * cur, mn[i][j - 1] * cur};
                mx[i][j] = ranges::max(vals);
                mn[i][j] = ranges::min(vals);
            }
        }
        long long ans = mx.back().back();
        return ans >= 0 ? ans % mod : -1;
    }
};