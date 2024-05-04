/**
 * @file leetcode_2639.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/find-the-width-of-columns-of-a-grid/?envType=daily-question&envId=2024-04-27
 * @version 0.1
 * @date 2024-04-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <vector>
using namespace std;
class Solution {
public:
    vector<int> findColumnWidth(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid.front().size();
        std::vector<int> ans(m);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                ans[i] = max(ans[i], static_cast<int>(std::to_string(grid[j][i]).length()));
            }
        }
        return ans;
    }
};