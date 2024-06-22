/**
 * @file leetcode_2787.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/ways-to-express-an-integer-as-sum-of-powers/description/
 * @version 0.1
 * @date 2024-06-22
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

[[maybe_unused]] auto _ = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();
template<typename T>
T qpow(T a, T b) {
    T ans{1};
    for (; b != 0; a *= a, b >>= 1)
        if (b & 1) ans *= a;
    return ans;
}
constexpr int MOD = 1e9 + 7;
class Solution {
public:
    int numberOfWays(int n, int p) {
        std::vector<int> nums;
        for (int i = 1, num; (num = qpow(i, p)) <= n; ++i) {
            nums.push_back(num);
        }
        std::vector<int> dp(n + 1);
        dp[0] = 1;
        for (int num : nums) {
            for (auto x{n}; x >= num; --x) {
                dp[x] = (dp[x] + dp[x - num]) % MOD;
            }
        }
        return dp[n];
    }
};