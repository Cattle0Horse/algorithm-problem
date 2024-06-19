/**
 * @file leetcode_57.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/insert-interval/
 * @version 0.1
 * @date 2024-06-16
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <algorithm>
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
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        std::vector<std::vector<int>> ans;
        // if (intervals.empty()) return {newInterval};
        int& left = newInterval[0];
        int& right = newInterval[1];
        int i = 0, n = intervals.size();

#define start(i) (intervals[i][0])
#define end(i)   (intervals[i][1])
        // find the first index of left <= end
        for (; i < n && end(i) < left; ++i) ans.push_back(intervals[i]);

        // As long as the right >= start can be combined
        for (; i < n && start(i) <= right; ++i) {
            left = std::min(left, start(i));
            right = std::max(right, end(i));
        }
        ans.push_back(newInterval);

        // ending
        for (; i < n; ++i) ans.push_back(intervals[i]);

#undef start
#undef end
        return ans;
    }
};
int main() {
    std::vector<std::vector<int>> intervals{
        {1, 5}};
    std::vector<int> newInterval{0, 0};
    for (auto&& row : Solution().insert(intervals, newInterval)) {
        for (int v : row) {
            std::cout << v << ' ';
        }
        std::cout << std::endl;
    };
    return 0;
}