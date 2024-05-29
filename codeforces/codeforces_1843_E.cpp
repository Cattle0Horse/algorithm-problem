/**
 * @file codeforces_1843_E.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://codeforces.com/problemset/problem/1843/E
 * @version 0.1
 * @date 2024-05-29
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

[[maybe_unused]] auto _ = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();

int testcase() {
    int n, m, q;
    std::cin >> n >> m;
    std::vector<int> left(m), right(m);
    for (int i{0}; i < m; ++i) {
        std::cin >> left[i] >> right[i];
    }
    std::cin >> q;
    std::vector<int> queries(q);
    for (int i{0}; i < q; ++i) {
        std::cin >> queries[i];
    }
    std::vector<int> a(n + 1);
    auto check = [&](int index) -> bool {
        std::fill(a.begin(), a.end(), 0);
        for (int i{0}; i < index; ++i) {
            a[queries[i]] = 1;
        }
        std::partial_sum(a.begin(), a.end(), a.begin());
        for (int i{0}; i < m; ++i) {
            int l = left[i], r = right[i];
            int cnt = a[r] - a[l - 1];
            if (cnt > r - l + 1 - cnt) {
                return true;
            }
        }
        return false;
    };
    // find the first index of check == true
    int l = 0, r = q + 1;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    return r == q + 1 ? -1 : r;
}

int main() {
    int _;
    std::cin >> _;
    while (_--) {
        std::cout << testcase() << std::endl;
    }
    return 0;
}