/**
 * @file leetcode_2981.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/find-longest-special-substring-that-occurs-thrice-i/description/?envType=daily-question&envId=2024-05-29
 * @version 0.1
 * @date 2024-05-29
 *
 * @copyright Copyright (c) 2024
 *
 */

// 定义s(n)为 由n个相同字符组成的字符串
// s(n)可以提供n-i+1个s(i), 其中 1 <= i <= n

// 每增加一个相同字符, [1, cnt]都可以多提供一个
// 差分数组实现区间加
#include <algorithm>
#include <array>
#include <string>
#include <vector>
class Solution {
private:
    constexpr static int K{3};

public:
    int maximumLength(std::string s) {
        int n = s.length();
        std::array<std::vector<int>, 26> groups;
        groups.fill(std::vector<int>(n + 2));
        for (int i{0}, x{0}; i < n; ++i) {
            x++;
            // [1, x]区间+1
            groups[s[i] - 'a'][1] += 1;
            groups[s[i] - 'a'][x + 1] -= 1;
            if (i + 1 < n && s[i] != s[i + 1]) {
                x = 0;
            }
        }
        int ans = -1;
        for (auto& cnt : groups) {
            for (int i = 1; i <= n; ++i) {
                cnt[i] += cnt[i - 1];
                if (cnt[i] >= K) {
                    ans = std::max(ans, i);
                } else {
                    break;
                }
            }
        }
        return ans;
    }
};
