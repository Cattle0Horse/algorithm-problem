/**
 * @file leetcode_1981.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/minimize-the-difference-between-target-and-chosen-elements/
 * @version 0.1
 * @date 2024-06-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
#include <bitset>
#include <cstdlib>
#include <limits>
#include <vector>
class Solution {
public:
    int minimizeTheDifference(std::vector<std::vector<int>>& mat, int target) {
        constexpr static int N = 70 * 70;
        using BitType = std::bitset<N + 1>;
        int n = mat.size(), m = mat.front().size();
        BitType last;
        last.set(0);

        for (auto&& row : mat) {
            BitType temp;
            for (int v : row) {
                temp |= last << v;
            }
            last = std::move(temp);
        }

        int ans = std::numeric_limits<int>::max();
        for (int i{0}; i <= N; ++i) {
            if (last.test(i)) {
                ans = std::min(ans, std::abs(i - target));
            }
        }
        return ans;
    }
};