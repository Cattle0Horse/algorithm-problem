/**
 * @file leetcode_3115.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/maximum-prime-difference/?envType=daily-question&envId=2024-07-02
 * @version 0.1
 * @date 2024-07-02
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifdef OY_LOCAL
#include <vector>
#include <iostream>
using namespace std;
#endif

// [0, n]
std::vector<bool> sieve(size_t n) {
    if (n == 0) return std::vector<bool>(1, false);
    std::vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (size_t i = 2; i * i <= n; ++i) {
        if (is_prime[i]) {
            for (size_t j{i * i}; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return is_prime;
}

std::vector<bool> is_prime;
[[maybe_unused]] auto __init_io__ = []() {
    is_prime = sieve(100);
    return std::cin.tie(nullptr)->sync_with_stdio(false);
}();
class Solution {
public:
    int maximumPrimeDifference(vector<int>& nums) {
        int n = nums.size();
        int l = n, r = -1;
        for (auto i{0}; i < n; ++i) {
            if (is_prime[nums[i]]) {
                l = std::min(l, i);
                r = std::max(r, i);
            }
        }
        return r - l;
    }
};