/**
 * @file leetcode_2404.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/most-frequent-even-element/description/
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

class Solution {
public:
    constexpr static int N = 1e5 + 1;
    int mostFrequentEven(vector<int>& nums) {
        std::array<int, N> cnt{};
        for (int v : nums) ++cnt[v];
        int ans = -1;
        for (int i = 0; i < N; i += 2) {
            if (cnt[i] > 0 && (ans == -1 || cnt[i] > cnt[ans])) {
                ans = i;
            }
        }
        return ans;
    }
};

#ifdef OY_LOCAL
int main() {
    //
}
#endif