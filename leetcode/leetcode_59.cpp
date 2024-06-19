/**
 * @file leetcode_59.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/spiral-matrix-ii/description/
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
    vector<vector<int>> generateMatrix(int n) {
        int num = 0;
        int left = 0, top = 0, right = n - 1, bottom = n - 1;

        vector<vector<int>> res(n, vector<int>(n));
        while (num < n * n) {

            // left to right
            for (int i = left; i <= right; ++i) res[top][i] = ++num;
            ++top;

            // top to bottom
            for (int i = top; i <= bottom; ++i) res[i][right] = ++num;
            --right;

            // right to left
            for (int i = right; i >= left; --i) res[bottom][i] = ++num;
            --bottom;

            // bottom to top
            for (int i = bottom; i >= top; --i) res[i][left] = ++num;
            ++left;
        }
        return res;
    }
};
int main() {
    Solution().generateMatrix(3);
    return 0;
}