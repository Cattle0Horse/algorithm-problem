/**
 * @file leetcode_520.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/detect-capital/
 * @version 0.1
 * @date 2024-04-29
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <algorithm>
#include <cctype>
#include <string>
class Solution {
public:
    bool detectCapitalUse(std::string word) {
        return std::find_if(word.begin(), word.end(), [](char c) {
                   return std::islower(c);
               }) == word.end() ||
               (std::find_if(word.begin(), word.end(), [](char c) {
                    return std::isupper(c);
                }) == word.end()) ||
               (std::isupper(word.front()) && std::find_if(word.begin() + 1, word.end(), [](char c) {
                                                  return std::isupper(c);
                                              }) == word.end());
    }
};