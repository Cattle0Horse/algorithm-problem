/**
 * @file fenwick.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief
 * @version 1.3
 * @date 2024-05-28
 * @last_modify 2024-07-20
 * @copyright Copyright (c) 2024
 *
 */

#include <cassert>
#include <cstddef>
#include <functional>
#include <vector>
#include <cstdint>

namespace OI::DataStructure {
// [l, r)
template<typename ValueType, typename RangeType = int32_t>
struct Fenwick {
public:
    using MergeFunctionType = std::function<ValueType(const ValueType&, const ValueType&)>;
    Fenwick() = default;
    Fenwick(RangeType leftRange, RangeType rightRange, MergeFunctionType merge, const ValueType& zeroValue = ValueType())
        : m_leftRange(leftRange), m_rightRange(rightRange),
          m_zeroValue(zeroValue), m_merge(merge),
          m_node(rightRange - leftRange + 1, zeroValue) {
        assert(leftRange <= rightRange);
    }
    Fenwick(RangeType rightRange, MergeFunctionType merge, const ValueType& zeroValue = ValueType())
        : Fenwick(0, rightRange, merge, zeroValue) {
        assert(rightRange >= 0);
    }
    template<typename InitFunctionType>
    Fenwick(RangeType leftRange, RangeType rightRange, InitFunctionType initFunc, MergeFunctionType merge, const ValueType& zeroValue = ValueType())
        : Fenwick(leftRange, rightRange, merge, zeroValue) {
        static_assert(std::is_convertible_v<InitFunctionType, std::function<ValueType(RangeType)>>, "initFunc must work as ValueType(RangeType)");
        for (size_t i{1}, n{m_node.size()}; i < n; ++i) {
            m_node[i] = std::move(m_merge(m_node[i], initFunc(i - 1 + m_leftRange)));
            size_t father = i + (i & -i);
            if (father < n) m_node[father] = std::move(m_merge(m_node[father], m_node[i]));
        }
    }
    template<typename InitFunctionType>
    Fenwick(RangeType rightRange, InitFunctionType initFunc, MergeFunctionType merge, const ValueType& zeroValue = ValueType())
        : Fenwick(0, rightRange, initFunc, merge, zeroValue) {
        assert(rightRange >= 0);
    }
    Fenwick(const std::vector<ValueType>& initValue, MergeFunctionType merge, RangeType startPoint = 0, const ValueType& zeroValue = ValueType())
        : Fenwick(startPoint, startPoint + initValue.size(), merge, zeroValue) {
        for (size_t i{1}, n{m_node.size()}; i < n; ++i) {
            m_node[i] = std::move(m_merge(m_node[i], initValue[i - 1]));
            size_t father = i + (i & -i);
            if (father < n) m_node[father] = std::move(m_merge(m_node[father], m_node[i]));
        }
    }
    void modify(RangeType p, const ValueType& v) {
        assert(m_leftRange <= p && p < m_rightRange);
        size_t n{m_node.size()};
        for (size_t x = p + 1 - m_leftRange; x < n; x += x & -x) {
            m_node[x] = std::move(m_merge(m_node[x], v));
        }
    }
    // get the sum [startPoint, p)
    ValueType pre(RangeType p) const {
        assert(m_leftRange <= p && p <= m_rightRange);
        ValueType ans{m_zeroValue};
        for (size_t x = p - m_leftRange; x > 0; x &= x - 1) {
            ans = std::move(m_merge(ans, m_node[x]));
        }
        return ans;
    }
    // get the sum [l, r)
    ValueType query(RangeType l, RangeType r) const {
        if (l >= r) return m_zeroValue;
        return pre(std::min(r, m_rightRange)) - pre(std::max(l, m_leftRange));
    }
    // get the date[p]
    ValueType query(RangeType p) const {
        assert(m_leftRange <= p && p < m_rightRange);
        return pre(std::min(p + 1, m_rightRange)) - pre(p);
    }

    // private:
    RangeType m_leftRange, m_rightRange;
    const ValueType m_zeroValue;
    MergeFunctionType m_merge;
    std::vector<ValueType> m_node;
};
template<typename Ostream, typename ValueType, typename RangeType>
Ostream& operator<<(Ostream& out, const Fenwick<ValueType, RangeType>& fenw) {
    out << "[";
    for (RangeType i = fenw.m_leftRange; i < fenw.m_rightRange; i += 1) {
        if (i != fenw.m_leftRange) out << ", ";
        out << fenw.query(i);
    }
    return out << "]";
}
} // namespace OI::DataStructure