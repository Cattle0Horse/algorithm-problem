/**
 * @file leetcode_2959.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/number-of-possible-sets-of-closing-branches/?envType=daily-question&envId=2024-07-17
 * @version 0.1
 * @date 2024-07-17
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifdef Cattle_Horse
#include "leetcode.h" // IWYU pragma: keep
using namespace std;
#else
#define dbg(...) void(114514)
#endif

[[maybe_unused]] auto __init_io__ = []() {
    return std::cin.tie(nullptr)->sync_with_stdio(false);
}();

constexpr int INF = 0x3f3f3f3f;
class Solution {
public:
    int numberOfSets(int n, int maxDistance, vector<vector<int>>& roads) {
        std::vector<std::vector<int>> mat(n, std::vector<int>(n, INF));
        for (auto& road : roads) {
            int u = road[0], v = road[1], w = road[2];
            mat[u][v] = std::min(mat[u][v], w);
            mat[v][u] = std::min(mat[v][u], w);
        }
        for (auto i{0}; i < n; ++i) {
            mat[i][i] = 0;
        }
        auto check = [&](uint32_t s) -> bool {
            if ((s & (s - 1)) == 0) return true;
            
            std::vector<std::vector<int>> dis(mat);
            for (int i = 0; i < n; ++i) {
                if (!(s >> i & 1)) {
                    for (int j = 0; j < n; ++j) {
                        dis[i][j] = dis[j][i] = INF;
                    }
                }
            }

            for (auto k{0}; k < n; ++k) {
                for (auto i{0}; i < n; ++i) {
                    for (auto j{0}; j < n; ++j) {
                        if (dis[i][j] > dis[i][k] + dis[k][j]) {
                            dis[i][j] = dis[i][k] + dis[k][j];
                        }
                    }
                }
            }
            // 判断保留的节点之间的最短路是否均不超过 maxDistance
            for (int i = 0; i < n; i++) {
                if (((s >> i) & 1) == 0) continue;
                for (int j = 0; j < n; j++) {
                    if ((s >> j) & 1 && dis[i][j] > maxDistance) {
                        return false;
                    }
                }
            }
            return true;
        };
        int ans = 1;
        for (uint32_t s = 1, S = 1 << n; s < S; ++s) {
            ans += check(s);
        }
        return ans;
    }
};

#ifdef Cattle_Horse
int main() {
    //
}
#endif