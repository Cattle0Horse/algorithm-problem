/**
 * @file leetcode_1529.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/minimum-suffix-flips/description/
 * @version 0.1
 * @date 2024-07-04
 *
 * @copyright Copyright (c) 2024
 *
 */

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
    // 从左至右翻转
    int minFlips(string target) {
        int ans = 0;
        for (char c : target) {
            if ((c - '0') != (ans & 1)) {
                ++ans;
            }
        }
        return ans;
    }
};