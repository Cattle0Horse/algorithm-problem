/**
 * @file tree_chain_v1.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief [1483. 树节点的第 K 个祖先](https://leetcode.cn/problems/kth-ancestor-of-a-tree-node/description/?envType=daily-question&envId=2024-04-06)
 * @version 1.1
 * @date 2024-04-05
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

    TreeChain(const Adjacency& adj, int n, int root = 0)
        : father(n, -1), son(n, son_init), depth(n, -1), top(n, -1), size(n, -1) {
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
        if (son[now] == son_init) return;
        dfs2(adj, son[now], top_id);
        for (auto&& v : adj[now]) {
            if (v == father[now] or v == son[now]) continue;
            dfs2(adj, v, v);
        }
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
        while (k--) x = father[x];
        return x;
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

    std::vector<int> father, son, depth, top, size;

    TreeChain(const Adjacency<T>& adj, int n, int root)
        : father(n, -1), son(n, son_init), depth(n, -1), top(n, -1), size(n, -1) {
        dfs1(adj, root, -1);
        dfs2(adj, root, root);
    }
    void dfs1(const Adjacency<T>& adj, int now, int fa, int dep = 1) {
        depth[now] = dep;
        father[now] = fa;
        size[now] = 1;
        for (auto&& [v, w] : adj[now]) {
            if (v == fa) continue;
            dfs1(adj, v, now, dep + 1);
            size[now] += size[v];
            if (son[now] == son_init || size[v] > size[son[now]]) son[now] = v;
        }
    }
    void dfs2(const Adjacency<T>& adj, int now, int top_id) {
        top[now] = top_id;
        if (son[now] == son_init) return;
        dfs2(adj, son[now], top_id);
        for (auto&& [v, w] : adj[now]) {
            if (v == father[now] or v == son[now]) continue;
            dfs2(adj, v, v);
        }
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
        while (k--) x = father[x];
        return x;
    }
};
} // namespace OI::Graph::WithWeight

// [2846. 边权重均等查询](https://leetcode.cn/problems/minimum-edge-weight-equilibrium-queries-in-a-tree/description/)

#include <iostream>
#include <functional>


class Solution {
public:
    std::vector<int> minOperationsQueries(int n, std::vector<std::vector<int>>& edges, std::vector<std::vector<int>>& queries) {
        constexpr int root{0};
        constexpr int weight_size{26};

        OI::Graph::WithWeight::Adjacency<int> adj(n);
        for (auto&& edge : edges) {
            int u{edge[0]}, v{edge[1]}, w{edge[2] - 1};
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
        }

        std::vector<std::array<int, weight_size>> cnt(n);
        std::function<void(int, int)> dfs = [&](int u, int father) {
            for (auto&& [v, w] : adj[u]) {
                if (v == father) continue;
                std::copy(cnt[u].begin(), cnt[u].end(), cnt[v].begin());
                ++cnt[v][w];
                dfs(v, u);
            }
        };
        cnt[root].fill(0);
        dfs(root, -1);

        OI::Graph::WithWeight::TreeChain<int> tree{adj, n, root};
        auto size{queries.size()};
        std::vector<int> ans(size);
        for (size_t i = 0; i < size; ++i) {
            int x{queries[i][0]}, y{queries[i][1]};
            int lca{tree.lca(x, y)};
            int mx{0};
            for (size_t i = 0; i < weight_size; ++i) {
                mx = std::max(mx, cnt[x][i] + cnt[y][i] - 2 * cnt[lca][i]);
            }
            auto& depth{tree.depth};
            ans[i] = depth[x] + depth[y] - 2 * depth[lca] - mx;
        }
        return ans;
    }
};

int main() {
    Solution solution{};
    int n = 7;
    std::vector<std::vector<int>> edges{
        {0, 1, 1},
        {1, 2, 1},
        {2, 3, 1},
        {3, 4, 2},
        {4, 5, 2},
        {5, 6, 2}};
    std::vector<std::vector<int>> queriers{{0, 3}, {3, 6}, {2, 6}, {0, 6}};

    // int n{8};
    // std::vector<std::vector<int>> edges{{1, 2, 6}, {1, 3, 4}, {2, 4, 6}, {2, 5, 3}, {3, 6, 6}, {3, 0, 8}, {7, 0, 2}};
    // std::vector<std::vector<int>> queriers{{4, 6}, {0, 4}, {6, 5}, {7, 4}};

    for (auto&& v : solution.minOperationsQueries(n, edges, queriers)) {
        std::cout << v << ' ';
    }
}