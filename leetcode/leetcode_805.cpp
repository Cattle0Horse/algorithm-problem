/**
 * @file leetcode_805.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/split-array-with-same-average/
 * @version 0.1
 * @date 2024-06-05
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>
#include <cstdlib>
#include <functional>
#include <vector>

namespace OI::Math {
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
} // namespace OI::Math

using namespace OI::Math;

class Solution {
public:
    bool splitArraySameAverage(std::vector<int>& nums) {
        int m = nums.size();
        if (m == 1) return false;

        int lsize = m >> 1, rsize = m - lsize;
        int sum = std::accumulate(nums.begin(), nums.end(), 0);
        auto leftSum{Combinations<int>::get_subsequence_set_count(nums.begin(), nums.begin() + lsize)};
        auto rightSum{Combinations<int>::get_subsequence_set_count(nums.begin() + lsize, nums.end())};
        for (auto& left : leftSum) std::sort(left.begin(), left.end());
        for (auto& right : rightSum) std::sort(right.begin(), right.end());

        // 枚举left中,选择放入A数组中的个数
        for (int lcnt{0}; lcnt <= lsize; ++lcnt) {
            // Asum * Bcnt == Bsum * Acnt
            // Asum * (m-Acnt) == (sum - Asum) * Acnt
            // Asum*m - Asum*Acnt == sum*Acnt - Asum*Acnt
            // Asum*m == sum*Acnt
            auto& left{leftSum[lcnt]};
            for (int rcnt{0}; rcnt <= rsize; ++rcnt) {
                if ((lcnt == 0 && rcnt == 0) || (lcnt == lsize && rcnt == rsize)) continue;
                auto& right{rightSum[rcnt]};
                int l = 0, r = right.size() - 1, expRight = sum * (lcnt + rcnt);
                while (l < left.size() && r >= 0) {
                    int expLeft = (left[l] + right[r]) * m;
                    if (expLeft == expRight) return true;
                    if (expLeft < expRight) {
                        ++l;
                    } else {
                        --r;
                    }
                }
            }
        }
        return false;
    }
};