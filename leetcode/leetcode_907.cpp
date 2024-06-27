/**
 * @file leetcode_907.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/sum-of-subarray-minimums/description/
 * @version 0.1
 * @date 2024-06-27
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <cstddef>
#include <cstdint>
#include <deque>
#include <functional>
#include <iterator>
#include <stack>
#include <utility>
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
using namespace OI::Vectors;
class Solution {
public:
    // 连续子数组, 求一个数作为最小值的次数(即对答案的贡献)
    // 则需要求比当前数小的左右两边第一个数
    int sumSubarrayMins(vector<int>& arr) {
        // auto before{getFirstBeforeIndex(arr, std::greater<>())};
        // auto after{getFirstAfterIndex(arr, std::greater<>())};
        auto range{firstBeforeAndAfterIndex(arr, std::greater<>())};
        int n = arr.size();
        int64_t ans{0};
        for (auto i{0}; i < n; ++i) {
            ans = (ans + static_cast<int64_t>(arr[i]) * (range[i].second - i) * (i - range[i].first) % MOD) % MOD;
        }
        return ans;
    }
};