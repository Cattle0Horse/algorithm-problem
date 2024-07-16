/**
 * @file leetcode_1004.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/max-consecutive-ones-iii/
 * @version 0.1
 * @date 2024-07-16
 *
 * @copyright Copyright (c) 2024
 *
 */

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
    int longestOnes(vector<int>& nums, int k) {
        int n = nums.size(), ans = 0;
        for (int l = 0, r = 0, zero = 0; r < n; ++r) {
            zero += nums[r] == 0;
            while (zero > k) zero -= nums[l++] == 0;
            ans = std::max(ans, r - l + 1);
        }
        return ans;
    }
};

#ifdef Cattle_Horse
int main() {
    std::vector<int> nums{0, 0, 0, 1};
    Solution().longestOnes(nums, 4);
}
#endif