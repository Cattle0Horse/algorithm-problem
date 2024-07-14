/**
 * @file leetcode_204.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/count-primes/description/
 * @version 0.1
 * @date 2024-07-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifdef OY_LOCAL
#include "leetcode.h" // IWYU pragma: keep
using namespace std;
#else
#define dbg(...) void(114514)
#endif

[[maybe_unused]] auto __init_io__ = []() {
    return std::cin.tie(nullptr)->sync_with_stdio(false);
}();

constexpr int N = 5e6;
int cnt[N + 1];
[[maybe_unused]] auto __init__ = []() {
    std::ranges::fill(cnt, 1);
    cnt[0] = cnt[1] = 0;
    for (size_t i = 2; i * i <= N; ++i) {
        if (cnt[i]) {
            for (size_t j{i * i}; j <= N; j += i) {
                cnt[j] = 1;
            }
        }
    }
    for (size_t i = 1; i <= N; ++i) {
        cnt[i] += cnt[i - 1];
    }
    dbg(cnt);
    return 0;
}();
class Solution {
public:
    int countPrimes(int n) {
        return n != 0 ? cnt[n - 1] : 0;
    }
};

#ifdef OY_LOCAL
int main() {
    dbg(Solution().countPrimes(10));;
    //
}
#endif