/**
 * @file leetcode_3097.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/shortest-subarray-with-or-at-least-k-ii/
 * @version 0.1
 * @date 2024-06-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <array>
#include <cstddef>
#include <string>
#include <unordered_map>
#ifdef OY_LOCAL
#include <vector>
#include <iostream>
#include <algorithm>
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
    // 连续子数组dp
    int minimumSubarrayLength(vector<int>& nums, int k) {
        // 每种状态对应的最大左端点
        // (状态, 最大右端点)
        std::unordered_map<int, int> dp{};
        // dp遍历到当前数字, 以当前数字结尾的所有情况
        int n = nums.size(), ans = 0x3f3f3f3f;
        for (auto i{0}; i < n; ++i) {
            int num = nums[i];
            // num 和前面的组合
            std::unordered_map<int, int> pre{};
            pre.swap(dp);
            for (auto&& [mask, left] : pre) {
                int or_sum = mask | num;
                if (dp.contains(or_sum)) {
                    dp[or_sum] = std::max(dp[or_sum], left);
                } else {
                    dp[or_sum] = left;
                }
            }
            dp[num] = i;
            for (auto&& [mask, left] : dp) {
                if (mask >= k) {
                    ans = std::min(ans, i - left + 1);
                }
            }
        }
        return ans == 0x3f3f3f3f ? -1 : ans;
    }
};

class Solution1 {
public:
    // 这是不连续的子数组的情况dp
    // note: 这不是本题解
    int minimumSubarrayLength(vector<int>& nums, int k) {
        std::unordered_map<int, int> dp;
        for (int num : nums) {
            // dp保留,当前数字不选
            // 和前一行进行组合
            std::unordered_map<int, int> pre(dp);
            dp[num] = 1;
            for (auto&& [mask, length] : pre) {
                int x = mask | num;
                if (dp.contains(x)) {
                    dp[x] = std::min(dp[x], length + 1);
                } else {
                    dp[x] = length + 1;
                }
            }
        }
        int ans = 0x3f3f3f3f;
        for (auto&& [mask, length] : dp) {
            if (mask >= k) {
                ans = std::min(ans, length);
            }
        }
        return ans;
    }
};

template<size_t N>
struct BitCnt : array<int, N> {
    template<typename T>
    T getValue() const {
        T mask{0};
        for (size_t i{0}; i < N; ++i) {
            mask |= (this->at(i) > 0) << i;
        }
        return mask;
    }
    template<typename T>
    BitCnt<N>& operator+=(T mask) {
        for (size_t i{0}; i < N; ++i) {
            this->at(i) += (mask >> i & 1);
        }
        return *this;
    }
    BitCnt<N>& operator+=(const BitCnt<N>& other) {
        for (size_t i{0}; i < N; ++i) {
            this->at(i) += other.at(i);
        }
        return *this;
    }
    template<typename T>
    BitCnt<N>& operator-=(T mask) {
        for (size_t i{0}; i < N; ++i) {
            this->at(i) -= (mask >> i & 1);
        }
        return *this;
    }
    BitCnt<N>& operator-=(const BitCnt<N>& other) {
        for (size_t i{0}; i < N; ++i) {
            this->at(i) -= other.at(i);
        }
        return *this;
    }
};

class Solution2 {
public:
    // 双指针
    int minimumSubarrayLength(vector<int>& nums, int k) {
        int n = nums.size();
        // 存储每一位1出现的次数
        BitCnt<32> cnt{};
        int ans = 0x3f3f3f3f;
        int l = 0;
        for (int r = 0; r < n; ++r) {
            // 加上当前数
            cnt += nums[r];
            // [l, r]
            while (l <= r && cnt.getValue<int>() >= k) {
                ans = std::min(ans, r - l + 1);
                cnt -= nums[l++];
            }
        }
        return ans == 0x3f3f3f3f ? -1 : ans;
    }
};

int main() {
    std::vector<int> nums{1, 2, 3};
    int k = 2;
    Solution().minimumSubarrayLength(nums, k);
}