/**
 * @file leetcode_80.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/remove-duplicates-from-sorted-array-ii/description/
 * @version 0.1
 * @date 2024-06-16
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifdef OY_LOCAL
#include <vector>
#include <string>
#include <iostream>
using namespace std;
#endif

[[maybe_unused]] auto _ = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if (n <= 2) return n;
        int slow = 2;
        for (int fast = 2; fast < n; ++fast) {
            if (nums[slow - 2] != nums[fast]) {
                nums[slow++] = nums[fast];
            }
        }
        return slow;
    }
};