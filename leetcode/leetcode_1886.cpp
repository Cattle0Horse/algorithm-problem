/**
 * @file leetcode_1886.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/determine-whether-matrix-can-be-obtained-by-rotation/
 * @version 0.1
 * @date 2024-07-06
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <algorithm>
#include <cassert>
#include <concepts>
#ifdef OY_LOCAL
#include <vector>
#include <iostream>
using namespace std;
#endif

[[maybe_unused]] auto __init_io__ = []() {
    return std::cin.tie(nullptr)->sync_with_stdio(false);
}();
template<typename T>
void rotate90(std::vector<std::vector<T>>& matrix) {
    int n = matrix.size();
    // 枚举圈数，最内圈->最外圈
    for (int i = n / 2 - 1; i >= 0; --i) {
        // 枚举一圈的需要交换的元素
        for (int j = (n + 1) / 2 - 1; j >= 0; --j) {
            // 四个元素交换位置
            // (x, y) -> (y, n-x-1)
            T temp(std::move(matrix[i][j]));
            matrix[i][j] = std::move(matrix[n - j - 1][i]);
            matrix[n - j - 1][i] = std::move(matrix[n - i - 1][n - j - 1]);
            matrix[n - i - 1][n - j - 1] = std::move(matrix[j][n - i - 1]);
            matrix[j][n - i - 1] = std::move(temp);
        }
    }
}
class Solution {
public:
    bool findRotation(vector<vector<int>>& mat, vector<vector<int>>& target) {
        for (auto k{0}; k < 4; ++k) {
            if (mat == target) return true;
            rotate90(mat);
        }
        return false;
    }
};
