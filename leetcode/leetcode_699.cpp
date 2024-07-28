// @date 2024/7/28 12:41:15
// @author Cattle_Horse (CattleHorse@duck.com)
// @problem 699. 掉落的方块
// @link https://leetcode.cn/classic/problems/falling-squares/description/

#ifdef Cattle_Horse
#include "leetcode.h" // IWYU pragma: keep
using namespace std;
#else
#define dbg(...) void(114514)
#endif

[[maybe_unused]] auto __init_io__ = []() {
    return std::cin.tie(nullptr)->sync_with_stdio(false);
}();

namespace OI::DataStructure {
namespace SegmentTreeDetails {
using RangeType = int64_t;
using SizeType = uint32_t;
template<typename ValueType, typename ModificationType>
struct SegmentTreeNode {
    // the id of the root is 1(default)
    SizeType id;
    // the left and right represent for the subsegment [left, right) of the node
    RangeType left, right;
    ValueType val;
    ModificationType mod;
};
template<typename Ostream, typename ValueType, typename ModificationType>
Ostream& operator<<(Ostream& out, const SegmentTreeNode<ValueType, ModificationType>& node) {
    return out << "{id: " << node.id << ", left: " << node.left << ", right: " << node.right << ", val: " << node.val << ", mod: " << node.mod << "}";
}
template<typename ValueType, typename ModificationType, bool RangeModify = true>
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

    template<typename BuildFunctionType>
    SegmentTree(BuildFunctionType _buildFunc, MergeFunctionType _mergeNode, UpdateFunctionType _updateMod,
                RangeType _leftRange, RangeType _rightRange,
                const ValueType& _valueZero = ValueType(),
                const ModificationType& _modZero = ModificationType())
        : m_mergeNode(_mergeNode), m_updateMod(_updateMod),
          m_leftRange(_leftRange), m_rightRange(_rightRange),
          m_valueZero(_valueZero), m_modZero(_modZero) {
        static_assert(std::is_convertible_v<BuildFunctionType, std::function<void(ValueType&, RangeType)>>,
                      "buildFunc must work as void(ValueType&, RangeType)");
        assert(m_leftRange <= m_rightRange);
        m_nodes.resize((m_rightRange - m_leftRange) << 1);
        funcBuild(1, _leftRange, _rightRange, _buildFunc);
    }

    void init(const std::vector<ValueType>& _initValue,
              MergeFunctionType _mergeNode, UpdateFunctionType _updateMod,
              RangeType _startPoint = 0, const ValueType& _valueZero = ValueType(),
              const ModificationType& _modZero = ModificationType()) {
        assert(_startPoint >= std::numeric_limits<RangeType>::min() / 2);
        assert(_startPoint <= std::numeric_limits<RangeType>::max() / 2 - static_cast<SizeType>(_initValue.size()));
        m_leftRange = _startPoint;
        m_rightRange = _startPoint + _initValue.size();
        m_init(_initValue, _mergeNode, _updateMod, _valueZero, _modZero);
    }

    void modify(RangeType l, RangeType r, const ModificationType& mod) {
        static_assert(RangeModify, "RangeModify Must Be True");
        assert(m_leftRange <= l && l <= r && r <= m_rightRange);
        modify(1, m_leftRange, m_rightRange, l, r, mod);
    }

    void modify(RangeType p, const ModificationType& mod) {
        assert(m_leftRange <= p && p < m_rightRange);
        modify(1, m_leftRange, m_rightRange, p, p + 1, mod);
    }

    ValueType query(RangeType l, RangeType r) const {
        return query(1, m_leftRange, m_rightRange, l, r);
    }

    ValueType query(RangeType p) const {
        return query(p, p + 1);
    }

private:
    void pushUp(SizeType cur, RangeType x, RangeType y) {
        m_nodes[cur].val = m_mergeNode(m_nodes[x].val, m_nodes[y].val);
    }

    void pushDown(SizeType cur, RangeType x, RangeType y) const {
        m_updateMod(m_nodes[x], m_nodes[cur].mod);
        m_updateMod(m_nodes[y], m_nodes[cur].mod);
        m_nodes[cur].mod = m_modZero;
    }

