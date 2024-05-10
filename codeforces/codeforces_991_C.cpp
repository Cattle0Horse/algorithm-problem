/**
 * @file codeforces_991_C.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://codeforces.com/problemset/problem/991/C
 * @version 0.1
 * @date 2024-05-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>
using i64 = long long;
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    i64 n;
    std::cin >> n;
    i64 target = n - (n >> 1);
    auto check = [&](i64 k) {
        i64 cnt = 0, m = n;
        while (m >= k) {
            m -= k;
            cnt += k;
            m -= m / 10;
        }
        cnt += m;
        return cnt >= target;
    };
    i64 l = 0, r = n;
    while (l + 1 < r) {
        i64 mid = (l + r) >> 1;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    std::cout << r << std::endl;
    return 0;
}