/**
 * @file leetcode_2521.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/distinct-prime-factors-of-product-of-array/description/
 * @version 0.1
 * @date 2024-07-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <concepts>
#include <cstddef>
#include <unordered_map>
#include <unordered_set>
#include <utility>
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

// template<std::integral T>
template<typename T>
std::vector<std::pair<T, size_t>> getFactorsWithCnt(T n) {
    std::vector<std::pair<T, size_t>> ans;
    for (T i{2}; i * i <= n; ++i) {
        if (n % i == 0) {
            int cnt = 0;
            while (n % i == 0) n /= i, ++cnt;
            ans.emplace_back(i, cnt);
        }
    }
    if (n != 1) ans.emplace_back(n, 1);
    return ans;
}
// template<std::integral T>
template<typename T>
std::vector<T> getFactors(T n) {
    std::vector<T> ans;
    for (T i{2}; i * i <= n; ++i) {
        if (n % i == 0) {
            while (n % i == 0) n /= i;
            ans.push_back(i);
        }
    }
    if (n != 1) ans.push_back(n);
    return ans;
}

class Solution {
public:
    int distinctPrimeFactors(vector<int>& nums) {
        std::unordered_set<int> set;
        for (int num : nums) {
            for (int factor : getFactors(num)) {
                set.insert(factor);
            }
        }
        return set.size();
    }
};