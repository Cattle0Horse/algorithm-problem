/**
 * @file leetcode_841.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/keys-and-rooms/
 * @version 0.1
 * @date 2024-07-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <queue>
#ifdef OY_LOCAL
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;
#endif

[[maybe_unused]] auto __init_io__ = []() {
    return std::cin.tie(nullptr)->sync_with_stdio(false);
}();

class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        int n = rooms.size();
        std::vector<bool> vis(n);
        std::queue<int> q;
        q.push(0);
        vis[0] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : rooms[u]) {
                if (vis[v]) continue;
                q.push(v);
                vis[v] = true;
            }
        }
        return std::ranges::all_of(vis, [](bool b) {
            return b == true;
        });
    }
};