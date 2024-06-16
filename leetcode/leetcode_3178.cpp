/**
 * @file leetcode_3178.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/find-the-child-who-has-the-ball-after-k-seconds/description/
 * @version 0.1
 * @date 2024-06-16
 *
 * @copyright Copyright (c) 2024
 *
 */

class Solution {
public:
    int numberOfChild(int n, int k) {
        if (n == 1) return 0;
        if (n == 2) return k % 2;
        k %= (n - 2) * 2 + 2;
        if (k < n) {
            return k;
        }
        // 花 n - 1 步走到最后
        k -= n - 1;
        return n - 1 - k;
    }
};