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

#include <cassert>
#include <climits>
#include <cstddef>
#include <functional>
#include <iterator>
#include <vector>

namespace OI::DataStructure::SegmentTree {
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
    SegmentTree(const SegmentTree& o): merge(o.merge), update(o.update), nodes(o.nodes),
                                       leftRange(o.leftRange), rightRange(o.rightRange),
                                       valueZero(o.valueZero), modZero(o.modZero) {}
    SegmentTree(SegmentTree&& o): merge(std::move(o.merge)), update(std::move(o.update)), nodes(std::move(o.nodes)),
                                  leftRange(o.leftRange), rightRange(o.rightRange),
                                  valueZero(std::move(o.valueZero)), modZero(std::move(o.modZero)) {
        o.leftRange = o.rightRange = 0;
    }
    SegmentTree& operator=(const SegmentTree& o) {
        if (this == &o) return *this;
        merge = o.merge;
        update = o.update;
        nodes = o.nodes;
        leftRange = o.leftRange;
        rightRange = o.rightRange;
        valueZero = o.valueZero;
        modZero = o.modZero;
    }
    SegmentTree& operator=(SegmentTree&& o) {
        if (this == &o) return *this;
        merge = std::move(o.merge);
        update = std::move(o.update);
        nodes = std::move(o.nodes);
        leftRange = o.leftRange;
        rightRange = o.rightRange;
        valueZero = std::move(o.valueZero);
        modZero = std::move(o.modZero);
        o.leftRange = o.rightRange = 0;
    }
    ~SegmentTree() = default;

    SegmentTree(const std::vector<ValueType>& _initValue,
                MergeFunctionType _merge, UpdateFunctionType _update,
                RangeType _startPoint = 0, const ValueType& _valueZero = ValueType(),
                const ModificationType& _modZero = ModificationType()) {
        init(_initValue, _merge, _update, _startPoint, _valueZero, _modZero);
    }

    SegmentTree(MergeFunctionType _merge, UpdateFunctionType _update,
                RangeType _leftRange, RangeType _rightRange,
                const ValueType& _initValue = ValueType(),
                const ValueType& _valueZero = ValueType(),
                const ModificationType& _modZero = ModificationType())
        : merge(_merge), update(_update),
          leftRange(_leftRange), rightRange(_rightRange),
          valueZero(_valueZero), modZero(_modZero) {
        assert(leftRange <= rightRange);
        nodes.resize((rightRange - leftRange) << 1);
        sameValueBuild(1, leftRange, rightRange, _initValue);
    }

    void init(const std::vector<ValueType>& _initValue,
              MergeFunctionType _merge, UpdateFunctionType _update,
              RangeType _startPoint = 0, const ValueType& _valueZero = ValueType(),
              const ModificationType& _modZero = ModificationType()) {
        assert(_startPoint >= LLONG_MIN / 2);
        assert(_startPoint <= LLONG_MAX / 2 - static_cast<RangeType>(_initValue.size()));
        leftRange = _startPoint;
        rightRange = _startPoint + _initValue.size();
        m_init(_initValue, _merge, _update, _valueZero, _modZero);
    }

    void modify(RangeType l, RangeType r, const ModificationType& mod) {
        assert(rangeModify);
        assert(leftRange <= l && l <= r && r <= rightRange);
        modify(1, leftRange, rightRange, l, r, mod);
    }

    void modify(RangeType p, const ModificationType& mod) {
        assert(leftRange <= p && p < rightRange);
        modify(1, leftRange, rightRange, p, p + 1, mod);
    }

    ValueType query(RangeType l, RangeType r) {
        return query(1, leftRange, rightRange, l, r);
    }

    ValueType query(RangeType p) {
        return query(p, p + 1);
    }

