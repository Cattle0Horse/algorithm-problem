/**
 * @file leetcode_229.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/majority-element-ii/
 * @version 0.1
 * @date 2024-06-28
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <cstdint>
#include <unordered_map>
#ifdef OY_LOCAL
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
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
    vector<int> majorityElement(vector<int>& nums) {
        return majority(nums, 3);
    }
    // 时间复杂度 O(n)
    // 空间复杂度 O(k)
    template<typename T>
    vector<int> majority(const vector<T>& nums, uint32_t k) {
        // 存在[0, k-1]个水王
        // (值, 血量)
        std::unordered_map<T, uint32_t> m(k - 1);
        for (auto&& num : nums) {
            if (m.contains(num) || m.size() < k - 1) {
                ++m[num];
            } else {
                // 全部消去一个
                for (auto it{m.begin()}; it != m.end();) {
                    --(it->second);
                    if (it->second == 0) {
                        it = m.erase(it);
                    } else {
                        ++it;
                    }
                }
            }
        }
        for (auto&& [_, cnt] : m) {
            cnt = 0;
        }
        for (auto&& num : nums) {
            ++m[num];
        }
        std::vector<int> ans;
        auto n{nums.size() / k};
        for (auto&& [num, cnt] : m) {
            if (cnt > n) {
                ans.push_back(num);
            }
        }
        return ans;
    }
};