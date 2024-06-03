/**
 * @file leetcode_2397.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/maximum-rows-covered-by-columns
 * @version 0.1
 * @date 2024-05-31
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
#include <vector>

// Gosper's Hack : https://zhuanlan.zhihu.com/p/360512296
// https://programmingforinsomniacs.blogspot.com/2018/03/gospers-hack-explained.html
/*
int m = 1<<n
for (auto i{(1u << k) - 1}; i < m; i = next_k_subset(i)) {
    // Any i contains k ones
    ...
}
*/
#define next_k_subset(i) (((i ^ (i + (i & -i))) >> (std::countr_zero(i & -i) + 2)) | (i + (i & -i)))

class Solution {
public:
    int maximumRows(std::vector<std::vector<int>>& matrix, int numSelect) {
        int m = matrix.size(), n = matrix.front().size();
        std::vector<int> mask(m);
        for (int i{0}; i < m; ++i) {
            for (int j{0}; j < n; ++j) {

                mask[i] |= matrix[i][j] << j;
            }
        }

        int ans = 0;
        for (auto i = (1u << numSelect) - 1, s = 1u << n; i < s; i = next_k_subset(i)) {
            ans = std::max(ans, static_cast<int>(std::count_if(mask.begin(), mask.end(), [&](int v) {
                               return (v & i) == v;
                           })));
        }
        return ans;
    }
};
