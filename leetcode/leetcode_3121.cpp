/**
 * @file leetcode_3121.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/count-the-number-of-special-characters-ii/?envType=problem-list-v2&envId=CpHNyXsu
 * @version 0.1
 * @date 2024-07-07
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <array>
#include <bit>
#include <cstdint>
#include <cstdio>
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
    int numberOfSpecialChars(string word) {
        uint32_t lower = 0, upper = 0, invalid = 0;
        for (char c : word) {
            uint32_t weight = 1u << (c & 31);
            // lower
            if ((c & 32) != 0) {
                lower |= weight;
                // 若大写字母在当前小写字母之前出现过, 则非法
                if (upper & weight) {
                    invalid |= weight;
                }
            } else {
                upper |= weight;
            }
        }
        return std::popcount(lower & upper & ~invalid);
    }
    // 记录大写字母出现的第一个位置
    //    小写字母出现的最后一个位置
    // int numberOfSpecialChars(string word) {
    //     int n = word.length();
    //     std::array<int, 26> upper_first{};
    //     upper_first.fill(n);
    //     std::array<int, 26> lower_last{};
    //     lower_last.fill(-1);
    //     for (auto i{0}; i < n; ++i) {
    //         char c = word[i];
    //         // lower
    //         if (c & 32) {
    //             int k = c - 'a';
    //             lower_last.at(k) = std::max(lower_last.at(k), i);
    //         } else {
    //             int k = c - 'A';
    //             upper_first.at(k) = std::min(upper_first.at(k), i);
    //         }
    //     }
    //     int ans = 0;
    //     for (auto i{0}; i < 26; ++i) {
    //         if (upper_first[i] != n && lower_last[i] != -1 && lower_last[i] < upper_first[i]) {
    //             ++ans;
    //         }
    //     }
    //     return ans;
    // }
};

int main() {
    Solution().numberOfSpecialChars("aaAbcBC");
}