/**
 * @file leetcode_2589.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/minimum-time-to-complete-all-tasks/description/
 * @version 0.1
 * @date 2024-06-20
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
#include <array>
#ifdef OY_LOCAL
#include <vector>
#include <string>
#include <iostream>
using namespace std;
#endif

[[maybe_unused]] auto _ = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();

/**
 * @file fenwick_v1.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief
 * @version 1.2
 * @date 2024-05-28
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <cassert>
#include <cstddef>
#include <functional>
#include <vector>

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
        : startPoint(_leftRange), zeroValue(_zeroValue), merge(_merge),
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
            size_t father = i + (i & -i);
            if (father < n) node[father] = merge(node[father], node[i]);
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
private:
    constexpr static int N = 2000;

public:
    // 排序后, 逆序遍历, 尽量在一个区间的左边运行
    int findMinimumTime(vector<vector<int>>& tasks) {
        std::sort(tasks.begin(), tasks.end(), [](const auto& a, const auto& b) {
            return a[1] < b[1];
        });
        Fenwick<int> f(1, N + 1, std::plus<int>(), 0);
        std::array<bool, N + 1> has;
        has.fill(false);
        int n = tasks.size(), ans = 0;
        for (int i = n - 1; i >= 0; --i) {
            int l = tasks[i][0], r = tasks[i][1], d = tasks[i][2];
            // [l, r]
            int need = d - (f.query(r) - f.query(l - 1));
            for (; l <= r && need > 0; ++l) {
                if (has[l]) continue;
                ++ans;
                --need;
                has[l] = true;
                f.modify(l, 1);
            }
        }
        return ans;
    }
};