/**
 * @file leetcode_2499.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/minimum-number-of-operations-to-make-arrays-similar/description/
 * @version 0.1
 * @date 2024-07-04
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
#include <array>
#include <cstdlib>
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
    long long makeSimilar(vector<int>& nums, vector<int>& target) {
        std::ranges::sort(nums);
        std::ranges::sort(target);
        std::array<std::vector<int>, 2> tars{};
        std::array<int, 2> indexes{};
        for (int x : target) {
            tars[x & 1].push_back(x);
        }
        long long ans = 0;
        for (int x : nums) {
            std::vector<int>& tar{tars[x & 1]};
            int& index{indexes[x & 1]};
            ans += std::abs(x - tar[index]) / 2;
            ++index;
        }
        return ans / 2;
    }
};