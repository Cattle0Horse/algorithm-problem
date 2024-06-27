/**
 * @file leetcode_2280.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/minimum-lines-to-represent-a-line-chart/description/
 * @version 0.1
 * @date 2024-06-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <utility>
#ifdef OY_LOCAL
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;
#endif

[[maybe_unused]] auto _ = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();

template<typename T>
struct Point {
    T x, y;
    Point(const T& a, const T& b): x(a), y(b) {}
    template<typename U>
    Point(const std::vector<U>& p): x(p[0]), y(p[1]) {}
    template<typename U>
    Point(const std::pair<U, U>& p): x(p.first), y(p.second) {}
};

template<typename T>
T slope(const Point<T>& a, const Point<T>& b) {
    return (b.y - a.y) / (b.x - a.x);
}

template<typename T>
T distance(const Point<T>& a, const Point<T>& b) {
    return (b.y - a.y) * (b.x - a.x);
}
template<typename T>
bool isCollinear(const Point<T>& a, const Point<T>& b, const Point<T>& c) {
    return (a.y - b.y) * (a.x - c.x) == (a.x - b.x) * (a.y - c.y);
}

class Solution {
public:
    // 判断斜率是否相等
    int minimumLines(vector<vector<int>>& stockPrices) {
        using P = Point<long long>;
        std::ranges::sort(stockPrices);
        int n = stockPrices.size();
        int ans = n - 1;
        for (auto i{2}; i < n; ++i) {
            ans -= isCollinear(P(stockPrices[i - 2]), P(stockPrices[i - 1]), P(stockPrices[i]));
        }
        return ans;
    }
};