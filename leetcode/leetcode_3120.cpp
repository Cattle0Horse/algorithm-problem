/**
 * @file leetcode_3120.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/count-the-number-of-special-characters-i/description/
 * @version 0.1
 * @date 2024-06-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <array>
#include <bit>
#include <cctype>
#include <cstdint>
#include <unordered_set>
#ifdef OY_LOCAL
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
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
    int numberOfSpecialChars(string word) {
        uint32_t has[2]{};
        for (char c : word) {
            has[c >> 5 & 1] |= 1 << (c & 31);
        }
        return std::popcount(has[0] & has[1]);
    }
};