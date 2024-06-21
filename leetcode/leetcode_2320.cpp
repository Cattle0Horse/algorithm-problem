/**
 * @file leetcode_2320.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/count-number-of-ways-to-place-houses/description/
 * @version 0.1
 * @date 2024-06-21
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

constexpr int mod = 1e9 + 7;
constexpr int N = 1e4;
int f[N + 1]{1, 2};
[[maybe_unused]] auto _ = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    for (int i{2}; i <= N; ++i) {
        f[i] = (f[i - 1] + f[i - 2]) % mod;
    }
    return 0;
}();

class Solution {
public:
    int countHousePlacements(int n) {
        return static_cast<long long>(f[n]) * f[n] % mod;
    }
};