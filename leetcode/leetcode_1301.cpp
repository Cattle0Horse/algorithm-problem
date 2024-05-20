/**
 * @file leetcode_1301.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/xor-queries-of-a-subarray/description/
 * @version 0.1
 * @date 2024-05-20
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <functional>
#include <numeric>
#include <vector>
class Solution {
public:
    std::vector<int> xorQueries(std::vector<int>& arr, std::vector<std::vector<int>>& queries) {
        std::vector<int> pre(arr.size() + 1), ans;
        std::partial_sum(arr.begin(), arr.end(), pre.begin() + 1, std::bit_xor<int>());
        ans.reserve(queries.size());
        for (auto&& q : queries) {
            ans.push_back(pre[q[1] + 1] ^ pre[q[0]]);
        }
        return ans;
    }
};