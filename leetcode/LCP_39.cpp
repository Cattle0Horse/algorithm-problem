/**
 * @file LCP_39.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/0jQkd0/description/
 * @version 0.1
 * @date 2024-06-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <array>
#include <cstdlib>
#include <numeric>
#include <unordered_map>
#ifdef OY_LOCAL
#include <vector>
#include <string>
#include <iostream>
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
    int minimumSwitchingTimes(vector<vector<int>>& source, vector<vector<int>>& target) {
        std::array<int, 10000 + 1> cnt;
        cnt.fill(0);
        int n = source.size(), m = source[0].size(), nm = n * m;
        for (int i{0}; i < nm; ++i) {
            ++cnt[source[i / m][i % m]];
            --cnt[target[i / m][i % m]];
        }
        return std::accumulate(cnt.begin(), cnt.end(), 0, [](int a, int b) {
            return a + (b > 0 ? b : 0);
        });
    }
};