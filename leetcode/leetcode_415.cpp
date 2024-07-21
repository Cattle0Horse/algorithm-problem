// @date 2024/7/21 12:08:44
// @author Cattle_Horse (CattleHorse@duck.com)
// @problem 415. 字符串相加
// @link https://leetcode.cn/classic/problems/add-strings/description/

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
    string addStrings(string num1, string num2) {
        std::cout << '\n';
        std::ranges::reverse(num1);
        std::ranges::reverse(num2);
        dbg(num1, num2);
        std::string ans{};
        uint32_t n = num1.size(), m = num2.size();
        int carry = 0;
        for (auto i{0u}; i < n || i < m; i += 1) {
            int a = i >= n ? 0 : num1[i] - '0', b = i >= m ? 0 : num2[i] - '0';
            int cur = a + b + carry;
            ans += cur % 10 + '0';
            carry = cur / 10;
        }
        if (carry != 0) ans += carry + '0';
        std::ranges::reverse(ans);
        return ans;
    }
};

// string Solution::addStrings(string num1, string num2)

#ifdef Cattle_Horse
int main() {
    std::cout << "*** 415. 字符串相加 ***" << std::endl
              << std::endl;

    Solution s0;

    {
        std::cout << "Test 1: ";

        string num1 = "11";
        string num2 = "123";
        string ans0 = s0.addStrings(num1, num2);
        string exp0 = "134";

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

        string num1 = "456";
        string num2 = "77";
        string ans1 = s0.addStrings(num1, num2);
        string exp1 = "533";

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

        string num1 = "0";
        string num2 = "0";
        string ans2 = s0.addStrings(num1, num2);
        string exp2 = "0";

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
