/**
 * @file leetcode_826.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/most-profit-assigning-work/description/?envType=daily-question&envId=2024-05-17
 * @version 0.1
 * @date 2024-05-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <algorithm>
#include <numeric>
#include <vector>

class Solution {
public:
    int maxProfitAssignment(std::vector<int>& difficulty, std::vector<int>& profit, std::vector<int>& worker) {
        int n = difficulty.size();
        std::vector<int> id(n);
        std::iota(id.begin(), id.end(), 0);
        std::sort(id.begin(), id.end(), [&](int x, int y) {
            return difficulty[x] < difficulty[y];
        });
        std::sort(worker.begin(), worker.end());
        int i = 0, maxProfit = 0, ans = 0;
        for (int w : worker) {
            while (i < n && difficulty[id[i]] <= w) {
                maxProfit = std::max(maxProfit, profit[id[i]]);
            }
            ans += maxProfit;
        }
        return ans;
    }
};