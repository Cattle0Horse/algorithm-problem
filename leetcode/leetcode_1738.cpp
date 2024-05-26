/**
 * @file leetcode_1738.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/find-kth-largest-xor-coordinate-value/?envType=daily-question&envId=2024-05-26
 * @version 0.1
 * @date 2024-05-26
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
#include <vector>
class Solution {
public:
    int kthLargestValue(std::vector<std::vector<int>>& matrix, int k) {
        int m = matrix.size(), n = matrix.front().size();
        for (int i{1}; i < n; ++i) {
            matrix[0][i] ^= matrix[0][i - 1];
        }
        for (int i{1}; i < m; ++i) {
            matrix[i][0] ^= matrix[i - 1][0];
        }
        for (int i{1}; i < m; ++i) {
            for (int j{1}; j < n; ++j) {
                matrix[i][j] ^= matrix[i - 1][j - 1] ^ matrix[i - 1][j] ^ matrix[i][j - 1];
            }
        }
        std::vector<int> ans;
        ans.reserve(m * n);
        for (auto&& row : matrix) {
            for (int v : row) {
                ans.push_back(v);
            }
        }
        std::nth_element(ans.begin(), ans.end() - k, ans.end());
        return ans[ans.size() - k];
    }
};