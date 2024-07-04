/**
 * @file leetcode_942.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/di-string-match/
 * @version 0.1
 * @date 2024-07-04
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
#include <numeric>
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
    vector<int> diStringMatch(string s) {
        int n = s.length();
        std::vector<int> ans;
        ans.reserve(n + 1);
        int l = 0, r = n;
        for (char c : s) {
            if (c == 'I') {
                ans.push_back(l++);
            } else {
                ans.push_back(r--);
            }
        }
        ans.push_back(l);
        return ans;
    }
};