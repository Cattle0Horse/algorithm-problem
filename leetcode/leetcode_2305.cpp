/**
 * @file leetcode_2305.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/fair-distribution-of-cookies/
 * @version 0.1
 * @date 2024-06-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
#include <bit>
#include <cstdint>
#include <limits>
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
    // 将cookie拆成k份, 使得这k份的最大值 最小
    int distributeCookies(vector<int>& cookies, int k) {
        int n = cookies.size();
        uint32_t S = (1u << n) - 1;
        // sum[s] : 一个孩子获得状态为s的饼干的饼干价值和
        std::vector<int> sum(S + 1);
        sum[0] = 0;
        for (auto i{1u}; i <= S; ++i) {
            sum[i] = sum[i & (i - 1)] + cookies[std::countr_zero(i)];
        }
        // dp[i][j] : i个孩子分配状态为s的饼干的最小不公平程度
        // 新增一个孩子分配j状态的饼干
        // dp[i][j] = min( x -> max(dp[i-1][j ^ x], sum[x] ) ) x 为j的子集
        OI::VV<int> dp{OI::create_vv<int>(k, S + 1)};
        dp[0] = sum;
        for (int i{1}; i < k; ++i) {
            for (auto j{0u}; j <= S; ++j) {
                // 将集合 j 分成两个集合
                dp[i][j] = OI::for_each_subset(j,
                                        [&](uint32_t s) { return std::max(dp[i - 1][s ^ j], sum[s]); },
                                        [](int a, int b) { return std::min(a, b); },
                                        std::numeric_limits<int>::max());
            }
        }
        return dp[k - 1][S];
    }
};