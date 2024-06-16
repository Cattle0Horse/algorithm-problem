/**
 * @file leetcode_3175.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/find-the-first-player-to-win-k-games-in-a-row/description/
 * @version 0.1
 * @date 2024-06-16
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <vector>
class Solution {
public:
    int findWinningPlayer(std::vector<int>& skills, int k) {
        int n = skills.size();
        int cnt = 0, index = 0;
        for (int i{1}; i < n; ++i) {
            if (skills[i] > skills[index]) {
                cnt = 1;
                index = i;
            } else {
                ++cnt;
            }
            if (cnt == k) {
                return index;
            }
        }
        return index;
    }
};