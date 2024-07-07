/**
 * @file leetcode_890.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/find-and-replace-pattern/description/
 * @version 0.1
 * @date 2024-07-07
 *
 * @copyright Copyright (c) 2024
 *
 */

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
/**
 * @file bit_counter.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief
 * @version 0.1
 * @date 2024-06-25
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <array>
#include <cstdint>

class Solution {
public:
    std::vector<int> getKey(const std::string& s) {
        static std::array<int, 26> cnt{};
        cnt.fill(0);
        for (char c : s) {
            cnt[c - 'a'] += 1;
        }
        std::vector<int> ans;
        for (int v : cnt) {
            if (v != 0) {
                ans.push_back(0);
            }
        }
        std::ranges::sort(ans);
        return ans;
    }
    vector<string> findAndReplacePattern(vector<string>& words, string pattern) {
        std::vector<std::string> ans;
        auto target{getKey(pattern)};
        for (auto&& word : words) {
            if (getKey(word) == target) {
                ans.push_back(word);
            }
        }
        return ans;
    }
};