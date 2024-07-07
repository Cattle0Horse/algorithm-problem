/**
 * @file leetcode_1823.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/find-the-winner-of-the-circular-game/description/
 * @version 0.1
 * @date 2024-07-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifdef OY_LOCAL
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;
#endif

[[maybe_unused]] auto __init_io__ = []() {
    return std::cin.tie(nullptr)->sync_with_stdio(false);
}();

class Solution {
public:
    // 逆推(下标从0开始)
    // f(n, m)
    // 每删去一个人 等同于数组向左移动m位
    // a, b, c, d, e, f
    //       |
    // d, e, f, a, b
    // 每一步%n, 从头开始计数(这个n是当前人数个数)
    // int f(int n, int m) {
    //     if (n == 1) return 0;
    //     return (f(n - 1, m) + m) % n;
    // }
    int f(int n, int m) {
        int ans = 0;
        for (int i = 2; i <= n; ++i) {
            ans = (ans + m) % i;
        }
        return ans;
    }
    int findTheWinner(int n, int k) {
        return f(n, k) + 1;
    }
};