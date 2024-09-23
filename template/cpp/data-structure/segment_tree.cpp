/**
 * @file segment_tree.cpp
 * @author Cattle_Horse (cattle_horse@qq.com)
 *
 * @brief  you need to implement two function and specify the type of value and the type of modification:
 * 1.(Function)merge       : It will combine the results of the two subsegment(Just like when you call the `query` method).
 *                           You still need to satisfy where `merge(valueZero, x) == x` and `merge(x, valueZero) == x`
 *                           for any possible value x(For example, for addition there is `merge(7, 0) == 7`,
 *                                                                 for taking the maximum value `merge(9, -INF) = 9`)
 *
 * 2.(Function)update      : It will use `mod` to modify `node`.
 *                           If lazy propagation is needed(when rangeModify is true), you also need to update `node.mod`.
 *
 * 3.(Type)value_type      : supports the = operator.
 *                           has default constructor.
 *                           Give the value of valueZero when constructing the segment tree (otherwise it will use the default constructor of ValueType).
 *
 * 4.(Type)ModificationType: supports the = operator.
 *                           has default constructor.
 *                           Give the value of valueZero when constructing the segment tree (otherwise it will use the default constructor of ModificationType).
 *
 * 5.(long long)_startPoint: Map of line segment tree indexes, this can help you pass in a vector with an initial index of 0 no matter what
 *                           Simply put, you can define _startPoint as the left boundary of your query range(It supports negative ranges)
 *
 * 6.(bool)rangeModify     : If you do not need range modification, please set `rangeModify` to false
 *
 * @version 1.4
 * @date 2024-04-22
 * @lastmodify 2024-07-20
 * @copyright Copyright (c) 2024
 * fork from  @link{https://github.com/ouuan/CPTH/blob/master/docs/SegmentTree.md}
 */
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <vector>

namespace OI::DataStructure {
namespace SegmentTreeDetails {
template<typename ValueType, typename ModificationType, typename RangeType = int32_t, typename SizeType = uint32_t>
struct SegmentTreeNode {
    using value_type = ValueType;
    using modification_type = ModificationType;
    using range_type = RangeType;
    using size_type = SizeType;
    // the id of the root is 1(default)
    size_type id;
    // the left and right represent for the subsegment [left, right) of the node
    range_type left, right;
    value_type val;
    modification_type mod;
};
template<typename Ostream, typename ValueType, typename ModificationType, typename RangeType, typename SizeType>
Ostream& operator<<(Ostream& out, const SegmentTreeNode<ValueType, ModificationType, RangeType, SizeType>& node) {
    return out << "{id: " << node.id << ", left: " << node.left << ", right: " << node.right << ", val: " << node.val << ", mod: " << node.mod << "}";
}
template<typename ValueType, typename ModificationType, bool RangeModify = true, typename RangeType = int32_t, typename SizeType = uint32_t>
class SegmentTree {
public:
    using value_type = ValueType;
    using modification_type = ModificationType;
    using range_type = RangeType;
    using size_type = SizeType;
    using node_type = SegmentTreeNode<value_type, modification_type, range_type, size_type>;
    using merge_function_type = std::function<value_type(const value_type&, const value_type&)>;
    using update_function_type = std::function<void(node_type&, const modification_type&)>;
    constexpr static bool range_modify() { return RangeModify; }

    SegmentTree() = default;
    SegmentTree(const std::vector<value_type>& _initValue,
                merge_function_type _mergeNode, update_function_type _updateMod,
                range_type _startPoint = 0, const value_type& _valueZero = value_type(),
                const modification_type& _modZero = modification_type()) {
        init(_initValue, _mergeNode, _updateMod, _startPoint, _valueZero, _modZero);
    }

