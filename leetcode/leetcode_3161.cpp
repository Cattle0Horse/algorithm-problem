/**
 * @file leetcode_3161.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/block-placement-queries/
 * @version 0.1
 * @date 2024-05-28
 *
 * @copyright Copyright (c) 2024
 *
 */

/**
 * @file segment_tree.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
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
 * 3.(Type)ValueType       : supports the = operator.
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
 * @version 1.2
 * @date 2024-04-22
 *
 * @copyright Copyright (c) 2024
 * fork from  @link{https://github.com/ouuan/CPTH/blob/master/docs/SegmentTree.md}
 */
#include <cassert>
#include <climits>
#include <cstddef>
#include <functional>
#include <vector>

namespace OI::DataStructure {
namespace SegmentTreeDetails {
using RangeType = long long;
template<typename ValueType, typename ModificationType>
struct SegmentTreeNode {
    // the id of the root is 1(default)
    size_t id;
    // the left and right represent for the subsegment [left, right) of the node
    RangeType left, right;
    ValueType val;
    ModificationType mod;
};

template<typename ValueType, typename ModificationType, bool rangeModify = true>
class SegmentTree {
public:
    using NodeType = SegmentTreeNode<ValueType, ModificationType>;
    using MergeFunctionType = std::function<ValueType(const ValueType&, const ValueType&)>;
    using UpdateFunctionType = std::function<void(NodeType&, const ModificationType&)>;

    SegmentTree() = default;

    SegmentTree(const std::vector<ValueType>& _initValue,
                MergeFunctionType _mergeNode, UpdateFunctionType _updateMod,
                RangeType _startPoint = 0, const ValueType& _valueZero = ValueType(),
                const ModificationType& _modZero = ModificationType()) {
        init(_initValue, _mergeNode, _updateMod, _startPoint, _valueZero, _modZero);
    }

    template<typename BuildFunctionType = std::function<void(ValueType&, RangeType)>>
    SegmentTree(BuildFunctionType _buildFunc, MergeFunctionType _mergeNode, UpdateFunctionType _updateMod,
                RangeType _leftRange, RangeType _rightRange,
                const ValueType& _valueZero = ValueType(),
                const ModificationType& _modZero = ModificationType())
        : m_mergeNode(_mergeNode), m_updateMod(_updateMod),
          m_leftRange(_leftRange), m_rightRange(_rightRange),
          m_valueZero(_valueZero), m_modZero(_modZero) {
        assert(m_leftRange <= m_rightRange);
        m_nodes.resize((m_rightRange - m_leftRange) << 1);
        func_build(1, _leftRange, _rightRange, _buildFunc);
    }

    void init(const std::vector<ValueType>& _initValue,
              MergeFunctionType _mergeNode, UpdateFunctionType _updateMod,
              RangeType _startPoint = 0, const ValueType& _valueZero = ValueType(),
              const ModificationType& _modZero = ModificationType()) {
        assert(_startPoint >= LLONG_MIN / 2);
        assert(_startPoint <= LLONG_MAX / 2 - static_cast<RangeType>(_initValue.size()));
        m_leftRange = _startPoint;
        m_rightRange = _startPoint + _initValue.size();
        m_init(_initValue, _mergeNode, _updateMod, _valueZero, _modZero);
    }

    void modify(RangeType l, RangeType r, const ModificationType& mod) {
        assert(rangeModify);
        assert(m_leftRange <= l && l <= r && r <= m_rightRange);
        modify(1, m_leftRange, m_rightRange, l, r, mod);
    }

    void modify(RangeType p, const ModificationType& mod) {
        assert(m_leftRange <= p && p < m_rightRange);
        modify(1, m_leftRange, m_rightRange, p, p + 1, mod);
    }

    ValueType query(RangeType l, RangeType r) {
        return query(1, m_leftRange, m_rightRange, l, r);
    }

    ValueType query(RangeType p) {
        return query(p, p + 1);
    }

private:
    void pushup(size_t cur, RangeType x, RangeType y) {
        m_nodes[cur].val = m_mergeNode(m_nodes[x].val, m_nodes[y].val);
    }

    void pushdown(size_t cur, RangeType x, RangeType y) {
        m_updateMod(m_nodes[x], m_nodes[cur].mod);
        m_updateMod(m_nodes[y], m_nodes[cur].mod);
        m_nodes[cur].mod = m_modZero;
    }

    void build(size_t cur, RangeType l, RangeType r, const std::vector<ValueType>& initValue) {
        m_nodes[cur].id = cur;
        m_nodes[cur].left = l;
        m_nodes[cur].right = r;
        m_nodes[cur].mod = m_modZero;
        if (l == r - 1)
            m_nodes[cur].val = initValue[l - m_leftRange];
        else {
            size_t x = cur + 1, y = cur + ((r - l) & ~1);
            build(x, l, (l + r) >> 1, initValue);
            build(y, (l + r) >> 1, r, initValue);
            pushup(cur, x, y);
        }
    }
    template<typename BuildFunctionType>
    void func_build(size_t cur, RangeType l, RangeType r, BuildFunctionType buildFunc) {
        m_nodes[cur].id = cur;
        m_nodes[cur].left = l;
        m_nodes[cur].right = r;
        m_nodes[cur].mod = m_modZero;
        if (l == r - 1)
            buildFunc(m_nodes[cur].val, l);
        else {
            size_t x = cur + 1, y = cur + ((r - l) & ~1);
            func_build(x, l, (l + r) >> 1, buildFunc);
            func_build(y, (l + r) >> 1, r, buildFunc);
            pushup(cur, x, y);
        }
    }