    void swap(SegmentTree& rhs) {
        std::swap(merge, rhs.merge);
        std::swap(update, rhs.update);
        std::swap(nodes, rhs.nodes);
        std::swap(leftRange, rhs.leftRange);
        std::swap(rightRange, rhs.rightRange);
        std::swap(valueZero, rhs.valueZero);
        std::swap(modZero, rhs.modZero);
    }

private:
    void pushup(size_t cur, RangeType x, RangeType y) {
        nodes[cur].val = merge(nodes[x].val, nodes[y].val);
    }

    void pushdown(size_t cur, RangeType x, RangeType y) {
        update(nodes[x], nodes[cur].mod);
        update(nodes[y], nodes[cur].mod);
        nodes[cur].mod = modZero;
    }

    void build(size_t cur, RangeType l, RangeType r, const std::vector<ValueType>& initValue) {
        nodes[cur].id = cur;
        nodes[cur].left = l;
        nodes[cur].right = r;
        nodes[cur].mod = modZero;
        if (l == r - 1)
            nodes[cur].val = initValue[l - leftRange];
        else {
            size_t x = cur + 1, y = cur + ((r - l) & ~1);
            build(x, l, (l + r) >> 1, initValue);
            build(y, (l + r) >> 1, r, initValue);
            pushup(cur, x, y);
        }
    }
    void sameValueBuild(size_t cur, RangeType l, RangeType r, const ValueType& initValue) {
        nodes[cur].id = cur;
        nodes[cur].left = l;
        nodes[cur].right = r;
        nodes[cur].mod = modZero;
        if (l == r - 1)
            nodes[cur].val = initValue;
        else {
            size_t x = cur + 1, y = cur + ((r - l) & ~1);
            sameValueBuild(x, l, (l + r) >> 1, initValue);
            sameValueBuild(y, (l + r) >> 1, r, initValue);
            pushup(cur, x, y);
        }
    }

    void m_init(const std::vector<ValueType>& _initValue,
                MergeFunctionType _merge, UpdateFunctionType _update,
                const ValueType& _valueZero, const ModificationType& _modZero) {
        merge = _merge;
        update = _update;
        valueZero = _valueZero;
        modZero = _modZero;
        nodes.resize((rightRange - leftRange) << 1);
        build(1, leftRange, rightRange, _initValue);
    }

    void modify(size_t cur, RangeType l, RangeType r, RangeType L, RangeType R, const ModificationType& mod) {
        if (l >= R || r <= L) return;
        if (L <= l && r <= R) {
            update(nodes[cur], mod);
        } else {
            size_t x = cur + 1, y = cur + ((r - l) & ~1);
            if (rangeModify) pushdown(cur, x, y);
            modify(x, l, (l + r) >> 1, L, R, mod);
            modify(y, (l + r) >> 1, r, L, R, mod);
            pushup(cur, x, y);
        }
    }

    ValueType query(size_t cur, RangeType l, RangeType r, RangeType L, RangeType R) {
        if (l >= R || r <= L) return valueZero;
        if (L <= l && r <= R) return nodes[cur].val;
        size_t x = cur + 1, y = cur + ((r - l) & ~1);
        if (rangeModify) pushdown(cur, x, y);
        return merge(query(x, l, (l + r) >> 1, L, R),
                     query(y, (l + r) >> 1, r, L, R));
    }

    MergeFunctionType merge;
    UpdateFunctionType update;
    std::vector<NodeType> nodes;
    RangeType leftRange = 0, rightRange = 0;
    ValueType valueZero;
    ModificationType modZero;
};

template<typename ValueType, typename ModificationType, bool rangeModify>
void swap(SegmentTree<ValueType, ModificationType, rangeModify>& lhs,
          SegmentTree<ValueType, ModificationType, rangeModify>& rhs) {
    lhs.swap(rhs);
}
} // namespace OI::DataStructure::SegmentTree

using namespace OI::DataStructure::SegmentTree;

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
        SegmentTree<Infomation, Modification, false> seg(seg_merge, seg_update, 0, n + 1);
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