    template<typename BuildFunctionType>
    SegmentTree(BuildFunctionType _buildFunc, merge_function_type _mergeNode, update_function_type _updateMod,
                range_type _leftRange, range_type _rightRange,
                const value_type& _valueZero = value_type(),
                const modification_type& _modZero = modification_type())
        : m_mergeNode(_mergeNode), m_updateMod(_updateMod),
          m_leftRange(_leftRange), m_rightRange(_rightRange),
          m_valueZero(_valueZero), m_modZero(_modZero) {
        static_assert(std::is_convertible_v<BuildFunctionType, std::function<void(value_type&, range_type)>>,
                      "buildFunc must work as void(value_type&, range_type)");
        assert(m_leftRange <= m_rightRange);
        m_nodes.resize((m_rightRange - m_leftRange) << 1);
        funcBuild(1, _leftRange, _rightRange, _buildFunc);
    }

    void init(const std::vector<value_type>& _initValue,
              merge_function_type _mergeNode, update_function_type _updateMod,
              range_type _startPoint = 0, const value_type& _valueZero = value_type(),
              const modification_type& _modZero = modification_type()) {
        assert(_startPoint >= std::numeric_limits<range_type>::min() / 2);
        assert(_startPoint <= std::numeric_limits<range_type>::max() / 2 - static_cast<range_type>(_initValue.size()));
        m_leftRange = _startPoint;
        m_rightRange = _startPoint + _initValue.size();
        m_init(_initValue, _mergeNode, _updateMod, _valueZero, _modZero);
    }

    void modify(range_type l, range_type r, const modification_type& mod) {
        static_assert(RangeModify, "RangeModify Must Be True");
        assert(m_leftRange <= l && l <= r && r <= m_rightRange);
        modify(1, m_leftRange, m_rightRange, l, r, mod);
    }

    void modify(range_type p, const modification_type& mod) {
        assert(m_leftRange <= p && p < m_rightRange);
        modify(1, m_leftRange, m_rightRange, p, p + 1, mod);
    }

    value_type query(range_type l, range_type r) const {
        return query(1, m_leftRange, m_rightRange, l, r);
    }

    value_type query(range_type p) const {
        return query(p, p + 1);
    }

private:
    void pushUp(size_type cur, range_type x, range_type y) {
        m_nodes[cur].val = m_mergeNode(m_nodes[x].val, m_nodes[y].val);
    }

    void pushDown(size_type cur, range_type x, range_type y) const {
        // if RangeModify is true, then m_nodes[x].mod and m_nodes[y].mod must be modified together
        m_updateMod(m_nodes[x], m_nodes[cur].mod);
        m_updateMod(m_nodes[y], m_nodes[cur].mod);
        m_nodes[cur].mod = m_modZero;
    }

    void build(size_type cur, range_type l, range_type r, const std::vector<value_type>& initValue) {
        m_nodes[cur].id = cur;
        m_nodes[cur].left = l;
        m_nodes[cur].right = r;
        m_nodes[cur].mod = m_modZero;
        if (l == r - 1)
            m_nodes[cur].val = initValue[l - m_leftRange];
        else {
            size_type x = cur + 1, y = cur + (static_cast<size_type>(r - l) & ~static_cast<size_type>(1));
            build(x, l, (l + r) >> 1, initValue);
            build(y, (l + r) >> 1, r, initValue);
            pushUp(cur, x, y);
        }
    }
    template<typename BuildFunctionType>
    void funcBuild(size_type cur, range_type l, range_type r, BuildFunctionType buildFunc) {
        static_assert(std::is_convertible_v<BuildFunctionType, std::function<void(value_type&, range_type)>>,
                      "buildFunc must work as void(value_type&, range_type)");
        m_nodes[cur].id = cur;
        m_nodes[cur].left = l;
        m_nodes[cur].right = r;
        m_nodes[cur].mod = m_modZero;
        if (l == r - 1)
            buildFunc(m_nodes[cur].val, l);
        else {
            size_type x = cur + 1, y = cur + (static_cast<size_type>(r - l) & ~static_cast<size_type>(1));
            funcBuild(x, l, (l + r) >> 1, buildFunc);
            funcBuild(y, (l + r) >> 1, r, buildFunc);
            pushUp(cur, x, y);
        }
    }

