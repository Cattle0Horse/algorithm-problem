/**
 * @file leetcode_2086.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/minimum-number-of-food-buckets-to-feed-the-hamsters/description/
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
    // 如果存在连续三个仓鼠, 则不能够喂养所有
    // 每遇到一个仓鼠, 在其右边放置食物桶(这才可能让后面的仓鼠吃这个食物), 如果右边不是空位, 则只能在左边放置
    int minimumBuckets(string hamsters) {
        int n = hamsters.length();
        int covered = -1, ans = 0;
        for (auto i{0}; i < n; ++i) {
            if (covered >= i) continue;
            if (hamsters[i] == 'H') {
                // 尝试在右边放食物
                if (i + 1 < n && hamsters[i + 1] == '.') {
                    covered = i + 2;
                    ++ans;
                } else {
                    // 尝试在左边放食物
                    if (i - 1 >= 0 && hamsters[i - 1] == '.') {
                        covered = i;
                        ++ans;
                    } else {
                        break;
                    }
                }
            }
        }
        return ans;
    }
};