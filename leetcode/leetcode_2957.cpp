/**
 * @file leetcode_2957.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/remove-adjacent-almost-equal-characters/description/
 * @version 0.1
 * @date 2024-07-04
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <cstdlib>
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
    // 不需要知道一个字符具体变成什么
    // 如果两个相邻字符近似i, i+1相等, 那么应该改变后面那个i+1(这样才能使得i+1与i+2非近似相等, 一定可以)
    int removeAlmostEqualCharacters(string word) {
        int n = word.length();
        int ans = 0;
        for (auto i{0}; i < n - 1;) {
            if (std::abs(word[i] - word[i + 1]) <= 1) {
                ++ans;
                i += 2;
            } else {
                i += 1;
            }
        }
        return ans;
    }
};