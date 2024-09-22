// @date 2024/9/22 11:40:25
// @author Cattle_Horse (CattleHorse@duck.com)
// @problem 3298. 统计重新排列后包含另一个字符串的子字符串数目 II
// @link https://leetcode.cn/problems/count-substrings-that-can-be-rearranged-to-contain-a-string-ii/

#ifdef Cattle_Horse
#include "leetcode.h" // IWYU pragma: keep
using namespace std;
#else
#define dbg(...) void(114514)
#endif

[[maybe_unused]] auto __init_io__ = []() {
    return std::cin.tie(nullptr)->sync_with_stdio(false);
}();
/**
 * @file target_number.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief
 * @version 0.1
 * @date 2024-09-22
 * https://leetcode.cn/problems/count-substrings-that-can-be-rearranged-to-contain-a-string-ii/description/
 * https://leetcode.cn/problems/minimum-window-substring/
 * @copyright Copyright (c) 2024
 *
 * 用于判断目标字符串是否可以由给定的字符重新排列组成
 * 即只需拥有足够的目标数量
 */

#include <string>
#include <type_traits>
#include <unordered_map>

template<typename ValueType = char, typename SizeType = int>
struct TargetNumber {
    using value_type = ValueType;
    using size_type = SizeType;
    std::unordered_map<value_type, size_type> need;
    size_type less;

    TargetNumber() = delete;
    template<typename Iterator>
    TargetNumber(Iterator begin, Iterator end) {
        for (; begin != end; ++begin) need[*begin] += 1;
        less = need.size();
    }
    TargetNumber(const std::string& target): TargetNumber(target.begin(), target.end()) {
        static_assert(std::is_same<value_type, char>::value, "Only char type is supported.");
    }
    TargetNumber(const std::vector<value_type>& target): TargetNumber(target.begin(), target.end()) {}
    /**
     * 获得字符，减少需要的个数
     */
    void acquire(const value_type& v, size_type cnt = 1) {
        auto before = need[v];
        need[v] -= cnt;
        if (before > 0 && need[v] <= 0) {
            less -= 1;
        }
    }
    /**
     * 释放字符，增加需要的个数(请确保释放的是通过acquire方法获得的字符)
     */
    void release(const value_type& v, size_type cnt = 1) {
        auto before = need[v];
        need[v] += cnt;
        if (before <= 0 && need[v] > 0) {
            less += 1;
        }
    }
    /**
     * 判断需要的字符是否足够
     */
    bool enough() const { return less == 0; }
};

class Solution {
public:
    long long validSubstringCount(string word1, string word2) {
        TargetNumber<char> need(word2);
        long long ans = 0;
        int l = 0;
        for (char c : word1) {
            need.acquire(c);
            while (need.enough()) need.release(word1[l++]);
            ans += l;
        }
        return ans;
    }
};

// long long Solution::validSubstringCount(string word1, string word2)

#ifdef Cattle_Horse
int main() {
    std::cout << "*** 3298. 统计重新排列后包含另一个字符串的子字符串数目 II ***" << std::endl
              << std::endl;

    Solution s0;

    {
        std::cout << "Test 1: ";

        string word1 = "bcca";
        string word2 = "abc";
        long long ans0 = s0.validSubstringCount(word1, word2);
        long long exp0 = 1;

        if (ans0 == exp0) {
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
            std::cout << "  Answer: " << ans0 << std::endl;
            std::cout << "  Expect: " << exp0 << std::endl;
        }
    }

    {
        std::cout << "Test 2: ";

        string word1 = "abcabc";
        string word2 = "abc";
        long long ans1 = s0.validSubstringCount(word1, word2);
        long long exp1 = 10;

        if (ans1 == exp1) {
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
            std::cout << "  Answer: " << ans1 << std::endl;
            std::cout << "  Expect: " << exp1 << std::endl;
        }
    }

    {
        std::cout << "Test 3: ";

        string word1 = "abcabc";
        string word2 = "aaabc";
        long long ans2 = s0.validSubstringCount(word1, word2);
        long long exp2 = 0;

        if (ans2 == exp2) {
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
            std::cout << "  Answer: " << ans2 << std::endl;
            std::cout << "  Expect: " << exp2 << std::endl;
        }
    }

    return 0;
}
#endif