/**
 * @file leetcode_2064.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/minimized-maximum-of-products-distributed-to-any-store/
 * @version 0.1
 * @date 2024-07-01
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
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
    // 最小化 最大值 二分答案
    int minimizedMaximum(int n, vector<int>& quantities) {
        int m = quantities.size();
        auto check = [&](int maximum) -> bool {
            int store_size = 0;
            for (int quantity : quantities) {
                // 每一个物品会占用 quantity / maximum (上取整) 个商店
                store_size += (quantity + maximum - 1) / maximum;
                if (store_size > n) {
                    return false;
                }
            }
            return true;
        };
        int last_false = 0, first_true = std::ranges::max(quantities) + 1;
        while (last_false + 1 < first_true) {
            int mid = (last_false + first_true) >> 1;
            if (check(mid)) {
                first_true = mid;
            } else {
                last_false = mid;
            }
        }
        return first_true;
    }
};