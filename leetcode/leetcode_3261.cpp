// @date 2024/8/20 21:59:53
// @author Cattle_Horse (CattleHorse@duck.com)
// @problem 3261. 统计满足 K 约束的子字符串数量 II
// @link https://leetcode.cn/classic/problems/count-substrings-that-satisfy-k-constraint-ii/description/

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
    vector<long long> countKConstraintSubstrings(string s, int k, vector<vector<int>>& queries) {
        int n = s.length();
        std::array<int, 2> cnt{};
        std::vector<int> left(n);
        // [l, r]
        for (auto r{0}, l{0}; r < n; r += 1) {
            cnt[s[r] & 1] += 1;
            while (cnt[0] > k && cnt[1] > k) {
                cnt[s[l] & 1] -= 1;
                l += 1;
            }
            left[r] = l;
        }
        std::vector<int> pre(n + 1, 0);
        for (auto r{0}; r < n; r += 1) {
            int l = left[r];
            pre[r + 1] = pre[r] + (r - l + 1LL);
        }
        std::vector<long long> ans;
        ans.reserve(queries.size());
        for (auto&& q : queries) {
            int l = q[0], r = q[1];
            int L = std::lower_bound(left.begin() + l, left.begin() + r + 1, l) - left.begin();
            // [l, L]  [L, r]
            long long res = pre[r + 1] - pre[L] + static_cast<long long>(L - l + 1LL) * (L - l) / 2;
            ans.push_back(res);
        }
        return ans;
    }
};

// vector<long long> Solution::countKConstraintSubstrings(string s, int k, vector<vector<int>> queries)

#ifdef Cattle_Horse
int main() {
    std::cout << "*** 3261. 统计满足 K 约束的子字符串数量 II ***" << std::endl
              << std::endl;

    Solution s0;

    {
        std::cout << "Test 1: ";

        string s = "0001111";
        int k = 2;
        vector<vector<int>> queries = {{0, 6}};
        vector<long long> ans0 = s0.countKConstraintSubstrings(s, k, queries);
        vector<long long> exp0 = {26};

        if (ans0 == exp0) {
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
            std::cout << "  Answer: ";
            for (long long& i : ans0) {
                std::cout << i << " ";
            }
            std::cout << std::endl
                      << "  Expect: ";
            for (long long& i : exp0) {
                std::cout << i << " ";
            }
            std::cout << std::endl;
        }
    }

    {
        std::cout << "Test 2: ";

        string s = "010101";
        int k = 1;
        vector<vector<int>> queries = {{0, 5}, {1, 4}, {2, 3}};
        vector<long long> ans1 = s0.countKConstraintSubstrings(s, k, queries);
        vector<long long> exp1 = {15, 9, 3};

        if (ans1 == exp1) {
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
            std::cout << "  Answer: ";
            for (long long& i : ans1) {
                std::cout << i << " ";
            }
            std::cout << std::endl
                      << "  Expect: ";
            for (long long& i : exp1) {
                std::cout << i << " ";
            }
            std::cout << std::endl;
        }
    }

    return 0;
}
#endif
