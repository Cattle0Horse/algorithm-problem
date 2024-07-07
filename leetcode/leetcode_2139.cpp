/**
 * @file leetcode_2139.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/minimum-moves-to-reach-target-score/description/?envType=problem-list-v2&envId=CpHNyXsu
 * @version 0.1
 * @date 2024-07-07
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <bit>
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
    // 逆推
    // 如果target为奇数, 则只能由target-1得来
    // 否则, 由于是从大到小, 越大的数字用来翻倍能节省更多操作
    //      因此能翻倍则翻倍, 如果没有翻倍次数了, 则直接返回剩余数字到1的操作次数
    int minMoves(int target, int maxDoubles) {
        int ans = 0;
        while (target != 1) {
            if (target & 1) {
                target -= 1;
                ans += 1;
            } else {
                if (maxDoubles == 0) {
                    ans += target - 1;
                    break;
                } else {
                    target >>= 1;
                    maxDoubles -= 1;
                    ans += 1;
                }
            }
        }
        return ans;
    }
};