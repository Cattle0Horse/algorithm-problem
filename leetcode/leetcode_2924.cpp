/**
 * @file leetcode_2924.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/contest/weekly-contest-370/problems/find-champion-ii/description/
 * @version 0.1
 * @date 2024-06-20
 *
 * @copyright Copyright (c) 2024
 *
 */
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
    int findChampion(int n, vector<vector<int>>& edges) {
        std::vector<int> degree(n);
        for (auto&& edge : edges) {
            int a{edge[0]}, b{edge[1]};
            ++degree[b];
        }
        int ans = -1;
        for (int i{0}; i < n; ++i) {
            if (degree[i] == 0) {
                if (ans != -1) return -1;
                ans = i;
            }
        }
        return ans;
    }
};