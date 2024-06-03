/**
 * @file leetcode_3170.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/lexicographically-minimum-string-after-removing-stars/description/
 * @version 0.1
 * @date 2024-06-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <map>
#include <string>
#include <vector>
class Solution {
public:
    std::string clearStars(std::string s) {
        std::map<char, std::vector<int>> stacks;
        int n = s.length();
        std::vector<bool> omit(n);
        for (int i{0}; i < n; ++i) {
            if (s[i] != '*') {
                stacks[s[i]].push_back(i);
            } else {
                for (auto&& [_, stack] : stacks) {
                    if (!stack.empty()) {
                        omit[stack.back()] = true;
                        stack.pop_back();
                        break;
                    }
                }
            }
        }
        std::string ans;
        for (int i{0}; i < n; ++i) {
            if (!omit[i] && s[i] != '*') {
                ans += s[i];
            }
        }
        return ans;
    }
};