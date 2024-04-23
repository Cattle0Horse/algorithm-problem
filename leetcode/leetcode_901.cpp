/**
 * @file leetcode_901.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/online-stock-span/description/
 * @version 0.1
 * @date 2024-04-23
 *
 * @copyright Copyright (c) 2024
 *
 * 在线查找左边第一个大于当前元素的位置
 */

#include <bits/stdc++.h>
using namespace std;

class StockSpanner {
private:
    vector<int> v;
    stack<int> s;

public:
    StockSpanner() {}

    int next(int price) {
        v.push_back(price);
        while (!s.empty() && v[s.top()] <= price) {
            s.pop();
        }
        int leftmost = s.empty() ? 0 : s.top() + 1;
        s.push(v.size() - 1);
        return v.size() - leftmost;
    }
};

int main() {
    StockSpanner stockSpanner;
    cout << stockSpanner.next(100) << endl; // 返回 1
    cout << stockSpanner.next(80) << endl;  // 返回 1
    cout << stockSpanner.next(60) << endl;  // 返回 1
    cout << stockSpanner.next(70) << endl;  // 返回 2
    cout << stockSpanner.next(60) << endl;  // 返回 1
    cout << stockSpanner.next(75) << endl;  // 返回 4 ，因为截至今天的最后 4 个股价 (包括今天的股价 75) 都小于或等于今天的股价。
    cout << stockSpanner.next(85) << endl;  // 返回 6
    return 0;
}