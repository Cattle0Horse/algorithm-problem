/**
 * @file leetcode_2374.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/node-with-highest-edge-score/
 * @version 0.1
 * @date 2024-07-07
 *
 * @copyright Copyright (c) 2024
 *
 */

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

class Solution {
public:
    int edgeScore(vector<int>& edges) {
        int n = edges.size();
        std::vector<int> score(n);
        for (auto i{0}; i < n; ++i) {
            score[edges[i]] += i;
        }
        int ans = 0;
        for (auto i{1}; i < n; ++i) {
            if (score[i] > score[ans]) {
                ans = i;
            }
        }
        return ans;
    }
};