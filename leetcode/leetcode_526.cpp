/**
 * @file leetcode_526.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/beautiful-arrangement/
 * @version 0.1
 * @date 2024-05-29
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <functional>
#include <vector>
class Solution {
private:
    constexpr static int INIT = -1;

public:
    int countArrangement(int n) {
        int m{1 << (n + 1)};
        std::vector<std::vector<int>> memo(n + 1, std::vector<int>(m, INIT));
        std::function<int(int, int)> dfs = [&](int index, int s) {
            if (index == n + 1) {
                return 1;
            }
            int& p = memo[index][s];
            if (p != INIT) return p;
            int ans = 0;
            for (int i = 1; i <= n; ++i) {
                if ((s >> i & 1) && (index % i == 0 || i % index == 0)) {
                    ans += dfs(index + 1, s ^ (1 << i));
                }
            }
            return p = ans;
        };
        return dfs(1, m - 1);
    }
};