/**
 * @file LCP_40.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/uOAnQW/description/
 * @version 0.1
 * @date 2024-06-21
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

[[maybe_unused]] auto __init_io__ = []() {
    return std::cin.tie(nullptr)->sync_with_stdio(false);
}();

class Solution {
public:
    // swap 前cnt中最小的偶数, 一个cnt之后的最大的奇数
    // 或者 前cnt中最小的一个奇数, 一个cnt之后的最大的偶数
    int maxmiumScore(vector<int>& cards, int cnt) {
        std::sort(cards.begin(), cards.end(), std::greater<int>());
        std::vector<int> a(cards.begin(), cards.begin() + cnt), b(cards.begin() + cnt, cards.end());
        int sum = std::accumulate(a.begin(), a.end(), 0);
        if (sum % 2 == 0) return sum;
        auto is_even = [](int x) {
            return x % 2 == 0;
        };
        auto is_odd = [](int x) {
            return x % 2 == 1;
        };
        int ans = 0;
        {
            auto last_even = std::find_if(a.rbegin(), a.rend(), is_even);
            auto first_odd = std::find_if(b.begin(), b.end(), is_odd);
            if (last_even != a.rend() && first_odd != b.end()) {
                ans = std::max(ans, sum - *last_even + *first_odd);
            }
        }
        {
            auto last_odd = std::find_if(a.rbegin(), a.rend(), is_odd);
            auto first_even = std::find_if(b.begin(), b.end(), is_even);
            if (last_odd != a.rend() && first_even != b.end()) {
                ans = std::max(ans, sum - *last_odd + *first_even);
            }
        }
        return ans;
    }
};

int main() {
    vector<int> cards{7, 4, 1};
    int cnt = 1;
    Solution().maxmiumScore(cards, cnt);
}