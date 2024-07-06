/**
 * @file leetcode_2571.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/minimum-operations-to-reduce-an-integer-to-0/description/
 * @version 0.1
 * @date 2024-07-04
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifdef OY_LOCAL
#include <vector>
#include <iostream>
using namespace std;
#endif

[[maybe_unused]] auto __init_io__ = []() {
    return std::cin.tie(nullptr)->sync_with_stdio(false);
}();

class Solution {
public:
    // 如果存在连续的1, 则可以添加最低位的1使其进位变成只有1个1
    int minOperations(int n) {
        int ans = 0;
        for (auto i{0}; i < 31;) {
            if (n >> i & 1) {
                int j = i + 1;
                while (j < 31 && (n >> j & 1)) ++j;
                // [i, j) 都是1
                if (j - i >= 2) {
                    i = j;
                    n |= 1 << j;
                } else {
                    ++i;
                }
                ++ans;
            } else {
                ++i;
            }
        }
        return ans;
    }
};