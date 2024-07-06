/**
 * @file leetcode_3111.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/minimum-rectangles-to-cover-points/description/
 * @version 0.1
 * @date 2024-07-04
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
#include <map>
#ifdef OY_LOCAL
#include <vector>
#include <iostream>
using namespace std;
#endif

[[maybe_unused]] auto __init_io__ = []() {
    return std::cin.tie(nullptr)->sync_with_stdio(false);
}();

class Solution {
public:
    int minRectanglesToCoverPoints(vector<vector<int>>& points, int w) {
        std::ranges::sort(points);
        int n = points.size(), start = points[0][0], ans{0};
        for (auto i{0}; i < n; ++i) {
            if (points[i][0] - start > w) {
                start = points[i][0];
                ++ans;
            }
        }
        return ans + 1;
    }
};