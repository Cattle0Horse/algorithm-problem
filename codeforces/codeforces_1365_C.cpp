/**
 * @file codeforces_1365_c.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://codeforces.com/problemset/problem/1365/C
 * @version 0.1
 * @date 2024-04-29
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
#include <iostream>
#include <vector>
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> pos(n);
    for (int i = 0, x; i < n; ++i) {
        std::cin >> x;
        pos[x - 1] = i;
    }
    std::vector<int> cnt(n);
    for (int i = 0, x; i < n; ++i) {
        std::cin >> x;
        --x;
        // the number of times that x needs to move to the right
        int y = i <= pos[x] ? pos[x] - i : n - i + pos[x];
        ++cnt[y];
    }
    std::cout << *std::max_element(cnt.begin(), cnt.end()) << std::endl;
    return 0;
}