    void m_init(const std::vector<ValueType>& _initValue,
                MergeFunctionType _mergeNode, UpdateFunctionType _updateMod,
                const ValueType& _valueZero, const ModificationType& _modZero) {
        m_mergeNode = _mergeNode;
        m_updateMod = _updateMod;
        m_valueZero = _valueZero;
        m_modZero = _modZero;
        m_nodes.resize((m_rightRange - m_leftRange) << 1);
        build(1, m_leftRange, m_rightRange, _initValue);
    }

    void modify(size_t cur, RangeType l, RangeType r, RangeType L, RangeType R, const ModificationType& mod) {
        if (l >= R || r <= L) return;
        if (L <= l && r <= R) {
            m_updateMod(m_nodes[cur], mod);
        } else {
            size_t x = cur + 1, y = cur + ((r - l) & ~1);
            if (rangeModify) pushdown(cur, x, y);
            modify(x, l, (l + r) >> 1, L, R, mod);
            modify(y, (l + r) >> 1, r, L, R, mod);
            pushup(cur, x, y);
        }
    }

    ValueType query(size_t cur, RangeType l, RangeType r, RangeType L, RangeType R) {
        if (l >= R || r <= L) return m_valueZero;
        if (L <= l && r <= R) return m_nodes[cur].val;
        size_t x = cur + 1, y = cur + ((r - l) & ~1);
        if (rangeModify) pushdown(cur, x, y);
        return m_mergeNode(query(x, l, (l + r) >> 1, L, R),
                           query(y, (l + r) >> 1, r, L, R));
    }

    MergeFunctionType m_mergeNode;
    UpdateFunctionType m_updateMod;
    std::vector<NodeType> m_nodes;
    RangeType m_leftRange = 0, m_rightRange = 0;
    ValueType m_valueZero;
    ModificationType m_modZero;
};
} // namespace SegmentTreeDetails
template<typename ValueType, typename ModificationType>
using SegmentTreeNode = SegmentTreeDetails::SegmentTreeNode<ValueType, ModificationType>;
template<typename ValueType, typename ModificationType, bool rangeModify = true>
using SegmentTree = SegmentTreeDetails::SegmentTree<ValueType, ModificationType, rangeModify>;
} // namespace OI::DataStructure

/*
using namespace OI::DataStructure;

using Infomation = int;
Infomation seg_merge(Infomation x, Infomation y) {
    return std::max(x, y);
}

struct Modification {
    constexpr static int NONE = -(1 << 29);
    int assign = NONE;
    bool isZero() const { return assign == NONE; }
};
void seg_update(SegmentTreeNode<Infomation, Modification>& node, const Modification& mod) {
    if (mod.isZero()) return;
    node.val = mod.assign;
}

// [0, n)
SegmentTree<Infomation, Modification, false> seg(seg_merge, seg_update, 0, n);
SegmentTree<Infomation, Modification, false> seg(vector<Infomation>(n), seg_merge, seg_update);
*/

using namespace OI::DataStructure;

using Infomation = int;
Infomation seg_merge(Infomation x, Infomation y) {
    return std::max(x, y);
}

struct Modification {
    constexpr static int NONE = -(1 << 29);
    int assign = NONE;
    bool isZero() const { return assign == NONE; }
    Modification& operator=(const Modification& o) {
        if (this == &o) return *this;
        this->assign = o.assign;
        return *this;
    }
};
void seg_update(SegmentTreeNode<Infomation, Modification>& node, const Modification& mod) {
    if (mod.isZero()) return;
    node.val = mod.assign;
}

#include <algorithm>
#include <set>
#include <vector>
class Solution {
public:
    std::vector<bool> getResults(std::vector<std::vector<int>>& queries) {
        std::vector<bool> ans;
        int n = std::min(static_cast<int>(5e4), static_cast<int>(3 * queries.size())) + 1;
        std::set<int> s{0, n};
        SegmentTree<Infomation, Modification> seg([](Infomation& val, long long p) { return val = 0; }, seg_merge, seg_update, 0, n + 1);
        for (auto&& query : queries) {
            int x = query[1];
            if (query[0] == 1) {
                auto nxt = s.upper_bound(x);
                int pre = *std::prev(nxt);
                seg.modify(x, Modification(x - pre));
                seg.modify(*nxt, Modification(*nxt - x));
                s.insert(x);
            } else {
                int sz = query[2];
                int pre = *std::prev(s.lower_bound(x));
                Infomation q = seg.query(0, pre + 1);
                ans.push_back(std::max(q, x - pre) >= sz);
            }
        }
        return ans;
    }
};