/**
 * @file leetcode_611.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/valid-triangle-number/description/
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
    // 循环最大数c, 找有a+b大于c的a的个数
    int triangleNumber(vector<int>& nums) {
        std::ranges::sort(nums);
        int n = nums.size(), ans = 0;
        for (auto i{0}; i < n; i += 1) {
            int c = nums[i];
            for (int k = i - 1, j = 0; k > j; k -= 1) {
                while (j < k && nums[j] + nums[k] <= c) ++j;
                // nums [j, k) 与 nums[k]匹配
                ans += k - j;
            }
        }
        return ans;
    }
};

#ifdef Cattle_Horse
int main() {
    //
}
#endif