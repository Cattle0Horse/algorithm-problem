/**
 * @file leetcode_2035.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/partition-array-into-two-arrays-to-minimize-sum-difference/description/
 * @version 0.1
 * @date 2024-06-05
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
#include <cstdlib>
#include <functional>
#include <limits>
#include <numeric>
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
    int minimumDifference(std::vector<int>& nums) {
        int m = nums.size(), n = m >> 1;
        int totalSum = std::accumulate(nums.begin(), nums.end(), 0);
        // int lsum = std::accumulate(nums.begin(), nums.begin() + n, 0);
        // int rsum = std::accumulate(nums.begin() + n, nums.end(), 0);
        // 折半, 各自在arr1中的和
        std::vector<std::vector<int>> leftSum{Combinations<int>::get_subsequence_set_count(nums.begin(), nums.begin() + n)};
        std::vector<std::vector<int>> rightSum{Combinations<int>::get_subsequence_set_count(nums.begin() + n, nums.end())};
        for (auto& left : leftSum) {
            std::sort(left.begin(), left.end());
        }
        for (auto& right : rightSum) {
            std::sort(right.begin(), right.end());
        }
        int ans = std::numeric_limits<int>::max();
        // 枚举左半部分选择在arr1中的个数
        for (int lcnt{0}; lcnt <= n; ++lcnt) {
            auto& left{leftSum[lcnt]};
            auto& right{rightSum[n - lcnt]};
            // sum1 = leftSum[.] + rightSum[.]
            // sum2 = totalSum - sum1;
            // 使得 abs(sum2-sum1) = abs(total-2*(left+right)) 最小
            int l = 0, r = right.size() - 1;
            while (l < left.size() && r >= 0) {
                int s = left[l] + right[r];
                ans = std::min(ans, std::abs(totalSum - 2 * s));
                if (totalSum == 2 * s) {
                    return 0;
                }
                if (totalSum > 2 * s) {
                    l++;
                } else {
                    r--;
                }
            }
        }
        return ans;
    }
};