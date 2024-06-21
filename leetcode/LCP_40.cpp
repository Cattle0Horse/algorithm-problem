/**
 * @file LCP_40.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/uOAnQW/description/
 * @version 0.1
 * @date 2024-06-21
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <algorithm>
#include <array>
#include <functional>
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
    int maxmiumScore(vector<int>& cards, int cnt) {
        std::sort(cards.begin(), cards.end(), std::greater<int>());
        std::array<std::vector<int>, 2> nums;
        for (int card : cards) {
            nums[card & 1].push_back(card);
        }
        int i = 0, j = 0;
        
    }
};