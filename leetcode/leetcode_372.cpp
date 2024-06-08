/**
 * @file leetcode_372.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/super-pow/description/
 * @version 0.1
 * @date 2024-06-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <vector>
class Solution {
private:
    constexpr static int MOD{1337};
    static int qpow(int a, int b) {
        int ans{1};
        for (a %= MOD; b != 0; b >>= 1, a = a * a % MOD)
            if (b & 1) ans = ans * a % MOD;
        return ans % MOD;
    }

public:
    // a^b = (a^10)^(b/10) * a^(b%10)
    int superPow(int a, std::vector<int>& b) {
        int ans = 1;
        for (int i = b.size() - 1; i >= 0; --i) {
            ans = ans * qpow(a, b[i]) % MOD;
            a = qpow(a, 10);
        }
        return ans;
    }
};