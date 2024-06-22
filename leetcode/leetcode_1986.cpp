/**
 * @file leetcode_1986.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief
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
template<typename T>
using V = std::vector<T>;
template<typename T>
using VV = V<V<T>>;
template<typename T>
using VVV = V<VV<T>>;

template<typename T>
VV<T> create_vv(size_t n, size_t m, const T& init_value) { return VV<T>(n, V<T>(m, init_value)); }
template<typename T>
VV<T> create_vv(size_t n, size_t m) { return VV<T>(n, V<T>(m)); }
template<typename T>
VVV<T> create_vvv(size_t n, size_t m, size_t k, const T& init_value) { return VVV<T>(n, VV<T>(m, V<T>(k, init_value))); }
template<typename T>
VVV<T> create_vvv(size_t n, size_t m, size_t k) { return VVV<T>(n, VV<T>(m, V<T>(k))); }

template<typename F>
void for_each_nonempty_subset(uint32_t S, F f) {
    for (uint32_t s{S}; s != 0; s = (s - 1) & S) {
        f(s);
    }
}
template<typename R, typename F, typename SF>
R for_each_nonempty_subset(uint32_t S, F f, SF sf, R init) {
    for (uint32_t s{S}; s != 0; s = (s - 1) & S) {
        init = sf(std::move(init), f(s));
    }
    return init;
}
} // namespace OI

constexpr int inf = std::numeric_limits<int>::max();

class Solution {
public:
    // 将 tasks 分成 x 份, 每一份的和小于等于sessionTime, 求最小的x
    int minSessions(vector<int>& tasks, int sessionTime) {
        int n = tasks.size();
        uint32_t S = (1 << n) - 1;
        // sum[s]:状态为s的和
        std::vector<int> sum(S + 1);
        for (uint32_t i{1u}; i <= S; ++i) {
            sum[i] = sum[i & (i - 1)] + tasks[std::countr_zero(i)];
        }
        // dp[s]:状态为s时最少需要分成多少组
        std::vector<int> dp(S + 1, n);
        dp[0] = 0;
        for (uint32_t s{1u}; s <= S; ++s) {
            OI::for_each_nonempty_subset(s, [&](uint32_t sub) {
                if (sum[sub] <= sessionTime) {
                    dp[s] = std::min(dp[s], dp[s ^ sub] + 1);
                }
            });
        }
        return dp[S];
    }
};