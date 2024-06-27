/**
 * @file leetcode_1856.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/maximum-subarray-min-product/
 * @version 0.1
 * @date 2024-06-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <cstdint>
#include <functional>
#ifdef OY_LOCAL
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;
#endif

[[maybe_unused]] auto _ = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();

namespace OI::Vectors {
// find the first index before index whose cmp is equal to true (return -1 if not present)
template<typename T, typename Compare>
std::vector<int32_t> firstBeforeIndex(const std::vector<T>& arr, Compare cmp) {
    int32_t n = arr.size();
    std::vector<int32_t> before(n);
    std::deque<int32_t> stack{};
    for (int32_t i{0}; i < n; ++i) {
        while (!stack.empty() && !cmp(arr[i], arr[stack.back()])) {
            stack.pop_back();
        }
        before[i] = (stack.empty() ? -1 : stack.back());
        stack.push_back(i);
    }
    return before;
}
// find the first index After index whose cmp is equal to true (return arr.size() if not present)
template<typename T, typename Compare>
std::vector<int32_t> firstAfterIndex(const std::vector<T>& arr, Compare cmp) {
    int32_t n = arr.size();
    std::vector<int32_t> after(n, n);
    std::deque<int32_t> stack{};
    for (int32_t i{0}; i < n; ++i) {
        while (!stack.empty() && !cmp(arr[i], arr[stack.back()])) {
            after[stack.back()] = i;
            stack.pop_back();
        }
        stack.push_back(i);
    }
    // for (int32_t back : stack) {
    //     after[back] = n;
    // }
    return after;
}

template<typename T, typename Compare>
std::vector<std::pair<int32_t, int32_t>> firstBeforeAndAfterIndex(const std::vector<T>& arr, Compare cmp) {
    int32_t n = arr.size();
    std::vector<std::pair<int32_t, int32_t>> ans(n, {-1, n});
    std::deque<int32_t> stack{};
    for (int32_t i{0}; i < n; ++i) {
        while (!stack.empty() && !cmp(arr[i], arr[stack.back()])) {
            ans[stack.back()].second = i;
            stack.pop_back();
        }
        if (!stack.empty()) ans[i].first = stack.back();
        stack.push_back(i);
    }
    return ans;
}
} // namespace OI::Vectors

constexpr int MOD = 1e9 + 7;
class Solution {
public:
    int maxSumMinProduct(vector<int>& nums) {
        int n = nums.size();
        // 找到nums[i]作为最小值所能获得的最大 最小乘积
        int64_t ans{0};
        // 前缀和
        vector<int64_t> pre(n + 1);
        // 不能用partial_sum方法, 内部的值类型定义为nums的类型
        // std::partial_sum(nums.begin(), nums.end(), pre.begin() + 1, std::plus<int64_t>());
        for (int i = 1; i <= n; ++i) {
            pre[i] = pre[i - 1] + nums[i - 1];
        }
        auto range{OI::Vectors::firstBeforeAndAfterIndex(nums, std::greater<>())};
        for (int i{0}; i < n; ++i) {
            auto [left, right] = range[i];
            int64_t sum = pre[right] - pre[left + 1];
            ans = std::max(ans, nums[i] * sum);
        }
        return ans % MOD;
    }
};