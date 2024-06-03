/**
 * @file leetcode_1521.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/find-a-value-of-a-mysterious-function-closest-to-target/
 * @version 0.1
 * @date 2024-06-02
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <algorithm>
#include <cstdlib>
#include <vector>
class Solution {
public:
    int closestToTarget(std::vector<int>& arr, int target) {
        int ans = 1e9, n = arr.size();
        for (int i = 0; i < n; ++i) {
            // arr[j] = arr[j...i] & sum
            // when arr[j] is the subset of arr[i], arr[0]~arr[j] all are the subset of arr[i]
            // loop can break
            for (int j = i - 1; j >= 0; --j) {
                if ((arr[i] & arr[j]) == arr[j]) break;
                ans = std::min(ans, std::abs(target - (arr[j] &= arr[i])));
            }
            ans = std::min(ans, std::abs(target - arr[i]));
        }
        return ans;
    }
};