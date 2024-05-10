/**
 * @file interview_16_21.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/sum-swap-lcci/
 * @version 0.1
 * @date 2024-05-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> findSwapValues(vector<int>& array1, vector<int>& array2) {
        int sum1 = std::accumulate(array1.begin(), array1.end(), 0);
        int sum2 = std::accumulate(array2.begin(), array2.end(), 0);
        std::sort(array1.begin(), array1.end());
        std::sort(array2.begin(), array2.end());
        int n = array1.size(), m = array2.size();
        for (int i = 0, j = 0; i < n && j < m;) {
            int x = sum1 - array1[i] + array2[j];
            int y = sum2 + array1[i] - array2[j];
            if (x == y) {
                return {array1[i], array2[j]};
            } else if (x < y) {
                j++;
            } else {
                i++;
            }
        }
        return {};
    }
};