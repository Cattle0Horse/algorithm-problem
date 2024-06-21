/**
 * @file LCP_03.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/programmable-robot/description/
 * @version 0.1
 * @date 2024-06-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
#include <set>
#include <unordered_set>
#include <utility>
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
    bool robot(string command, vector<vector<int>>& obstacles, int x, int y) {
        std::set<std::pair<int, int>> s;
        int xx{0}, yy{0};
        s.insert({xx, yy});
        for (char c : command) {
            if (c == 'U') ++yy;
            else ++xx;
            s.insert({xx, yy});
        }
        // 判断(_x,_y)是否在command路径上
        auto contains = [&](int _x, int _y) {
            int loop_num = std::min(_x / xx, _y / yy);
            return s.contains({_x - loop_num * xx, _y - loop_num * yy});
        };
        if (!contains(x, y)) return false;
        for (auto&& obstacle : obstacles) {
            int ox{obstacle[0]}, oy{obstacle[1]};
            if (ox > x || oy > y) continue;
            if (contains(ox, oy)) return false;
        }
        return true;
    }
};