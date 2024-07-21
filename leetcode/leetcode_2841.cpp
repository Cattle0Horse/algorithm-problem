// @date 2024/7/21 10:01:45
// @author Cattle_Horse (CattleHorse@duck.com)
// @problem 2841. 几乎唯一子数组的最大和
// @link https://leetcode.cn/classic/problems/maximum-sum-of-almost-unique-subarray/description/

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
    long long maxSum(vector<int>& nums, int m, int k) {
        long long ans = 0;
        std::unordered_map<long long, int> cnt;
        int n = nums.size();
        long long sum = 0;
        for (auto r{0}, l{0}; r < n; r += 1) {
            int y = nums[r];
            sum += y;
            cnt[y] += 1;
            dbg(cnt, sum);
            // [l, r]
            if (r - l + 1 >= k) {
                if (cnt.size() >= static_cast<size_t>(m)) {
                    ans = std::max(ans, sum);
                }
                int x = nums[l++];
                sum -= x;
                cnt[x] -= 1;
                if (cnt[x] == 0) {
                    cnt.erase(x);
                }
            }
        }
        return ans;
    }
};

// long long Solution::maxSum(vector<int> nums, int m, int k)

#ifdef Cattle_Horse
int main() {
    std::cout << "*** 2841. 几乎唯一子数组的最大和 ***" << std::endl
              << std::endl;

    Solution s0;

    {
        std::cout << "Test 1: ";

        vector<int> nums = {2, 6, 7, 3, 1, 7};
        int m = 3;
        int k = 4;
        long long ans0 = s0.maxSum(nums, m, k);
        long long exp0 = 18;

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

        vector<int> nums = {5, 9, 9, 2, 4, 5, 4};
        int m = 1;
        int k = 3;
        long long ans1 = s0.maxSum(nums, m, k);
        long long exp1 = 23;

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

        vector<int> nums = {1, 2, 1, 2, 1, 2, 1};
        int m = 3;
        int k = 3;
        long long ans2 = s0.maxSum(nums, m, k);
        long long exp2 = 0;

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
