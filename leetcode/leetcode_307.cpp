/**
 * @file leetcode_307.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/range-sum-query-mutable/description/
 * @version 0.1
 * @date 2024-05-28
 *
 * @copyright Copyright (c) 2024
 *
 */

/**
 * @file fenwick_v1.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief
 * @version 1.0
 * @date 2024-05-28
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <cassert>
#include <cstddef>
#include <functional>
#include <utility>
#include <vector>

namespace OI::DataStructure::Fenwick {
using RangeType = long long;
// [l, r)
template<typename ValueType>
class Fenwick {
public:
    using MergeFunctionType = std::function<ValueType(const ValueType&, const ValueType&)>;
    Fenwick() = default;
    Fenwick(RangeType _leftRange, RangeType _rightRange,
            MergeFunctionType _merge,
            const ValueType& _zeroValue = ValueType())
        : startPoint(_leftRange), merge(_merge), zeroValue(_zeroValue),
          node(_rightRange - _leftRange + 1, _zeroValue) {
        assert(_leftRange <= _rightRange);
    }
    Fenwick(const std::vector<ValueType>& _initValue,
            MergeFunctionType _merge,
            RangeType _startPoint = 0,
            const ValueType& _zeroValue = ValueType())
        : Fenwick(_startPoint, _startPoint + _initValue.size(), _merge, _zeroValue) {
        for (size_t i{1}, n{node.size()}; i < n; ++i) {
            node[i] = merge(node[i], _initValue[i - 1]);
            int father = i + (i & -i);
            if (father < n) {
                node[father] += node[i];
            }
        }
        // for (size_t i{0}, n = _initValue.size(); i < n; ++i) {
        //     modify(static_cast<RangeType>(i) + _startPoint, _initValue[i]);
        // }
    }
    void modify(RangeType p, const ValueType& v) {
        size_t n{node.size()};
        for (size_t x = p - startPoint + 1; x < n; x += x & -x) {
            node[x] = merge(node[x], v);
        }
    }
    ValueType query(RangeType p) {
        ValueType ans{zeroValue};
        for (size_t x = p - startPoint + 1; x > 0; x &= x - 1) {
            ans = merge(ans, node[x]);
        }
        return ans;
    }

private:
    RangeType startPoint;
    ValueType zeroValue;
    MergeFunctionType merge;
    std::vector<ValueType> node;
};
} // namespace OI::DataStructure::Fenwick

using namespace OI::DataStructure::Fenwick;

class NumArray {
private:
    Fenwick<int> fenwick;
    std::vector<int> nums;

public:
    NumArray(std::vector<int>& nums): nums(nums), fenwick(nums, std::plus<int>()) {}

    void update(int index, int val) {
        fenwick.modify(index, val - std::exchange(nums[index], val));
    }

    int sumRange(int left, int right) {
        return fenwick.query(right) - (left == 0 ? 0 : fenwick.query(left - 1));
    }
};