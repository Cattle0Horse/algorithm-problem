/**
 * @file leetcode_2410.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/maximum-matching-of-players-with-trainers/description/
 * @version 0.1
 * @date 2024-07-03
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <algorithm>
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
    int matchPlayersAndTrainers(vector<int>& players, vector<int>& trainers) {
        std::ranges::sort(players);
        std::ranges::sort(trainers);
        int i = 0, n = trainers.size();
        int ans = 0;
        for (int v : players) {
            while (i < n && v > trainers[i]) ++i;
            if (i < n) {
                ++ans;
                ++i;
            }
        }
        return ans;
    }
};