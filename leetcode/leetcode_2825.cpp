/**
 * @file leetcode_2825.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/make-string-a-subsequence-using-cyclic-increments/description/
 * @version 0.1
 * @date 2024-07-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <array>
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
    char next_char(char c) {
        return (c - 'a' + 1) % 26 + 'a';
    }
    // 贪心, 尽可能的匹配
    bool canMakeSubsequence(string str1, string str2) {
        int n = str2.length();
        int index = 0;
        for (char c : str1) {
            index += (c == str2[index] || next_char(c) == str2[index]);
            if (index == n) return true;
        }
        return false;
    }
};