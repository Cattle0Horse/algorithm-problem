// @date 2024/7/21 00:11:23
// @author Cattle_Horse (CattleHorse@duck.com)
// @problem 1186. 删除一次得到子数组最大和
// @link https://leetcode.cn/classic/problems/maximum-subarray-sum-with-one-deletion/description/

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
    int maximumSum(vector<int>& arr) {
        int n = arr.size();
        if (n == 1) return arr[0];
        // dp目前是否删除了元素
        // 以当前位置结尾的最大连续子数组和(删除了或没删除元素)
        int ans = -0x3f3f3f3f;
        int dp[2]{ans, ans};
        for (int x : arr) {
            dp[1] = std::max(dp[1] + x, dp[0]);
            dp[0] = std::max(dp[0], 0) + x;
            ans = std::max({ans, dp[0], dp[1]});
        }
        return ans;
    }
};

// int Solution::maximumSum(vector<int> arr)

#ifdef Cattle_Horse
int main() {
    std::cout << "*** 1186. 删除一次得到子数组最大和 ***" << std::endl
              << std::endl;

    Solution s0;

    {
        std::cout << "Test 1: ";

        vector<int> arr = {1, -2, 0, 3};
        int ans0 = s0.maximumSum(arr);
        int exp0 = 4;

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

        vector<int> arr = {1, -2, -2, 3};
        int ans1 = s0.maximumSum(arr);
        int exp1 = 3;

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

        vector<int> arr = {-1, -1, -1, -1};
        int ans2 = s0.maximumSum(arr);
        int exp2 = -1;

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
