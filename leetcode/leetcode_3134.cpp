// @date 2024/8/27 21:39:02
// @author Cattle_Horse (CattleHorse@duck.com)
// @problem 3134. 找出唯一性数组的中位数
// @link https://leetcode.cn/classic/problems/find-the-median-of-the-uniqueness-array/description/

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
    /*
    二分+滑动窗口
    以i为左端点的子数组，j越大则不同元素的个数必定不小
    对于结果cnt，若有x个小于cnt的数
    */
    int medianOfUniquenessArray(vector<int>& nums) {
        int n = nums.size();
        long long all = static_cast<long long>(1 + n) * n / 2;
        long long k = (all + 1) / 2;
        std::array<int, static_cast<int>(1e5 + 1)> mp;
        auto check = [&](uint32_t upper) -> bool {
            mp.fill(0);
            uint32_t sz = 0;
            long long cnt = 0;
            for (int i = 0, j = 0; j < n; j += 1) {
                if (mp[nums[j]] == 0) sz += 1;
                mp[nums[j]] += 1;
                while (sz > upper) {
                    mp[nums[i]] -= 1;
                    if (mp[nums[i]] == 0) {
                        sz -= 1;
                    }
                    i += 1;
                }
                // 以j结尾的子数组，不同元素的个数小于等于upper的个数有j-i+1个 [i, j]
                cnt += j - i + 1;
            }
            return cnt >= k;
        };
        int last_false = 0, first_true = n;
        while (last_false + 1 < first_true) {
            int mid = (last_false + first_true) >> 1;
            if (check(mid)) {
                first_true = mid;
            } else {
                last_false = mid;
            }
        }
        return first_true;
    }
};

// int Solution::medianOfUniquenessArray(vector<int> nums)

#ifdef Cattle_Horse
int main() {
    std::cout << "*** 3134. 找出唯一性数组的中位数 ***" << std::endl
              << std::endl;

    Solution s0;

    {
        std::cout << "Test 1: ";

        vector<int> nums = {1, 2, 3};
        int ans0 = s0.medianOfUniquenessArray(nums);
        int exp0 = 1;

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

        vector<int> nums = {3, 4, 3, 4, 5};
        int ans1 = s0.medianOfUniquenessArray(nums);
        int exp1 = 2;

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

        vector<int> nums = {4, 3, 5, 4};
        int ans2 = s0.medianOfUniquenessArray(nums);
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

        vector<int> nums = {1};
        int ans3 = s0.medianOfUniquenessArray(nums);
        int exp3 = 1;

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

        vector<int> nums = {91, 64, 76, 18, 61, 55, 46, 93, 65, 99};
        int ans4 = s0.medianOfUniquenessArray(nums);
        int exp4 = 4;

        if (ans4 == exp4) {
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
            std::cout << "  Answer: " << ans4 << std::endl;
            std::cout << "  Expect: " << exp4 << std::endl;
        }
    }

    return 0;
}
#endif
