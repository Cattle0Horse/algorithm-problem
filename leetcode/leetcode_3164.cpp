/**
 * @file leetcode_3164.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/find-the-number-of-good-pairs-ii/
 * @version 0.1
 * @date 2024-05-28
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
#include <unordered_map>
#include <vector>
class Solution {
public:
    long long numberOfPairs(std::vector<int>& nums1, std::vector<int>& nums2, int k) {
        long long ans = 0;
        std::unordered_map<int, int> cnt;
        int max = 0;
        for (int num : nums1) {
            if (num % k != 0) continue;
            max = std::max(max, num);
            ++cnt[num / k];
        }
        std::unordered_map<int, int> cnt2;
        for (int num : nums2) {
            if (cnt2.contains(num)) {
                ans += cnt2[num];
            } else {
                int s = 0;
                for (int j = num; j <= max; j += num) {
                    // constains !!!
                    // don't casually add element in hash map
                    s += cnt.contains(j) ? cnt[j] : 0;
                }
                cnt2[num] = s;
                ans += s;
            }
        }
        return ans;
    }
};