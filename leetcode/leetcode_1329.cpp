/**
 * @file leetcode_1329.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/sort-the-matrix-diagonally/?envType=daily-question&envId=2024-04-29
 * @version 0.1
 * @date 2024-04-29
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
#include <cstdlib>
#include <vector>
using namespace std;
class Solution {
public:
    vector<vector<int>> diagonalSort(vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size();
        vector<vector<int>> diag(m + n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                diag[i - j + m].push_back(mat[i][j]);
            }
        }
        for (auto& d : diag) {
            sort(d.rbegin(), d.rend());
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                mat[i][j] = diag[i - j + m].back();
                diag[i - j + m].pop_back();
            }
        }
        return mat;
    }
};
