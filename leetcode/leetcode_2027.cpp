/**
 * @file leetcode_2027.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/minimum-moves-to-convert-string/description/
 * @version 0.1
 * @date 2024-07-04
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
    int minimumMoves(string s) {
        // [0, covered] 已经被覆盖过
        int ans{0}, n = s.length(), covered = -1;
        for (auto i{0}; i < n; ++i) {
            if (s[i] == 'X' && i > covered) {
                ++ans;
                covered = i + 2;
            }
        }
        return ans;
    }

    // int minimumMoves(string s) {
    //     int ans{0}, n = s.length();
    //     for (auto i{0}; i < n; ++i) {
    //         if (s[i] == 'X') {
    //             ++ans;
    //             for (int j = std::min(n, i + 3) - 1; j >= i; --j) {
    //                 if (s[j] == 'X') {
    //                     s[j] = 'O';
    //                 }
    //             }
    //         }
    //     }
    //     return ans;
    // }
};