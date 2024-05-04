/**
 * @file leetcode_1235.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/maximum-profit-in-job-scheduling/description/?envType=daily-question&envId=2024-05-04https://leetcode.cn/problems/maximum-profit-in-job-scheduling/description/?envType=daily-question&envId=2024-05-04
 * @version 0.1
 * @date 2024-05-04
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
#include <numeric>
#include <vector>

class Solution {
public:
    int jobScheduling(std::vector<int>& startTime, std::vector<int>& endTime, std::vector<int>& profit) {
        int n = startTime.size();
        std::vector<int> h(n);
        std::iota(h.begin(), h.end(), 0);
        std::sort(h.begin(), h.end(), [&](int i, int j) {
            if (endTime[i] != endTime[j]) {
                return endTime[i] < endTime[j];
            }
            if (startTime[i] != startTime[j]) {
                return startTime[i] < startTime[j];
            }
            return profit[i] < profit[j];
        });
        std::vector<int> dp(n);
        dp[0] = profit[h[0]];
        for (int i = 1; i < n; i++) {
            int l = -1, r = i;
            while (l + 1 < r) {
                int mid = (l + r) >> 1;
                if (endTime[h[mid]] <= startTime[h[i]]) {
                    l = mid;
                } else {
                    r = mid;
                }
            }
            if (l == -1) {
                dp[i] = profit[h[i]];
            } else {
                dp[i] = profit[h[i]] + dp[l];
            }
            dp[i] = std::max(dp[i], dp[i - 1]);
        }
        return dp.back();
    }
};