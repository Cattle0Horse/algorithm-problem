/**
 * @file leetcode_1755.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/closest-subsequence-sum/
 * @version 0.1
 * @date 2024-06-05
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
#include <bit>
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <iterator>
#include <limits>
#include <vector>

template<typename ValueType>
class Combinations {
    using size_type = uint32_t;
    using operator_type = std::function<ValueType(const ValueType&, const ValueType&)>;

public:
    template<typename RandomAccessIterator>
    static std::vector<ValueType> get_subsequence_set(RandomAccessIterator first, RandomAccessIterator last, operator_type op = std::plus<ValueType>(), const ValueType& zero_value = ValueType()) {
        size_type n = std::distance(first, last), S = 1 << n;
        std::vector<ValueType> subsequence_set(S, zero_value);
        for (size_type s{1u}; s < S; ++s) {
            subsequence_set[s] = op(subsequence_set[s & (s - 1)], *(first + std::countr_zero(s)));
        }
        return subsequence_set;
    }
    template<typename RandomAccessIterator>
    static std::vector<std::vector<ValueType>> get_subsequence_set_count(RandomAccessIterator first, RandomAccessIterator last, operator_type op = std::plus<ValueType>(), const ValueType& zero_value = ValueType()) {
        size_type n = std::distance(first, last), S = 1 << n;
        std::vector<std::vector<ValueType>> result(n + 1);
        result[0].push_back(zero_value);
        std::vector<ValueType> temp(S, zero_value);
        for (size_type s{1u}; s < S; ++s) {
            temp[s] = op(temp[s & (s - 1)], *(first + std::countr_zero(s)));
            result[std::popcount(s)].push_back(temp[s]);
        }
        return result;
    }
};

class Solution {
public:
    int minAbsDifference(std::vector<int>& nums, int goal) {
        int m = nums.size(), leftSize = m >> 1, rightSize = m - leftSize;
        // 折半, 左半选一些, 记录所有情况, 排序
        // 枚举右半, 二分(或双指针)找到最接近goal的和
        std::vector<int> leftSum{Combinations<int>::get_subsequence_set(nums.begin(), nums.begin() + leftSize)};
        std::vector<int> rightSum{Combinations<int>::get_subsequence_set(nums.begin() + leftSize, nums.end())};
        std::sort(leftSum.begin(), leftSum.end());
        std::sort(rightSum.begin(), rightSum.end());
        int ans{std::numeric_limits<int>::max()};
        int l = 0, r = rightSum.size() - 1;
        while (l < leftSum.size() && r >= 0) {
            int s = leftSum[l] + rightSum[r];
            ans = std::min(ans, std::abs(goal - s));
            if (s > goal) {
                --r;
            } else {
                ++l;
            }
        }
        return ans;
    }
};