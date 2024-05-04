/**
 * @file leetcode_1252.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/cells-with-odd-values-in-a-matrix/
 * @version 0.1
 * @date 2024-04-29
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
#include <vector>
class Solution {
public:
    int oddCells(int m, int n, std::vector<std::vector<int>>& indices) {
        std::vector<int> cnt_row(m), cnt_col(n);
        for (auto&& point : indices) {
            ++cnt_row[point[0]];
            ++cnt_col[point[1]];
        }
        int even = std::count_if(cnt_col.begin(), cnt_col.end(), [](int v) {
            return v % 2 == 0;
        });
        int ans = 0;
        for (int cnt : cnt_row) {
            ans += (cnt % 2 == 1) ? even : n - even;
        }
        return ans;
    }
};