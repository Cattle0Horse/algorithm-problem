/**
 * @file dynamic_segment_tree.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 *
 * @brief  you need to implement two function and specify the type of value and the type of modification:
 * 1.(Function)merge       : It will combine the results of the two subsegment(Just like when you call the `query` method).
 *                           You still need to satisfy where `merge(valueZero, x) == x` and `merge(x, valueZero) == x`
 *                           for any possible value x(For example, for addition there is `merge(7, 0) == 7`,
 *                                                                 for taking the maximum value `merge(9, -INF) = 9`)
 *
 * 2.(Function)update      : It will use `mod` to modify `node`.
 *                           If lazy propagation is needed(For example, when rangeModify is true), you also need to update `node.mod`.
 *
 * 3.(Type)ValueType       : supports the = operator.
 *                           has default constructor.
 *                           Give the value of valueZero when constructing the segment tree (otherwise it will use the default constructor of ValueType).
 *
 * 4.(Type)ModificationType: supports the = operator.
 *                           has default constructor.
 *                           Give the value of valueZero when constructing the segment tree (otherwise it will use the default constructor of ValueType).
 *
 * 5.(long long)leftRange  : The root node of the segment tree manages the left boundary of the range(It supports negative ranges)
 *
 * 6.(long long)rightRange : The root node of the segment tree manages the right(exclusive) boundary of the range(It supports negative ranges)
 *
 * 7.(bool)rangeModify     : If you do not need range modification, please set `rangeModify` to false
 *
 * 8. For online judge, you can annotate the destructor to improve efficiency
 *
 * @version 1.0
 * @date 2024-04-22
 *
 * @copyright Copyright (c) 2024
 */

/*
usage1:
struct Modification {
    constexpr static int NONE = 1 << 29;
    int assign = NONE;
    bool is_zero() const { return assign == NONE; }
    Modification& operator=(const Modification& o) {
        if (this == &o) return *this;
        this->assign = o.assign;
        return *this;
    }
};
int seg_merge(int x, int y) {
    return x + y;
}
void seg_update(SegmentTreeNode<int, Modification>& node, const Modification& mod) {
    if (!mod.is_zero()) {
        node.val = (node.right - node.left) * mod.assign;
    }
}
SegmentTree<int, Modification, false> seg(seg_merge, seg_update, -1000, 1000);

-----------------------------------------------------------------------------------
usage2:
struct Modification {
    constexpr static int NONE = 0;
    int add = 0;
    bool is_zero() const { return add == NONE; }
    Modification& operator=(const Modification& o) {
        if (this == &o) return *this;
        this->add = o.add;
        return *this;
    }
};

int seg_merge(int x, int y) {
    return x + y;
}
void seg_update(SegmentTreeNode<int, Modification>& node, const Modification& mod) {
    if (!mod.is_zero()) {
        node.val += (node.right - node.left) * mod.add;
        node.mod.add += mod.add; // range_modify require
    }
}
SegmentTree<int, Modification, true> seg(seg_merge, seg_update, -1e9, 1e9);
*/

#include <cassert>
#include <functional>

namespace OI::DataStructure::DynamicSegmentTree {
using RangeType = long long;

template<typename ValueType, typename ModificationType>
struct SegmentTreeNode {
    // the left and right represent for the subsegment [left, right) of the node
    RangeType m_left, m_right;
    ValueType m_val;
    ModificationType m_mod;
    SegmentTreeNode *m_leftChild = nullptr, *m_rightChild = nullptr;

    void createLeftChildren(RangeType left, RangeType right, const ValueType& val, const ModificationType& mod) {
        if (m_leftChild == nullptr) {
            m_leftChild = new SegmentTreeNode(left, right, val, mod);
        }
    }
    void createRightChildren(RangeType left, RangeType right, const ValueType& val, const ModificationType& mod) {
        if (m_rightChild == nullptr) {
            m_rightChild = new SegmentTreeNode(left, right, val, mod);
        }
    }

