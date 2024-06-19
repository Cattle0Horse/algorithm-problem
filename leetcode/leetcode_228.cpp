/**
 * @file leetcode_228.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/summary-ranges/description/
 * @version 0.1
 * @date 2024-06-17
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifdef OY_LOCAL
#include <vector>
#include <string>
#include <iostream>
using namespace std;
#endif

[[maybe_unused]] auto _ = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();

class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        std::vector<std::string> ans;
        std::vector<int> temp;
        auto push = [&]() {
            ans.emplace_back(temp.size() == 1u ? std::to_string(temp.front()) : std::to_string(temp.front()) + "->" + std::to_string(temp.back()));
            temp.clear();
        };
        for (int num : nums) {
            if (!temp.empty() && temp.back() != num - 1) {
                push();
            }
            temp.push_back(num);
        }
        if (!temp.empty()) push();
        return ans;
    }
};