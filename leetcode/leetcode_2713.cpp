/**
 * @file leetcode_2713.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/maximum-strictly-increasing-cells-in-a-matrix/description/?envType=daily-question&envId=2024-06-19
 * @version 0.1
 * @date 2024-06-19
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <algorithm>
#include <map>
#ifdef OY_LOCAL
#include <vector>
#include <string>
#include <iostream>
using namespace std;
#endif

[[maybe_unused]] auto ____ = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();

#include <vector>
class Solution {
public:
    // 按值递推
    int maxIncreasingCells(std::vector<std::vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size();
        std::map<int, std::vector<std::pair<int, int>>> g;
        for (int i{0}; i < n; ++i) {
            for (int j{0}; j < m; ++j) {
                g[mat[i][j]].emplace_back(i, j);
            }
        }
        std::vector<int> mx_row(n), mx_col(m);
        for (auto&& [_, pos] : g) {
            int sz = pos.size();
            std::vector<int> mx;
            mx.reserve(sz);
            for (auto&& [i, j] : pos) {
                mx.push_back(std::max(mx_row[i], mx_col[j]) + 1);
            }
            for (int k = 0; k < sz; k++) {
                auto& [i, j] = pos[k];
                mx_row[i] = max(mx_row[i], mx[k]); // 更新第 i 行的最大 f 值
                mx_col[j] = max(mx_col[j], mx[k]); // 更新第 j 列的最大 f 值
            }
        }
        return *std::max_element(mx_row.begin(), mx_row.end());
    }
};