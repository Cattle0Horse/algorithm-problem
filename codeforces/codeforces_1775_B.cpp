/**
 * @file codeforces_1775_B.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://codeforces.com/problemset/problem/1775/B
 * @version 0.1
 * @date 2024-04-23
 *
 * @copyright Copyright (c) 2024
 *
 * 题意：
 *
 * 输入 T(≤1e5) 表示 T 组数据。所有数据的 k 之和 ≤1e5。
 * 每组数据输入 n(1≤n≤1e5) 和 n 行，每行输入 k(1≤k≤1e5) 和 k 个不同数字，范围 [1,2e5]。
 * 这 k 个数字表示一个二进制数比特 1 的位置。
 * 例如给你 2,3,5 表示二进制 101100（从右往左读）。
 * 所以，输入相当于给你一个长为 n 的数组，包含 n 个二进制数。
 *
 * 你需要从数组中选择两个不同的子序列，使得这两个子序列的 OR（按位或）相等。
 * 能否做到？输出 Yes 或 No。
 *
 * 注：子序列不要求连续。
 * 注：只要有一个元素的下标不在另一个子序列的元素下标中，两个子序列就算不同的。
 * 例如 [1,1,1] 中有 三个 不同的子序列 [1,1]。
 *
 *
 * 解析：
 *
 * 把所有数进行或运算记为a，选出一个删掉，看剩下的或运算是不是a的子集。
 * 可以记录每一个位置出现1的次数，删掉的那个数要满足它的1的位置减去后不为0
 */

#include <bits/stdc++.h>
using namespace std;

bool solve() {
    int n, k;
    cin >> n;
    unordered_map<int, int> cnt;
    vector<vector<int>> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> k;
        arr[i].resize(k);
        for (int j = 0; j < k; ++j) {
            cin >> arr[i][j];
            ++cnt[arr[i][j]];
        }
    }
    for (auto& num : arr) {
        if (std::none_of(num.begin(), num.end(), [&](int x) {
                return cnt[x] == 1;
            })) {
            return true;
        }
    }
    return false;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        cout << (solve() ? "Yes" : "No") << endl;
    }
}