/**
 * @file leetcode_1289.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/minimum-falling-path-sum-ii/description/
 * @version 0.1
 * @date 2024-06-21
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <algorithm>
#include <limits>
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
    int minFallingPathSum(vector<vector<int>>& grid) {
        int n = grid.size();
        std::vector<int> dp(grid[0]);
        for (int i{1}; i < n; ++i) {
            auto pre{dp};
            for (int j{0}; j < n; ++j) {
                int mn = std::numeric_limits<int>::max();
                for (int k{0}; k < n; ++k) {
                    if (k != j) {
                        mn = std::min(mn, pre[k]);
                    }
                }
                dp[j] = mn + grid[i][j];
            }
        }
        return *std::min_element(dp.begin(), dp.end());
    }
};
class Solution2 {
public:
    // 记录前一行的最小值和次小值, 判断当前下标是否等于前一行最小值的下标
    // 如果等于, 则返回次小只
    // 否则返回最小值
    int minFallingPathSum(vector<vector<int>>& grid) {
        
        constexpr static int inf = std::numeric_limits<int>::max();
        int n = grid.size();
        int first_val = 0, first_index = -1, second_val = 0;
        for (int i{0}; i < n; ++i) {
            int pre_first_val = first_val, pre_first_index = first_index, pre_second_val = second_val;
            first_val = inf, first_index = -1, second_val = inf;
            for (int j{0}; j < n; ++j) {
                int cur_val = grid[i][j] + (j == pre_first_index ? pre_second_val : pre_first_val);
                if (cur_val < first_val) {
                    second_val = first_val;
                    first_index = j;
                    first_val = cur_val;
                } else if (cur_val < second_val) {
                    second_val = cur_val;
                }
            }
        }
        return first_val;
    }
};