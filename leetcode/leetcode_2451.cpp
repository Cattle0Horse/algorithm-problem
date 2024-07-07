/**
 * @file leetcode_2451.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/odd-string-difference/
 * @version 0.1
 * @date 2024-07-06
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <unordered_map>
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
    string oddString(vector<string>& words) {
        int m = words.size();
        int n = words[0].length();
        for (int j{1}; j < n; ++j) {
            std::unordered_map<int, int> diff;
            for (int i{0}; i < m; ++i) {
                ++diff[words[i][j] - words[i][j - 1]];
            }
            if (diff.size() == 2) {
                for (int i{0}; i < m; ++i) {
                    if (diff[words[i][j] - words[i][j - 1]] == 1) {
                        return words[i];
                    }
                }
            }
        }
        return "";
    }
};