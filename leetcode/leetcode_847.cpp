/**
 * @file leetcode_847.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/shortest-path-visiting-all-nodes/description/
 * @version 0.1
 * @date 2024-06-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <cstdint>
#include <limits>
#include <queue>
#include <utility>
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

constexpr int inf = std::numeric_limits<int>::max();

class Solution {
public:
    int shortestPathLength(vector<vector<int>>& g) {
        int n = g.size();
        uint32_t m = (1 << n) - 1;
        auto dis{OI::create_vv(n, m + 1, inf)};
        std::queue<std::pair<int, uint32_t>> q;
        for (int i{0}; i < n; ++i) {
            q.emplace(i, m & ~(1 << i));
            dis[i][m & ~(1 << i)] = 0;
        }
        while (!q.empty()) {
            auto [u, s] = q.front();
            q.pop();
            int step = dis[u][s];
            if (s == 0) return step;
            for (int v : g[u]) {
                int vs = s & ~(1 << v);
                if (dis[v][vs] == inf) {
                    dis[v][vs] = step + 1;
                    q.emplace(v, vs);
                }
            }
        }
        return -1;
    }
};