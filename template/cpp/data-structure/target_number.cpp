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