    void m_init(const std::vector<value_type>& _initValue,
                merge_function_type _mergeNode, update_function_type _updateMod,
                const value_type& _valueZero, const modification_type& _modZero) {
        m_mergeNode = _mergeNode;
        m_updateMod = _updateMod;
        m_valueZero = _valueZero;
        m_modZero = _modZero;
        m_nodes.resize((m_rightRange - m_leftRange) << 1);
        build(1, m_leftRange, m_rightRange, _initValue);
    }

    void modify(size_type cur, range_type l, range_type r, range_type L, range_type R, const modification_type& mod) {
        if (l >= R || r <= L) return;
        if (L <= l && r <= R) {
            m_updateMod(m_nodes[cur], mod);
        } else {
            size_type x = cur + 1, y = cur + (static_cast<size_type>(r - l) & ~static_cast<size_type>(1));
            if constexpr (RangeModify) pushDown(cur, x, y);
            modify(x, l, (l + r) >> 1, L, R, mod);
            modify(y, (l + r) >> 1, r, L, R, mod);
            pushUp(cur, x, y);
        }
    }

    value_type query(size_type cur, range_type l, range_type r, range_type L, range_type R) const {
        if (l >= R || r <= L) return m_valueZero;
        if (L <= l && r <= R) return m_nodes[cur].val;
        size_type x = cur + 1, y = cur + (static_cast<size_type>(r - l) & ~static_cast<size_type>(1));
        if constexpr (RangeModify) pushDown(cur, x, y);
        return m_mergeNode(query(x, l, (l + r) >> 1, L, R),
                           query(y, (l + r) >> 1, r, L, R));
    }

public:
    // private:
    merge_function_type m_mergeNode;
    update_function_type m_updateMod;
    mutable std::vector<node_type> m_nodes;
    range_type m_leftRange = 0, m_rightRange = 0;
    value_type m_valueZero;
    modification_type m_modZero;
};
template<typename Ostream, typename ValueType, typename ModificationType, bool RangeModify, typename RangeType, typename SizeType>
Ostream& operator<<(Ostream& out, const SegmentTree<ValueType, ModificationType, RangeModify, RangeType, SizeType>& seg) {
    out << "[";
    for (RangeType i = seg.m_leftRange; i < seg.m_rightRange; i += 1) {
        if (i != seg.m_leftRange) out << ", ";
        out << seg.query(i);
    }
    return out << "]";
}
} // namespace SegmentTreeDetails
template<typename ValueType, typename ModificationType, typename RangeType = int32_t, typename SizeType = uint32_t>
using SegmentTreeNode = SegmentTreeDetails::SegmentTreeNode<ValueType, ModificationType, RangeType, SizeType>;
template<typename ValueType, typename ModificationType, bool RangeModify = true, typename RangeType = int32_t, typename SizeType = uint32_t>
using SegmentTree = SegmentTreeDetails::SegmentTree<ValueType, ModificationType, RangeModify, RangeType, SizeType>;
} // namespace OI::DataStructure
/*
using Infomation = int;
struct Modification {
    constexpr static int NONE = -(1 << 29);
    int assign = NONE;
    bool isZero() const { return assign == NONE; }
};

using SegmentTree = OI::DataStructure::SegmentTree<Infomation, Modification, true>;

Infomation seg_merge(Infomation x, Infomation y) {
    return std::max(x, y);
}
void seg_update(SegmentTree::node_type& node, const Modification& mod) {
    if (mod.isZero()) return;
    node.val = mod.assign;
    node.mod.assign = mod.assign;
}

// [0, n)
auto buildFunc = [](SegmentTree::value_type& v, SegmentTree::range_type i) {
    std::cin >> v;
    // v = 0;
};
SegmentTree seg(buildFunc, seg_merge, seg_update, 0, n);
// SegmentTree<Infomation, Modification, false> seg(vector<Infomation>(n), seg_merge, seg_update);
*/