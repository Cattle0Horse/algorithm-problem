/**
 * @file LCP_01.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/guess-numbers/description/
 * @version 0.1
 * @date 2024-06-21
 *
 * @copyright Copyright (c) 2024
 *
 */
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
    int game(vector<int>& guess, vector<int>& answer) {
        int n = guess.size(), ans = 0;
        for (int i{0}; i < n; ++i) {
            ans += guess[i] == answer[i];
        }
        return ans;
    }
};