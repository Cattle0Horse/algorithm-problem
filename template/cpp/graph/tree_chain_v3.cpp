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

namespace OI::Graph::WithWeight {
template<typename T>
using Adjacency = std::vector<std::vector<std::pair<int, T>>>;

template<typename T>
struct TreeChain {
    constexpr static int son_init{-1};
    constexpr static int no_ancestor{-1};
    constexpr static int root_depth{1};

    std::vector<int> father, son, depth, top, size;
    // 为了实现k快速查找k级祖先
    // dfn : 树链剖分的dfs序
    // id  : dfn对应的原节点编号
    // 二者互为映射关系
    std::vector<int> dfn, id, max_dfn;
    int tot;

    TreeChain(const Adjacency<T>& adj, int n, int root = 0)
        : father(n, -1), son(n, son_init), depth(n, -1), top(n, -1), size(n, -1), dfn(n), id(n), max_dfn(n), tot(0) {
        dfs1(adj, root, -1);
        dfs2(adj, root, root);
    }
    void dfs1(const Adjacency<T>& adj, int now, int fa, int dep = root_depth) {
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
    void dfs2(const Adjacency<T>& adj, int now, int top_id) {
        top[now] = top_id;
        dfn[now] = tot++;
        id[dfn[now]] = now;
        if (son[now] == son_init) {
            max_dfn[now] = dfn[now];
            return;
        }
        dfs2(adj, son[now], top_id);
        for (auto&& v : adj[now]) {
            if (v == father[now] || v == son[now]) continue;
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
} // namespace OI::Graph::WithWeight