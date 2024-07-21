// @date 2024/7/20 19:09:49
// @author Cattle_Horse (CattleHorse@duck.com)
// @problem 2771. 构造最长非递减子数组
// @link https://leetcode.cn/contest/weekly-contest-353/problems/longest-non-decreasing-subarray-from-two-arrays/description/

#ifdef Cattle_Horse
#include "leetcode.h" // IWYU pragma: keep
using namespace std;
#else
#define dbg(...) void(114514)
#endif

[[maybe_unused]] auto __init_io__ = []() {
    return std::cin.tie(nullptr)->sync_with_stdio(false);
}();

// todo: Not pass
class Solution {
public:
    int maxNonDecreasingLength(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), ans = 1;
        std::vector<int> dp_min(n, 1);
        std::vector<int> dp_max(n, 1);

        int pre_mn = std::min(nums1[0], nums2[0]);
        int pre_mx = std::max(nums1[0], nums2[0]);
        for (auto i{1}; i < n; i += 1) {
            auto&& [mn, mx] = std::minmax(nums1[i], nums2[i]);
            if (pre_mn <= mn) {
                dp_min[i] = dp_min[i - 1] + 1;
                dp_max[i] = dp_max[i - 1] + 1;
            } else if (pre_mn <= mx) {
                if (pre_mx <= mx) {
                    dp_max[i] = dp_max[i - 1] + 1;
                } else {
                    dp_max[i] = dp_min[i - 1] + 1;
                }
                dp_min[i] = 1;
            } else {
                dp_max[i] = dp_min[i] = 1;
            }
            pre_mn = mn, pre_mx = mx;
            ans = std::max({ans, dp_min[i], dp_max[i]});
        }
        std::cout << '\n';
        dbg(nums1, nums2);
        dbg(dp_min, dp_max);
        return ans;
    }
};

// int Solution::maxNonDecreasingLength(vector<int> nums1, vector<int> nums2)

#ifdef Cattle_Horse
int main() {
    std::cout << "*** 2771. 构造最长非递减子数组 ***" << std::endl
              << std::endl;

    Solution s0;

    {
        std::cout << "Test 1: ";

        vector<int> nums1 = {2, 3, 1};
        vector<int> nums2 = {1, 2, 1};
        int ans0 = s0.maxNonDecreasingLength(nums1, nums2);
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

        vector<int> nums1 = {1, 3, 2, 1};
        vector<int> nums2 = {2, 2, 3, 4};
        int ans1 = s0.maxNonDecreasingLength(nums1, nums2);
        int exp1 = 4;

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

        vector<int> nums1 = {1, 1};
        vector<int> nums2 = {2, 2};
        int ans2 = s0.maxNonDecreasingLength(nums1, nums2);
        int exp2 = 2;

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

        vector<int> nums1 = {7, 4, 4};
        vector<int> nums2 = {8, 7, 20};
        int ans3 = s0.maxNonDecreasingLength(nums1, nums2);
        int exp3 = 3;

        if (ans3 == exp3) {
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
            std::cout << "  Answer: " << ans3 << std::endl;
            std::cout << "  Expect: " << exp3 << std::endl;
        }
    }

    {
        std::cout << "Test 5: ";

        vector<int> nums1 = {5, 16, 15};
        vector<int> nums2 = {12, 1, 14};
        int ans3 = s0.maxNonDecreasingLength(nums1, nums2);
        int exp3 = 2;

        if (ans3 == exp3) {
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
            std::cout << "  Answer: " << ans3 << std::endl;
            std::cout << "  Expect: " << exp3 << std::endl;
        }
    }

    return 0;
}
#endif