    void build(SizeType cur, RangeType l, RangeType r, const std::vector<ValueType>& initValue) {
        m_nodes[cur].id = cur;
        m_nodes[cur].left = l;
        m_nodes[cur].right = r;
        m_nodes[cur].mod = m_modZero;
        if (l == r - 1)
            m_nodes[cur].val = initValue[l - m_leftRange];
        else {
            SizeType x = cur + 1, y = cur + (static_cast<SizeType>(r - l) & ~static_cast<SizeType>(1));
            build(x, l, (l + r) >> 1, initValue);
            build(y, (l + r) >> 1, r, initValue);
            pushUp(cur, x, y);
        }
    }
    template<typename BuildFunctionType>
    void funcBuild(SizeType cur, RangeType l, RangeType r, BuildFunctionType buildFunc) {
        static_assert(std::is_convertible_v<BuildFunctionType, std::function<void(ValueType&, RangeType)>>,
                      "buildFunc must work as void(ValueType&, RangeType)");
        m_nodes[cur].id = cur;
        m_nodes[cur].left = l;
        m_nodes[cur].right = r;
        m_nodes[cur].mod = m_modZero;
        if (l == r - 1)
            buildFunc(m_nodes[cur].val, l);
        else {
            SizeType x = cur + 1, y = cur + (static_cast<SizeType>(r - l) & ~static_cast<SizeType>(1));
            funcBuild(x, l, (l + r) >> 1, buildFunc);
            funcBuild(y, (l + r) >> 1, r, buildFunc);
            pushUp(cur, x, y);
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

    void modify(SizeType cur, RangeType l, RangeType r, RangeType L, RangeType R, const ModificationType& mod) {
        if (l >= R || r <= L) return;
        if (L <= l && r <= R) {
            m_updateMod(m_nodes[cur], mod);
        } else {
            SizeType x = cur + 1, y = cur + (static_cast<SizeType>(r - l) & ~static_cast<SizeType>(1));
            if constexpr (RangeModify) pushDown(cur, x, y);
            modify(x, l, (l + r) >> 1, L, R, mod);
            modify(y, (l + r) >> 1, r, L, R, mod);
            pushUp(cur, x, y);
        }
    }

    ValueType query(SizeType cur, RangeType l, RangeType r, RangeType L, RangeType R) const {
        if (l >= R || r <= L) return m_valueZero;
        if (L <= l && r <= R) return m_nodes[cur].val;
        SizeType x = cur + 1, y = cur + (static_cast<SizeType>(r - l) & ~static_cast<SizeType>(1));
        if constexpr (RangeModify) pushDown(cur, x, y);
        return m_mergeNode(query(x, l, (l + r) >> 1, L, R),
                           query(y, (l + r) >> 1, r, L, R));
    }

public:
    MergeFunctionType m_mergeNode;
    UpdateFunctionType m_updateMod;
    mutable std::vector<NodeType> m_nodes;
    RangeType m_leftRange = 0, m_rightRange = 0;
    const ValueType m_valueZero;
    ModificationType m_modZero;
};
template<typename Ostream, typename ValueType, typename ModificationType, bool RangeModify>
Ostream& operator<<(Ostream& out, const SegmentTree<ValueType, ModificationType, RangeModify>& seg) {
    out << "[";
    for (RangeType i = seg.m_leftRange; i < seg.m_rightRange; i += 1) {
        if (i != seg.m_leftRange) out << ", ";
        out << seg.query(i);
    }
    return out << "]";
}
} // namespace SegmentTreeDetails
template<typename ValueType, typename ModificationType>
using SegmentTreeNode = SegmentTreeDetails::SegmentTreeNode<ValueType, ModificationType>;
template<typename ValueType, typename ModificationType, bool rangeModify = true>
using SegmentTree = SegmentTreeDetails::SegmentTree<ValueType, ModificationType, rangeModify>;
} // namespace OI::DataStructure

using namespace OI::DataStructure;

using Infomation = int;
Infomation seg_merge(Infomation x, Infomation y) {
    return std::max(x, y);
}
template<typename Ostream>
Ostream& operator<<(Ostream& out, const Infomation& val) {
    return out << val;
}
struct Modification {
    constexpr static int NONE = -(1 << 19);
    int assign = NONE;
    bool isZero() const { return assign == NONE; }
};
template<typename Ostream>
Ostream& operator<<(Ostream& out, const Modification& mod) {
    return out << mod.assign;
}
void seg_update(SegmentTreeNode<Infomation, Modification>& node, const Modification& mod) {
    if (mod.isZero()) return;
    node.val = mod.assign;
    node.mod.assign = mod.assign;
}

// [0, n)
// auto buildFunc = [](Infomation& v, int i) { std::cin >> v; };
// SegmentTree<Infomation, Modification, true> seg(buildFunc, seg_merge, seg_update, 0, n);
// SegmentTree<Infomation, Modification, false> seg(vector<Infomation>(n), seg_merge, seg_update);

class Solution {
public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        int n = positions.size();
        std::vector<int> vals;
        vals.reserve(2 * n);
        for (auto&& p : positions) {
            vals.push_back(p[0]);
            vals.push_back(p[0] + p[1]);
        }
        std::ranges::sort(vals);
        vals.erase(std::unique(vals.begin(), vals.end()), vals.end());
        std::vector<int> ans;
        ans.reserve(n);
        auto buildFunc = [](Infomation& v, int i) {
            v = 0;
        };
        SegmentTree<Infomation, Modification, true> seg(buildFunc, seg_merge, seg_update, 0, vals.size());
        for (auto&& p : positions) {
            int l = std::ranges::lower_bound(vals, p[0]) - vals.begin();
            int r = std::ranges::lower_bound(vals, p[0] + p[1]) - vals.begin();
            int mx = seg.query(l, r);
            seg.modify(l, r, {mx + p[1]});
            ans.push_back(seg.query(0, vals.size()));
        }
        return ans;
    }
};

