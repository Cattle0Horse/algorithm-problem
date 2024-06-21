/**
 * @file leetcode_2923.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/contest/weekly-contest-370/problems/find-champion-i/description/
 * @version 0.1
 * @date 2024-06-20
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
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
    int findChampion(vector<vector<int>>& grid) {
        int n = grid.size();
        for (int i{0}; i < n; ++i) {
            if (std::count(grid[i].begin(), grid[i].end(), 0) == 1) {
                return i;
            }
        }
        return -1;
    }
};