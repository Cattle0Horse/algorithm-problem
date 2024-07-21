/**
 * @file leetcode_402.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/remove-k-digits/
 * @version 0.1
 * @date 2024-07-17
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
    // 找到严格降序的数
    // 可以使用栈方便的找到前一个数
    string removeKdigits(string num, int k) {
        std::vector<char> stk;
        for (char c : num) {
            while (k > 0 && !stk.empty() && stk.back() > c) {
                stk.pop_back();
                --k;
            }
            stk.push_back(c);
        }
        while (k > 0 && !stk.empty()) {
            if (stk.back() == '0') return "0";
            stk.pop_back();
            --k;
        }
        auto begin = stk.begin();
        while (begin != stk.end() && *begin == '0') {
            ++begin;
        }
        return begin == stk.end() ? "0" : std::string(begin, stk.end());
    }
    // string removeKdigits(string num, int k) {
    //     for (auto it = num.begin() + 1; it != num.end();) {
    //         if (k > 0 && it != num.begin() && *std::prev(it) > *it) {
    //             it = num.erase(std::prev(it));
    //             --k;
    //         } else {
    //             ++it;
    //         }
    //     }
    //     std::string ans = std::string(num.begin(), num.begin() + num.size() - k);
    //     auto end = num.begin() + num.size() - k;
    //     auto begin = num.begin();
    //     while (begin != end && *begin == '0') {
    //         ++begin;
    //     }
    //     if (end - begin == 0) return "0";
    //     return std::string(begin, end);
    // }
};

#ifdef Cattle_Horse
int main() {
    //
}
#endif