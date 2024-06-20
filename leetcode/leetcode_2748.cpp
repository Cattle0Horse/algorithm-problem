/**
 * @file leetcode_2748.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/number-of-beautiful-pairs/description/?envType=daily-question&envId=2024-06-20
 * @version 0.1
 * @date 2024-06-20
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <array>
#include <numeric>
#include <unordered_map>
#ifdef OY_LOCAL
#include <vector>
#include <string>
#include <iostream>
using namespace std;
#endif

[[maybe_unused]] auto _ = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();

class Solution {
    int get_first(int a) {
        while (a >= 10) {
            a /= 10;
        }
        return a;
    }

public:
    int countBeautifulPairs(vector<int>& nums) {
        // pns[i] : 与i互质的数
        std::array<std::vector<int>, 10> pns;
        for (int i{1}; i < 10; ++i) {
            for (int j{1}; j < 10; ++j) {
                if (std::gcd(i, j) == 1) {
                    pns[i].push_back(j);
                }
            }
        }
        std::array<int, 10> cnt;
        cnt.fill(0);
        int ans{0};
        for (int num : nums) {
            for (int p : pns[num % 10]) {
                ans += cnt[p];
            }
            ++cnt[get_first(num)];
        }
        return ans;
    }
};