/**
 * @file leetcode_2718.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/sum-of-matrix-after-queries/description/
 * @version 0.1
 * @date 2024-07-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <ranges>
#ifdef OY_LOCAL
#include "leetcode.h" // IWYU pragma: keep
using namespace std;
#else
#define dbg(...) void(114514)
#endif

[[maybe_unused]] auto __init_io__ = []() {
    return std::cin.tie(nullptr)->sync_with_stdio(false);
}();

class Solution {
public:
    // long long matrixSumQueries(int n, vector<vector<int>>& queries) {
    //     std::vector<std::pair<int, int>> row(n, {-1, -1}), col(n, {-1, -1});
    //     for (auto i{0u}; i < queries.size(); i += 1) {
    //         int type = queries[i][0], index = queries[i][1], val = queries[i][2];
    //         if (type == 0) {
    //             row[index] = {i, val};
    //         } else {
    //             col[index] = {i, val};
    //         }
    //     }
    //     long long ans = 0;
    //     for (auto i{0}; i < n; i += 1) {
    //         for (auto j{0}; j < n; j += 1) {
    //             if (row[i].first == -1 && col[j].first == -1) {
    //                 ans += 0;
    //             } else if (row[i].first > col[j].first) {
    //                 ans += row[i].second;
    //             } else {
    //                 ans += col[j].second;
    //             }
    //         }
    //     }
    //     return ans;
    // }

    // 逆序操作(只有最后一个出现的会对答案做出贡献)...记录有多少个没有被操作的数
    long long matrixSumQueries(int n, vector<vector<int>>& queries) {
        long long ans = 0;
        std::unordered_set<int> vis[2];
        for (auto&& query : views::reverse(queries)) {
            int type = query[0], index = query[1], val = query[2];
            if (!vis[type].contains(index)) {
                ans += static_cast<long long>(n - vis[type ^ 1].size()) * val;
                vis[type].insert(index);
            }
        }
        return ans;
    }
};

#ifdef OY_LOCAL
int main() {
    //
}
#endif