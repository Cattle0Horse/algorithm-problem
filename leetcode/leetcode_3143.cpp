// @date 2024/8/3 10:14:02
// @author Cattle_Horse (CattleHorse@duck.com)
// @problem 3143. 正方形中的最多点数
// @link https://leetcode.cn/classic/problems/maximum-points-inside-the-square/description/

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
    int maxPointsInsideSquare(vector<vector<int>>& points, string s) {
        int n = s.length();
        dbg(n);
        auto check = [&](int side) -> bool {
            std::unordered_set<char> has;
            for (auto i{0}; i < n; i += 1) {
                if (std::abs(points[i][0]) <= side && std::abs(points[i][1]) <= side) {
                    if (!has.insert(s[i]).second) {
                        return true;
                    }
                }
            }
            return false;
        };
        int mx = -1;
        for (auto&& p : points) {
            mx = std::max({mx, std::abs(p[0]), std::abs(p[1])});
        }
        int last_false = -1, first_true = mx + 1;
        while (last_false + 1 < first_true) {
            int mid = (last_false + first_true) >> 1;
            dbg(mid);
            if (check(mid)) {
                first_true = mid;
            } else {
                last_false = mid;
            }
        }
        int side = last_false;
        return std::ranges::count_if(points, [&](const std::vector<int>& p) {
            return std::abs(p[0]) <= side && std::abs(p[1]) <= side;
        });
    }
};

// int Solution::maxPointsInsideSquare(vector<vector<int>> points, string s)

#ifdef Cattle_Horse
int main() {
    std::cout << "*** 3143. 正方形中的最多点数 ***" << std::endl
              << std::endl;

    Solution s0;

    {
        std::cout << "Test 1: ";

        vector<vector<int>> points = {{2, 2}, {-1, -2}, {-4, 4}, {-3, 1}, {3, -3}};
        string s = "abdca";
        int ans0 = s0.maxPointsInsideSquare(points, s);
        int exp0 = 2;

        if (ans0 == exp0) {
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
            std::cout << "  Answer: " << ans0 << std::endl;
            std::cout << "  Expect: " << exp0 << std::endl;
        }
    }

    {
        std::cout << "Test 2: ";

        vector<vector<int>> points = {{1, 1}, {-2, -2}, {-2, 2}};
        string s = "abb";
        int ans1 = s0.maxPointsInsideSquare(points, s);
        int exp1 = 1;

        if (ans1 == exp1) {
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
            std::cout << "  Answer: " << ans1 << std::endl;
            std::cout << "  Expect: " << exp1 << std::endl;
        }
    }

    {
        std::cout << "Test 3: ";

        vector<vector<int>> points = {{1, 1}, {-1, -1}, {2, -2}};
        string s = "ccd";
        int ans2 = s0.maxPointsInsideSquare(points, s);
        int exp2 = 0;

        if (ans2 == exp2) {
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
            std::cout << "  Answer: " << ans2 << std::endl;
            std::cout << "  Expect: " << exp2 << std::endl;
        }
    }

    // [[-1,-4],[16,-8],[13,-3],[-12,0]]
    {
        std::cout << "Test 4: ";

        vector<vector<int>> points = {{-1, -4}, {16, -8}, {13, -3}, {-12, 0}};
        string s = "abda";
        int ans2 = s0.maxPointsInsideSquare(points, s);
        int exp2 = 1;

        if (ans2 == exp2) {
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
            std::cout << "  Answer: " << ans2 << std::endl;
            std::cout << "  Expect: " << exp2 << std::endl;
        }
    }

    return 0;
}
#endif
