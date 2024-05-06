/**
 * @file codeforces_1759_D.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://codeforces.com/problemset/problem/1759/D
 * @version 0.1
 * @date 2024-05-06
 *
 * @copyright Copyright (c) 2024
 * 设 n 的质因子分解中有 c2 个 2 和 c5 个 5。
 *
 * 如果 c2 < c5，那么不断把 n 乘以 2 直到 c2 = c5。
 * 如果 c5 < c2，那么不断把 n 乘以 5 直到 c2 = c5。
 *
 * 把 n 乘上的系数记作 k，如果 10k <= m 就继续乘 10。
 *
 * 由于要输出最大的数，我们需要让 k 变成 k 的若干倍，同时不超过 m。
 * 我们可以把 k 变成 (m/k)*k = m-m%k。
 */

#include <iostream>
using i64 = long long;

void testcase() {
    auto getFactorCount = [](i64 n, int f) {
        int cnt = 0;
        while (n % f == 0) {
            n /= f;
            ++cnt;
        }
        return cnt;
    };
    i64 n, m, k = 1;
    std::cin >> n >> m;
    int c2 = getFactorCount(n, 2), c5 = getFactorCount(n, 5);
    while (c2 < c5 && k * 2 <= m) {
        c2++;
        k *= 2;
    }
    while (c5 < c2 && k * 5 <= m) {
        c5++;
        k *= 5;
    }
    while (k * 10 <= m) {
        k *= 10;
    }
    // find a multiple of k, and less than or equal to m
    k *= m / k;
    std::cout << n * k << std::endl;
}

int main() {
    int _;
    std::cin >> _;
    while (_--) {
        testcase();
    }
    return 0;
}