/**
 * @file leetcode_1014.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/best-sightseeing-pair/description/
 * @version 0.1
 * @date 2024-06-20
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

[[maybe_unused]] auto _ = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();

class Solution {
public:
    int maxScoreSightseeingPair(vector<int>& values) {
        int ans{0};
        int mx{values[0] + 0};
        int n = values.size();
        for (int j{1}; j < n; ++j) {
            ans = std::max(ans, mx + values[j] - j);
            mx = std::max(mx, values[j] + j);
        }
        return ans;
    }
};