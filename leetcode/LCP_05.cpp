/**
 * @file LCP_05.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/coin-bonus/description/
 * @version 0.1
 * @date 2024-06-20
 *
 * @copyright Copyright (c) 2024
 *
 */

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
 * @file tree_chain_v3.cpp
 * @author Cattle_Horse (1141754930@qq.com)
 * @brief
 * @version 3.0
 * @date 2024-04-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <vector>
namespace OI::Graph::WithoutWeight {
using Adjacency = std::vector<std::vector<int>>;
struct TreeChain {
    constexpr static int son_init{-1};
    constexpr static int no_ancestor{-1};

    std::vector<int> father, son, depth, top, size;
    // dfn : 树链剖分的dfs序
    // id  : dfn对应的原节点编号
    // 二者互为映射关系
    std::vector<int> dfn, id, max_dfn;
    int tot;

    TreeChain(const Adjacency& adj, int n, int root = 0)
        : father(n, -1), son(n, son_init), depth(n, -1), top(n, -1), size(n, -1), dfn(n), id(n), max_dfn(n), tot(0) {
        dfs1(adj, root, -1);
        dfs2(adj, root, root);
    }
    void dfs1(const Adjacency& adj, int now, int fa, int dep = 1) {
        depth[now] = dep;
        father[now] = fa;
        size[now] = 1;
        for (auto&& v : adj[now]) {
            if (v == fa) continue;
            dfs1(adj, v, now, dep + 1);
            size[now] += size[v];
            if (son[now] == son_init || size[v] > size[son[now]]) son[now] = v;
        }
    }
    void dfs2(const Adjacency& adj, int now, int top_id) {
        top[now] = top_id;
        dfn[now] = tot++;
        id[dfn[now]] = now;
        if (son[now] == son_init) {
            max_dfn[now] = dfn[now];
            return;
        }
        dfs2(adj, son[now], top_id);
        for (auto&& v : adj[now]) {
            if (v == father[now] or v == son[now]) continue;
            dfs2(adj, v, v);
        }
        max_dfn[now] = tot - 1;
    }
    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (depth[top[u]] > depth[top[v]]) {
                u = father[top[u]];
            } else {
                v = father[top[v]];
            }
        }
        return depth[u] < depth[v] ? u : v;
    }
    int distance(int u, int v) {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }
    int kth_ancestor(int x, int k) {
        // assert(x >= 0 && k >= 0);
        if (depth[x] - 1 < k) return no_ancestor;
        // depth[x] - depth[top[x]] : 该重链上的祖先个数
        while (depth[x] - depth[top[x]] < k) {
            k -= depth[x] - depth[top[x]] + 1;
            x = father[top[x]];
        }
        // 此时祖先在当前重链内
        return id[dfn[x] - k];
    }
};
} // namespace OI::Graph::WithoutWeight

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

using namespace OI::Graph::WithoutWeight;
using namespace OI::DataStructure;

constexpr int P = 1e9 + 7;

using Infomation = long long;
Infomation seg_merge(Infomation x, Infomation y) {
    return (x + y) % P;
}

struct Modification {
    int add = 0;
    bool isZero() const { return add == 0; }
};
void seg_update(SegmentTreeNode<Infomation, Modification>& node, const Modification& mod) {
    if (mod.isZero()) return;
    node.val = (node.val + (node.right - node.left) * mod.add % P) % P;
    node.mod.add = (node.mod.add + mod.add) % P;
}

class Solution {
public:
    vector<int> bonus(int n, vector<vector<int>>& leadership, vector<vector<int>>& operations) {
        Adjacency adj(n);
        for (auto&& vec : leadership) {
            int a{vec[0] - 1}, b{vec[1] - 1};
            adj[a].push_back(b);
        }
        TreeChain chain(adj, n, 0);
        auto &dfn{chain.dfn}, &max_dfn{chain.max_dfn};
        auto seg_init = [](Infomation& val, long long p) {
            val = 0;
        };
        SegmentTree<Infomation, Modification> seg(seg_init, seg_merge, seg_update, 0, n);
        std::vector<int> ans;
        for (auto&& vec : operations) {
            int op{vec[0]}, id{vec[1] - 1};
            if (op == 1) {
                int num{vec[2]};
                seg.modify(dfn[id], Modification(num));
            } else if (op == 2) {
                int num{vec[2]};
                seg.modify(dfn[id], max_dfn[id] + 1, Modification(num));
            } else {
                ans.push_back(seg.query(dfn[id], max_dfn[id] + 1));
            }
        }
        return ans;
    }
};