/**
 * @file leetcode_1296.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/divide-array-in-sets-of-k-consecutive-numbers/
 * @version 0.1
 * @date 2024-06-29
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

// premise: the arr in [begin, end) is ordered
//    {1, 1, 2, 3, 3, 3, 3, 3, 3}
// -> {{1, 2}, {2, 1}, {3, 6}}
template<typename T, typename Iterator>
std::vector<std::pair<T, int>> toPairCount(Iterator begin, Iterator end) {
    std::vector<std::pair<T, int>> res;
    // [left, begin)
    for (Iterator left = begin; begin != end; left = begin) {
        while (begin != end && *begin == *left) ++begin;
        res.emplace_back(*left, static_cast<int>(std::distance(left, begin)));
    }
    return res;
}

class Solution {
public:
    bool isPossibleDivide(vector<int>& nums, int k) {
        if (nums.size() % k != 0) return false;
        std::ranges::sort(nums);
        auto arr{toPairCount<int>(nums.begin(), nums.end())};
        int n = arr.size();
        for (auto i{0}; i < n; ++i) {
            auto [val, cnt] = arr[i];
            if (cnt == 0) continue;
            if (i + k - 1 >= n) return false;
            for (auto j{1}; j < k; ++j) {
                auto& [nv, nc] = arr[i + j];
                if (nv != val + j || nc < cnt) return false;
                nc -= cnt;
            }
        }
        return true;
    }
};