/**
 * @file leetcode_3072.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/distribute-elements-into-two-arrays-ii/?envType=daily-question&envId=2024-06-05
 * @version 0.1
 * @date 2024-06-05
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>

namespace OY {
template<typename Tp>
struct Discretizer : std::vector<Tp> {
    using std::vector<Tp>::vector;
    Discretizer& operator<<(const Tp& item) {
        std::vector<Tp>::push_back(item);
        return *this;
    }
    Discretizer& operator<<(const std::vector<Tp>& items) {
        std::vector<Tp>::insert(std::end(*this), items.begin(), items.end());
        return *this;
    }
    Discretizer& operator<<(const std::vector<std::vector<Tp>>& items) {
        for (auto& each : items) *this << each;
        return *this;
    }
    Discretizer& operator<<(const std::pair<Tp, Tp>& items) { return *this << items.first << items.second; }
    template<size_t N>
    Discretizer& operator<<(const std::array<Tp, N>& items) {
        std::vector<Tp>::insert(std::end(*this), items.begin(), items.end());
        return *this;
    }
    void prepare() {
        std::sort(std::begin(*this), std::end(*this));
        std::vector<Tp>::resize(std::unique(std::begin(*this), std::end(*this)) - std::begin(*this));
    }
    typename std::vector<Tp>::size_type rank(const Tp& item) { return std::distance(std::begin(*this), std::lower_bound(std::begin(*this), std::end(*this), item)); }
};
} // namespace OY

namespace OI::DataStructure {
// [l, r)
template<typename ValueType>
class Fenwick {
    using RangeType = long long;

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
    // get the sum [startPoint, p]
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
} // namespace OI::DataStructure

using namespace OI::DataStructure;
class Solution {
public:
    std::vector<int> resultArray(std::vector<int>& nums) {
        OY::Discretizer<int> D;
        D << nums;
        D.prepare();
        Fenwick<int> f1(0, D.size(), std::plus<int>());
        Fenwick<int> f2(0, D.size(), std::plus<int>());
        std::vector<int> arr1{nums[0]}, arr2{nums[1]};
        f1.modify(D.rank(nums[0]), 1);
        f2.modify(D.rank(nums[1]), 1);
        for (int i = 2; i < nums.size(); ++i) {
            int num = nums[i];
            int rank = D.rank(num);
            int g1 = arr1.size() - f1.query(rank);
            int g2 = arr2.size() - f2.query(rank);
            if (g1 > g2 || (g1 == g2 && arr1.size() <= arr2.size())) {
                arr1.push_back(num);
                f1.modify(rank, 1);
            } else {
                arr2.push_back(num);
                f2.modify(rank, 1);
            }
        }
        arr1.insert(arr1.end(), arr2.begin(), arr2.end());
        return arr1;
    }
};