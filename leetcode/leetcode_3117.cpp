// @date 2024/8/16 21:46:23
// @author Cattle_Horse (CattleHorse@duck.com)
// @problem 3117. 划分数组得到最小的值之和
// @link https://leetcode.cn/classic/problems/minimum-sum-of-values-by-dividing-array/description/

#ifdef Cattle_Horse
#include "leetcode.h" // IWYU pragma: keep
using namespace std;
#else
#define dbg(...) void(114514)
#endif

[[maybe_unused]] auto __init_io__ = []() {
    return std::cin.tie(nullptr)->sync_with_stdio(false);
}();

constexpr int INF = std::numeric_limits<int>::max(), INIT = -1;

class Solution {
public:
    int minimumValueSum(vector<int>& nums, vector<int>& andValues) {
        int n = nums.size(), m = andValues.size();
        std::vector<std::vector<std::unordered_map<int, int>>> dp(n, std::vector<std::unordered_map<int, int>>(m));
        // i: the index of nums
        // j: the number of segment
        // val: current & sum
        auto dfs = [&](auto&& self, int i, int j, int val) -> int {
            // not enough
            if (n - i < m - j) return INF;
            // finish
            if (j == m) return i == n ? 0 : INF;
            if (dp[i][j].contains(val)) return dp[i][j][val];
            // current segment & sum
            int sum = val == INIT ? nums[i] : val & nums[i];
            // continue to choose
            int ans = self(self, i + 1, j, sum);
            // construct the next segment
            if (sum == andValues[j]) {
                int res = self(self, i + 1, j + 1, INIT);
                if (res != INF) {
                    ans = std::min(ans, res + nums[i]);
                }
            }
            return dp[i][j][val] = ans;
        };
        int ans = dfs(dfs, 0, 0, INIT);
        return ans == INF ? -1 : ans;
    }
};

// int Solution::minimumValueSum(vector<int> nums, vector<int> andValues)

#ifdef Cattle_Horse
int main() {
    std::cout << "*** 3117. 划分数组得到最小的值之和 ***" << std::endl
              << std::endl;

    Solution s0;

    {
        std::cout << "Test 1: ";

        vector<int> nums = {1, 4, 3, 3, 2};
        vector<int> andValues = {0, 3, 3, 2};
        int ans0 = s0.minimumValueSum(nums, andValues);
        int exp0 = 12;

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

        vector<int> nums = {2, 3, 5, 7, 7, 7, 5};
        vector<int> andValues = {0, 7, 5};
        int ans1 = s0.minimumValueSum(nums, andValues);
        int exp1 = 17;

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

        vector<int> nums = {1, 2, 3, 4};
        vector<int> andValues = {2};
        int ans2 = s0.minimumValueSum(nums, andValues);
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
