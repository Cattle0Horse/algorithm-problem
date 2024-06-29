/**
 * @file leetcode_2710.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/remove-trailing-zeros-from-a-string/description/?envType=daily-question&envId=2024-06-29
 * @version 0.1
 * @date 2024-06-29
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <string>
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
    string removeTrailingZeros(string s) {
        return string(s.begin(), s.begin() + s.find_last_not_of('0'));
    }
};