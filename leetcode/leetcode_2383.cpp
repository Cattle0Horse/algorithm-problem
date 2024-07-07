/**
 * @file leetcode_2383.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/minimum-hours-of-training-to-win-a-competition/
 * @version 0.1
 * @date 2024-07-07
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
    // 题目说依次遇上对手 就简单很多
    int minNumberOfHours(int hp, int xp, vector<int>& energy, vector<int>& experience) {
        int n = energy.size();
        int ans = 0;
        for (auto i{0}; i < n; ++i) {
            int need_energy = std::max(0, energy[i] + 1 - hp);
            int need_experience = std::max(0, experience[i] + 1 - xp);
            ans += need_energy;
            ans += need_experience;
            hp += need_energy - energy[i];
            xp += need_experience - experience[i];
        }
        return ans;
    }
};