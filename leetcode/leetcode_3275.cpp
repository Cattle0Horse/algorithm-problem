// @date 2024/9/1 23:44:13
// @author Cattle_Horse (CattleHorse@duck.com)
// @problem 3275. 第 K 近障碍物查询
// @link https://leetcode.cn/classic/problems/k-th-nearest-obstacle-queries/description/

#ifdef Cattle_Horse
#include "leetcode.h" // IWYU pragma: keep
using namespace std;
#else
#define dbg(...) void(114514)
#endif

[[maybe_unused]] auto __init_io__ = []() {
    return std::cin.tie(nullptr)->sync_with_stdio(false);
}();

class Solution {
public:
    vector<int> resultsArray(vector<vector<int>>& queries, int k) {
        int n = queries.size();
        std::multiset<int> arr;
        std::vector<int> ans;
        ans.reserve(n);
        for (auto&& q : queries) {
            int dis = std::abs(q[0]) + std::abs(q[1]);
            arr.insert(dis);
            if (static_cast<int>(arr.size()) > k) {
                auto it = arr.end();
                std::advance(it, -1);
                arr.erase(it);
            }
            if (static_cast<int>(arr.size()) == k) {
                ans.push_back(*arr.rbegin());
            } else {
                ans.push_back(-1);
            }
        }
        return ans;
    }
};

/*
class Solution {
public:
    vector<int> resultsArray(vector<vector<int>>& queries, int k) {
        int n = queries.size();
        std::priority_queue<int, std::vector<int>, std::less<>> pq;
        std::vector<int> ans;
        ans.reserve(n);
        for (auto&& q : queries) {
            int dis = std::abs(q[0]) + std::abs(q[1]);
            pq.push(dis);
            if (pq.size() > k) {
                pq.pop();
            }
            if (pq.size() == k) {
                ans.push_back(pq.top());
            } else {
                ans.push_back(-1);
            }
        }
        return ans;
    }
};
*/

// vector<int> Solution::resultsArray(vector<vector<int>> queries, int k)

#ifdef Cattle_Horse
int main() {
    std::cout << "*** 3275. 第 K 近障碍物查询 ***" << std::endl
              << std::endl;

    Solution s0;

    {
        std::cout << "Test 1: ";

        vector<vector<int>> queries = {{1, 2}, {3, 4}, {2, 3}, {-3, 0}};
        int k = 2;
        vector<int> ans0 = s0.resultsArray(queries, k);
        vector<int> exp0 = {-1, 7, 5, 3};

        if (ans0 == exp0) {
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
            std::cout << "  Answer: ";
            for (int& i : ans0) {
                std::cout << i << " ";
            }
            std::cout << std::endl
                      << "  Expect: ";
            for (int& i : exp0) {
                std::cout << i << " ";
            }
            std::cout << std::endl;
        }
    }

    {
        std::cout << "Test 2: ";

        vector<vector<int>> queries = {{5, 5}, {4, 4}, {3, 3}};
        int k = 1;
        vector<int> ans1 = s0.resultsArray(queries, k);
        vector<int> exp1 = {10, 8, 6};

        if (ans1 == exp1) {
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
            std::cout << "  Answer: ";
            for (int& i : ans1) {
                std::cout << i << " ";
            }
            std::cout << std::endl
                      << "  Expect: ";
            for (int& i : exp1) {
                std::cout << i << " ";
            }
            std::cout << std::endl;
        }
    }

    return 0;
}
#endif
