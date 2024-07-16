/**
 * @file leetcode_2222.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/number-of-ways-to-select-buildings/
 * @version 0.1
 * @date 2024-07-15
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifdef Cattle_Horse
#include "leetcode.h" // IWYU pragma: keep
using namespace std;
#else
#define dbg(...) void(114514)
#endif

[[maybe_unused]] auto __init_io__ = []() {
    return std::cin.tie(nullptr)->sync_with_stdio(false);
}();

class Solution {
public:
    long long numberOfWays(string s) {
        int n = s.length();
        // 前后缀0的个数
        std::vector<int> pre(n), suf(n);
        pre[0] = s[0] == '0';
        for (auto i{1}; i < n; i += 1) {
            pre[i] = pre[i - 1] + (s[i] == '0');
        }
        suf[n - 1] = s[n - 1] == '0';
        for (auto i{n - 2}; i >= 0; i -= 1) {
            suf[i] = suf[i + 1] + (s[i] == '0');
        }
        dbg(pre, suf);
        long long ans = 0;
        // 枚举中间
        for (auto i{1}; i < n - 1; i += 1) {
            int left[2]{pre[i - 1], i - pre[i - 1]};
            int right[2]{suf[i + 1], n - i - 1 - suf[i + 1]};
            int p = (s[i] - '0') ^ 1;
            ans += left[p] + right[p];
        }
        return ans;
    }
};

#ifdef Cattle_Horse
int main() {
    dbg(Solution().numberOfWays("001101"));
}
#endif