/**
 * @file leetcode_312.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/burst-balloons/description/?envType=daily-question&envId=2024-06-09
 * @version 0.1
 * @date 2024-06-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <functional>
#include <vector>

class Solution {
public:
    int maxCoins(std::vector<int>& nums) {
        int n = nums.size();
        nums.insert(nums.begin(), 1);
        nums.push_back(1);
        std::vector<std::vector<int>> memo(n + 2, std::vector<int>(n + 2, -1));
        // 添加气球
        std::function<int(int, int)> dfs = [&](int l, int r) {
            if (l > r) return 0;
            int& res = memo[l][r];
            if (res != -1) return res;
            for (int i{l}; i <= r; ++i) {
                // l和r间选择一个气球添加, 其左右两边的气球是l-1和r+1
                int sum = nums[i] * nums[l - 1] * nums[r + 1];
                sum += dfs(l, i - 1) + dfs(i + 1, r);
                res = std::max(res, sum);
            }
            return res;
        };
        return dfs(1, n);
    }
};