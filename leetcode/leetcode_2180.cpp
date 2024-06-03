/**
 * @file leetcode_2180.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/count-integers-with-even-digit-sum/
 * @version 0.1
 * @date 2024-05-31
 *
 * @copyright Copyright (c) 2024
 *
 */

class Solution {
public:
    int countEven(int num) {
        // calculate the number of x in [1, num] that digit(x) is even
        // digit(x) is the sum of all digits for x
        auto digit = [](int x) {
            int sum = 0;
            for (; x > 0; x /= 10) {
                sum += x % 10;
            }
            return sum;
        };
        int ans = 0;
        for (int i{1}; i <= num; ++i) {
            if (digit(i) % 2 == 0) {
                ++ans;
            }
        }
        return ans;
    }
};