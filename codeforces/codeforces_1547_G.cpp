/**
 * @file codeforces_1547_G.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://codeforces.com/contest/1547/problem/G
 * @version 0.1
 * @date 2024-04-25
 *
 * @copyright Copyright (c) 2024
 *
 * 如果终点的路径上有环，那么它的路径就有无限条
 */

#include <functional>
#include <iostream>
#include <unordered_set>
#include <vector>

constexpr int NO_PATH{0}, ONLY_ONE_PATH{1}, MULTIPLY_PATH{2}, INFINITY_PATH{-1};

void testcase() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> g(n);
    std::vector<bool> is_cycle(n, false);
    for (int i = 0, u, v; i < m; ++i) {
        std::cin >> u >> v;
        if (--u == --v) {
            is_cycle[u] = true;
        } else {
            g[u].push_back(v);
        }
    }
    std::vector<int> ans(n, NO_PATH);
    std::unordered_set<int> path_node;
    std::function<void(int)> dfs1 = [&](int cur) {
        if (path_node.contains(cur)) {
            is_cycle[cur] = true;
            return;
        }
        path_node.insert(cur);
        for (int v : g[cur]) {
            dfs1(v);
        }
        path_node.erase(cur);
    };
    dfs1(0);
    std::function<void(int, bool)> dfs2 = [&](int cur, bool had_cycle) {
        if (had_cycle) {
            is_cycle[cur] = true;
        }
        ++ans[cur];
        for (int v : g[cur]) {
            dfs2(v, is_cycle[cur]);
        }
    };
    dfs2(0, is_cycle[0]);
    for (int i = 0; i < n; ++i) {
        if (is_cycle[i]) {
            ans[i] = INFINITY_PATH;
        } else if (ans[i] > 2) {
            ans[i] = 2;
        }
        std::cout << ans[i] << " \n"[i == n - 1];
    }
}

int main() {
    int _;
    std::cin >> _;
    while (_--) {
        testcase();
    }
    return 0;
}