// vector<int> Solution::fallingSquares(vector<vector<int>> positions)

#ifdef Cattle_Horse
int main() {
    std::cout << "*** 699. 掉落的方块 ***" << std::endl
              << std::endl;

    Solution s0;

    {
        std::cout << "Test 1: ";

        vector<vector<int>> positions = {{1, 2}, {2, 3}, {6, 1}};
        vector<int> ans0 = s0.fallingSquares(positions);
        vector<int> exp0 = {2, 5, 5};

        if (ans0 == exp0) {
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
            std::cout << "  Answer: ";
            for (int& i : ans0) {
                std::cout << i << " ";
            }
            std::cout << std::endl
                      << "  Expect: ";
            for (int& i : exp0) {
                std::cout << i << " ";
            }
            std::cout << std::endl;
        }
    }

    {
        std::cout << "Test 2: ";

        vector<vector<int>> positions = {{100, 100}, {200, 100}};
        vector<int> ans1 = s0.fallingSquares(positions);
        vector<int> exp1 = {100, 100};

        if (ans1 == exp1) {
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
            std::cout << "  Answer: ";
            for (int& i : ans1) {
                std::cout << i << " ";
            }
            std::cout << std::endl
                      << "  Expect: ";
            for (int& i : exp1) {
                std::cout << i << " ";
            }
            std::cout << std::endl;
        }
    }

    {
        std::cout << "Test 3: ";

        vector<vector<int>> positions = {{1, 5}, {2, 2}, {7, 5}};
        vector<int> ans1 = s0.fallingSquares(positions);
        vector<int> exp1 = {5, 7, 7};

        if (ans1 == exp1) {
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
            std::cout << "  Answer: ";
            for (int& i : ans1) {
                std::cout << i << " ";
            }
            std::cout << std::endl
                      << "  Expect: ";
            for (int& i : exp1) {
                std::cout << i << " ";
            }
            std::cout << std::endl;
        }
    }
    return 0;
}
#endif
