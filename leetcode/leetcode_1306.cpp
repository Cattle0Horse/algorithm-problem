/**
 * @file leetcode_1306.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/jump-game-iii/description/
 * @version 0.1
 * @date 2024-06-19
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <functional>
#include <queue>
#include <set>
#include <unordered_map>
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

class Solution {
public:
    bool canReach(vector<int>& arr, int start) {
        if (start == 0) return true;
        int n = arr.size();
        std::vector<bool> vis(n);
        std::queue<int> q;
        auto push = [&](int i) {
            if ((0 <= i && i < n) && !vis[i]) {
                q.push(i);
                vis[i] = true;
            }
        };
        push(start);

        while (!q.empty()) {
            int i = q.front();
            if (i == 0) return true;
            q.pop();
            push(i + arr[i]);
            push(i - arr[i]);
        }
        return false;
    }
};

class Solution2 {
public:
    bool canReach(vector<int>& arr, int start) {
        if (arr[start] == 0) return true;
        int n = arr.size();
        std::unordered_map<int, bool> memo;
        std::function<bool(int)> dfs = [&](int i) -> bool {
            if (!(0 <= i && i < n)) return false;
            if (memo.contains(i)) return memo[i];
            memo[i] = false;
            return memo[i] = dfs(i + arr[i]) || dfs(i - arr[i]);
        };
        return dfs(start);
    }
};