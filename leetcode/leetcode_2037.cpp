/**
 * @file leetcode_2037.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/minimum-number-of-moves-to-seat-everyone/
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
    int minMovesToSeat(vector<int>& seats, vector<int>& students) {
        std::ranges::sort(seats);
        std::ranges::sort(students);
        int n = seats.size();
        for (auto i{0}; i < n; ++i) {
            
        }


    }
};