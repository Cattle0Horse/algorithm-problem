/**
 * @file leetcode_521.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/longest-uncommon-subsequence-i/description/
 * @version 0.1
 * @date 2024-06-16
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <algorithm>
#include <string>
class Solution {
public:
    int findLUSlength(std::string a, std::string b) {
        return a == b ? -1 : std::max(a.length(), b.length());
    }
};