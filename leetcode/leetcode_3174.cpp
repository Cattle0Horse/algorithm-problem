/**
 * @file leetcode_3174.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/clear-digits/description/
 * @version 0.1
 * @date 2024-06-16
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <cctype>
#include <string>
class Solution {
public:
    std::string clearDigits(std::string s) {
        std::string stack;
        for (char c : s) {
            if (std::isdigit(c)) {
                stack.pop_back();
            } else {
                stack.push_back(c);
            }
        }
        return stack;
    }
};