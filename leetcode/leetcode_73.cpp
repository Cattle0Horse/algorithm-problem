/**
 * @file leetcode_73.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/set-matrix-zeroes/
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

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        std::vector<bool> row(n), col(m);
        for (int i{0}; i < n; ++i) {
            for (int j{0}; j < m; ++j) {
                if (matrix[i][j] == 0) {
                    row[i] = col[j] = true;
                }
            }
        }
        for (int i{0}; i < n; ++i) {
            if (row[i]) fill(matrix[i].begin(), matrix[i].end(), 0);
        }
        for (int j{0}; j < m; ++j) {
            if (col[j]) {
                for (int i{0}; i < n; ++i) {
                    matrix[i][j] = 0;
                }
            }
        }
    }
};