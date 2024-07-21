// @date 2024/7/20 18:51:32
// @author Cattle_Horse (CattleHorse@duck.com)
// @problem 2769. 找出最大的可达成数字
// @link https://leetcode.cn/contest/weekly-contest-353/problems/find-the-maximum-achievable-number/description/

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
    int theMaximumAchievableX(int num, int t) {
        return num + 2 * t;
    }
};

// int Solution::theMaximumAchievableX(int num, int t)

#ifdef Cattle_Horse
int main() {
    std::cout << "*** 2769. 找出最大的可达成数字 ***" << std::endl
              << std::endl;

    Solution s0;

    {
        std::cout << "Test 1: ";

        int num = 4;
        int t = 1;
        int ans0 = s0.theMaximumAchievableX(num, t);
        int exp0 = 6;

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

        int num = 3;
        int t = 2;
        int ans1 = s0.theMaximumAchievableX(num, t);
        int exp1 = 7;

        if (ans1 == exp1) {
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
            std::cout << "  Answer: " << ans1 << std::endl;
            std::cout << "  Expect: " << exp1 << std::endl;
        }
    }

    return 0;
}
#endif