    ~SegmentTreeNode() {
        if (m_leftChild != nullptr) delete m_leftChild;
        if (m_rightChild != nullptr) delete m_rightChild;
    }
};

template<typename ValueType, typename ModificationType, bool RangeModify = true>
class SegmentTree {
public:
    using NodeType = SegmentTreeNode<ValueType, ModificationType>;
    using MergeFunctionType = std::function<ValueType(const ValueType&, const ValueType&)>;
    using UpdateFunctionType = std::function<void(NodeType&, const ModificationType&)>;

    SegmentTree() = default;
    ~SegmentTree() {
        if (m_root != nullptr) delete m_root;
    }
    SegmentTree(MergeFunctionType _merge, UpdateFunctionType _update,
                RangeType _leftRange, RangeType _rightRange,
                const ValueType& _valueZero = ValueType(),
                const ModificationType& _modZero = ModificationType())
        : m_merge(_merge), m_update(_update),
          m_leftRange(_leftRange), m_rightRange(_rightRange),
          m_valueZero(_valueZero), m_modZero(_modZero) {
        assert(std::numeric_limits<RangeType>::min() / 2 <= _leftRange && _leftRange <= _rightRange && _rightRange <= std::numeric_limits<RangeType>::max() / 2);
        m_root = new NodeType(m_leftRange, m_rightRange, m_valueZero, m_modZero);
    }

    void modify(RangeType l, RangeType r, const ModificationType& mod) {
        static_assert(RangeModify, "RangeModify Must Be True");
        assert(m_leftRange <= l && l <= r && r <= m_rightRange);
        modify(m_root, m_leftRange, m_rightRange, l, r, mod);
    }

    void modify(RangeType p, const ModificationType& mod) {
        assert(m_leftRange <= p && p < m_rightRange);
        modify(m_root, m_leftRange, m_rightRange, p, p + 1, mod);
    }

    ValueType query(RangeType l, RangeType r) {
        return query(m_root, m_leftRange, m_rightRange, l, r);
    }

    ValueType query(RangeType p) {
        return query(p, p + 1);
    }

private:
    void pushup(NodeType* cur) {
        cur->m_val = m_merge(cur->m_leftChild->val, cur->m_rightChild->val);
    }

    void pushdown(NodeType* cur) {
        m_update(*(cur->m_leftChild), cur->m_mod);
        m_update(*(cur->m_rightChild), cur->m_mod);
        cur->m_mod = m_modZero;
    }

    void modify(NodeType* cur, RangeType l, RangeType r, RangeType L, RangeType R, const ModificationType& mod) {
        if (l >= R || r <= L) return;
        if (L <= l && r <= R) {
            m_update(*cur, mod);
        } else {
            cur->createLeftChildren(l, (l + r) >> 1, m_valueZero, m_modZero);
            cur->createRightChildren((l + r) >> 1, r, m_valueZero, m_modZero);
            if (RangeModify) pushdown(cur);
            modify(cur->m_leftChild, l, (l + r) >> 1, L, R, mod);
            modify(cur->m_rightChild, (l + r) >> 1, r, L, R, mod);
            pushup(cur);
        }
    }

    ValueType query(NodeType* cur, RangeType l, RangeType r, RangeType L, RangeType R) {
        if (l >= R || r <= L) return m_valueZero;
        if (L <= l && r <= R) return cur->m_val;
        cur->createLeftChildren(l, (l + r) >> 1, m_valueZero, m_modZero);
        cur->createRightChildren((l + r) >> 1, r, m_valueZero, m_modZero);
        if constexpr (RangeModify) pushdown(cur);
        return m_merge(query(cur->m_leftChild, l, (l + r) >> 1, L, R),
                     query(cur->m_rightChild, (l + r) >> 1, r, L, R));
    }

    MergeFunctionType m_merge;
    UpdateFunctionType m_update;
    NodeType* m_root = nullptr;
    RangeType m_leftRange = 0, m_rightRange = 0;
    ValueType m_valueZero;
    ModificationType m_modZero;
};
} // namespace OI::DataStructure::DynamicSegmentTree