// @date 2024/8/17 09:02:15
// @author Cattle_Horse (CattleHorse@duck.com)
// @problem 3048. 标记所有下标的最早秒数 I
// @link https://leetcode.cn/classic/problems/earliest-second-to-mark-indices-i/description/

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
    int earliestSecondToMarkIndices(vector<int>& nums, vector<int>& changeIndices) {
        int n = nums.size(), m = changeIndices.size();
        // 二分答案，目前拥有的秒数，并且二分答案的区间保证秒数足够
        auto check = [&](int second) -> bool {
            std::vector<bool> done(n);
            int done_cnt = 0;
            int study = 0;
            for (auto i{second - 1}; i >= 0; i -= 1) {
                int idx = changeIndices[i] - 1;
                if (!done[idx]) {
                    done[idx] = true;
                    done_cnt += 1;
                    study += nums[idx];
                } else if (study > 0) {
                    study -= 1;
                }
            }
            return done_cnt == n && study == 0;
        };
        long long last_false = std::accumulate(nums.begin(), nums.end(), 0LL) + n - 1, first_true = m + 1;
        while (last_false + 1 < first_true) {
            int mid = (last_false + first_true) >> 1;
            if (check(mid)) {
                first_true = mid;
            } else {
                last_false = mid;
            }
        }
        return first_true == m + 1 ? -1 : first_true;
    }
};

// int Solution::earliestSecondToMarkIndices(vector<int> nums, vector<int> changeIndices)

#ifdef Cattle_Horse
int main() {
    std::cout << "*** 3048. 标记所有下标的最早秒数 I ***" << std::endl
              << std::endl;

    Solution s0;

    {
        std::cout << "Test 1: ";

        vector<int> nums = {2, 2, 0};
        vector<int> changeIndices = {2, 2, 2, 2, 3, 2, 2, 1};
        int ans0 = s0.earliestSecondToMarkIndices(nums, changeIndices);
        int exp0 = 8;

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

        vector<int> nums = {1, 3};
        vector<int> changeIndices = {1, 1, 1, 2, 1, 1, 1};
        int ans1 = s0.earliestSecondToMarkIndices(nums, changeIndices);
        int exp1 = 6;

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

        vector<int> nums = {0, 1};
        vector<int> changeIndices = {2, 2, 2};
        int ans2 = s0.earliestSecondToMarkIndices(nums, changeIndices);
        int exp2 = -1;

        if (ans2 == exp2) {
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
            std::cout << "  Answer: " << ans2 << std::endl;
            std::cout << "  Expect: " << exp2 << std::endl;
        }
    }

    {
        std::cout << "Test 4: ";

        vector<int> nums = {0, 2, 3, 0};
        vector<int> changeIndices = {2, 4, 1, 3, 3, 3, 3, 3, 3, 2, 1};
        int ans2 = s0.earliestSecondToMarkIndices(nums, changeIndices);
        int exp2 = 10;

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
