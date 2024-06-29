/**
 * @file leetcode_2653.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/sliding-subarray-beauty/
 * @version 0.1
 * @date 2024-06-28
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <map>
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

class Solution {
public:
    vector<int> getSubarrayBeauty(vector<int>& nums, int k, int x) {
        int n = nums.size();
        std::vector<int> ans;
        ans.reserve(n - k + 1);
        std::map<int, int> cnt{};
        auto fk = [&]() {
            int _x = x;
            for (auto&& [key, val] : cnt) {
                if (key >= 0) break;
                _x -= val;
                if (_x <= 0) return key;
            }
            return 0;
        };
        for (auto i{0}; i < n; ++i) {
            int num = nums[i];
            ++cnt[num];
            if (i >= k - 1) {
                ans.push_back(fk());
                --cnt[nums[i - k + 1]];
            }
        }
        return ans;
    }
};