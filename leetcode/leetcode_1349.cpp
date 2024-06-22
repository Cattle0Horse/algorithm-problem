/**
 * @file leetcode_1349.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/maximum-students-taking-exam/
 * @version 0.1
 * @date 2024-06-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
#include <bit>
#include <cstdint>
#include <functional>
#include <numeric>
#ifdef OY_LOCAL
#include <vector>
#include <iostream>
using namespace std;
#endif

[[maybe_unused]] auto _ = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();

namespace OI {
template<typename ValueType>
using V = std::vector<ValueType>;
template<typename ValueType>
using VV = std::vector<std::vector<ValueType>>;
template<typename ValueType>
using VVV = std::vector<std::vector<std::vector<ValueType>>>;

template<typename ValueType>
VV<ValueType> create_vv(size_t n, size_t m, const ValueType& init_value) { return VV<ValueType>(n, V<ValueType>(m, init_value)); }
template<typename ValueType>
VV<ValueType> create_vv(size_t n, size_t m) { return VV<ValueType>(n, V<ValueType>(m)); }
template<typename ValueType>
VVV<ValueType> create_vvv(size_t n, size_t m, size_t k, const ValueType& init_value) { return VVV<ValueType>(n, VV<ValueType>(m, V<ValueType>(k, init_value))); }
template<typename ValueType>
VVV<ValueType> create_vvv(size_t n, size_t m, size_t k) { return VVV<ValueType>(n, VV<ValueType>(m, V<ValueType>(k))); }

template<typename F>
void for_each_subset(uint32_t S, F f) {
    uint32_t s = 0;
    do {
        f(s);
        s = (s - 1) & S;
    } while (s != 0u);
}
template<typename R, typename F, typename SF>
R for_each_subset(uint32_t S, F f, SF sf, R init) {
    uint32_t s = 0;
    do {
        init = sf(std::move(init), f(s));
        s = (s - 1) & S;
    } while (s != 0u);
    return init;
}
} // namespace OI

class Solution {
public:
    int maxStudents(vector<vector<char>>& seats) {
        int m = seats.size(), n = seats[0].size();
        std::vector<uint32_t> mask(m);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (seats[i][j] == '.') {
                    mask[i] |= 1u << j;
                }
            }
        }
        // dp[i][s]: 第i行, 座位状态为s时的最大学生人数
        std::vector<int> dp(1 << n);
        for (int i{0}; i < m; ++i) {
            auto pre{dp};
            // 枚举当前行座位选择情况
            OI::for_each_subset(mask[i], [&](uint32_t s) {
                // 只看不出现相邻座位的情况
                if ((s & (s << 1)) != 0) {
                    dp[s] = 0;
                    return;
                }
                // 上一行可以坐下的位置, 枚举其子集, 求子集中的最大值
                uint32_t mask2 = (i == 0 ? 0 : mask[i - 1] & ~((s << 1) | (s >> 1)));
                int ans = OI::for_each_subset(mask2,
                                            [&](uint32_t k) { return pre[k]; },
                                            [](int a, int b) { return std::max(a, b); },
                                            0);
                // 加上当前行的座位个数
                dp[s] = ans + std::popcount(s);
            });
        }
        return ranges::max(dp);
    }
};