/**
 * @file leetcode_2435.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/paths-in-matrix-whose-sum-is-divisible-by-k/description/
 * @version 0.1
 * @date 2024-06-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <cstddef>
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
} // namespace OI

constexpr int mod = 1e9 + 7;

class Solution {
public:
    int numberOfPaths(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();
        OI::VVV<int> dp{OI::create_vvv<int>(m + 1, n + 1, k)};
        dp[0][1][0] = 1;
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                for (int v = 0; v < k; ++v)
                    dp[i + 1][j + 1][(v + grid[i][j]) % k] = (dp[i + 1][j][v] + dp[i][j + 1][v]) % mod;
        return dp[m][n][0];
    }
};