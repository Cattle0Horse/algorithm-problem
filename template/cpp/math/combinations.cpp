/**
 * @file combination.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief
 * @version 1.0
 * @date 2024-06-05
 *
 * @copyright Copyright (c) 2024
 * 折半搜索
 * https://leetcode.cn/problems/partition-array-into-two-arrays-to-minimize-sum-difference/description/
 * https://leetcode.cn/problems/closest-subsequence-sum/description/
 * 用于求解一组数的子集的运算结果表
 * 如 arr={1,3,5}, op = std::plus<>();
 * 则返回
 * 0,
 * 1, 3, 5,
 * 4, 6, 8,
 * 9
 */

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
