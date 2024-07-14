/**
 * @file leetcode_1942.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/the-number-of-the-smallest-unoccupied-chair/description/
 * @version 0.1
 * @date 2024-07-14
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifdef OY_LOCAL
#include "leetcode.h" // IWYU pragma: keep
using namespace std;
#else
#define dbg(...) void(114514)
#endif

[[maybe_unused]] auto __init_io__ = []() {
    return std::cin.tie(nullptr)->sync_with_stdio(false);
}();

template<typename T, typename Compare = std::less<T>, typename Container = std::vector<T>>
using PriorityQueue = std::priority_queue<T, Container, Compare>;
template<typename T, typename Container = std::vector<T>>
using MaxPriorityQueue = PriorityQueue<T, std::less<T>, Container>;
template<typename T, typename Container = std::vector<T>>
using MinPriorityQueue = PriorityQueue<T, std::greater<T>, Container>;

class Solution {
public:
    int smallestChair(vector<vector<int>>& times, int targetFriend) {
        int n = times.size();
        std::vector<int> id(n);
        std::iota(id.begin(), id.end(), 0);
        std::ranges::sort(id, [&](int i, int j) {
            return times[i] < times[j];
        });
        MinPriorityQueue<int> chair;
        for (auto i{0}; i < n; i += 1) {
            chair.push(i);
        }
        auto cmp = [&](const std::pair<int, int>& a, const std::pair<int, int>& b) {
            return times[a.first][1] > times[b.first][1];
        };
        PriorityQueue<std::pair<int,int>, decltype(cmp)> leaving(cmp);
        for (int i : id) {
            auto& cur{times[i]};
            while (!leaving.empty() && times[leaving.top().first][1] <= cur[0]) {
                // 归还椅子
                chair.push(leaving.top().second);
                leaving.pop();
            }
            // 占用椅子
            int vis = chair.top();
            chair.pop();
            leaving.emplace(i, vis);
            if (i == targetFriend) {
                return vis;
            }
        }
        return -1;
    }
};

#ifdef OY_LOCAL
int main() {
    //
}
#endif