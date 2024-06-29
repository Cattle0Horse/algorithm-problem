/**
 * @file leetcode_853.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/car-fleet/description/
 * @version 0.1
 * @date 2024-06-29
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifdef OY_LOCAL
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;
#endif

[[maybe_unused]] auto __init_io__ = []() {
    return std::cin.tie(nullptr)->sync_with_stdio(false);
}();

class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        int n = position.size();
        std::vector<int> index(n);
        std::iota(index.begin(), index.end(), 0);
        std::ranges::sort(index, [&](int i, int j) {
            return position[i] < position[j];
        });
        // 可以追上j的车数
        int cnt = 0;
        for (auto j{0}; j < n; ++j) {
            int i = index[j];
            int pos = position[i], spd = speed[i];

        }
    }
};