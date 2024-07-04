/**
 * @file leetcode_2835.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/minimum-operations-to-form-subsequence-with-target-sum/description/
 * @version 0.1
 * @date 2024-07-03
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
#include <functional>
#include <numeric>
#ifdef OY_LOCAL
#include <vector>
#include <iostream>
using namespace std;
#endif

[[maybe_unused]] auto __init_io__ = []() {
    return std::cin.tie(nullptr)->sync_with_stdio(false);
}();
/**
 * @file bit_counter.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief
 * @version 0.1
 * @date 2024-06-25
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <array>
#include <cstdint>
namespace OI::DataStructure {
template<size_t N, typename CntType = int32_t>
struct StaticBitCounter : std::array<CntType, N> {
    template<typename T>
    T getDecimal() const {
        T mask{0};
        for (size_t i{0}; i < N; ++i) mask |= (this->at(i) > 0) << i;
        return mask;
    }
    template<typename T>
    StaticBitCounter& operator+=(T mask) {
        for (size_t i{0}; i < N; ++i) this->at(i) += (mask >> i & 1);
        return *this;
    }
    StaticBitCounter& operator+=(const StaticBitCounter& other) {
        for (size_t i{0}; i < N; ++i) this->at(i) += other.at(i);
        return *this;
    }
    template<typename T>
    StaticBitCounter& operator-=(T mask) {
        for (size_t i{0}; i < N; ++i) this->at(i) -= (mask >> i & 1);
        return *this;
    }
    StaticBitCounter& operator-=(const StaticBitCounter& other) {
        for (size_t i{0}; i < N; ++i) this->at(i) -= other.at(i);
        return *this;
    }
    template<typename T>
    friend StaticBitCounter operator+(const StaticBitCounter& lhs, const T& rhs) { return StaticBitCounter{lhs} += rhs; }
    template<typename T>
    friend StaticBitCounter operator+(const T& lhs, const StaticBitCounter& rhs) { return StaticBitCounter{rhs} += lhs; }
    friend StaticBitCounter operator+(const StaticBitCounter& lhs, const StaticBitCounter& rhs) { return StaticBitCounter{lhs} += rhs; }
    template<typename T>
    friend StaticBitCounter operator-(const StaticBitCounter& lhs, const T& rhs) { return StaticBitCounter{lhs} += rhs; }
    template<typename T>
    friend StaticBitCounter operator-(const T& lhs, const StaticBitCounter& rhs) { return StaticBitCounter{rhs} += lhs; }
    friend StaticBitCounter operator-(const StaticBitCounter& lhs, const StaticBitCounter& rhs) { return StaticBitCounter{lhs} += rhs; }
};
} // namespace OI::DataStructure
using BitCounter = OI::DataStructure::StaticBitCounter<32>;
class Solution {
public:
    // 从target的最低二进制位开始填充, 如果数组中没有当前位的数字, 则需要向前借
    int minOperations(vector<int>& nums, int target) {
        std::ranges::sort(nums);
        BitCounter cnt{};
        int n = nums.size(), ans{0};
        for (auto i{0}, j{0}; i < 31; ++i) {
            cnt[i] -= target >> i & 1;
            while (j < n && nums[j] == (1 << i)) {
                cnt[i] += 1;
                ++j;
            }
            if (cnt[i] < 0) {
                // 向前借多少位(上取整)
                int need = (-cnt[i] + 1) / 2;
                ans += need;
                cnt[i + 1] -= need;
            } else {
                // 否则当前位置多的可以组合向前进
                cnt[i + 1] += cnt[i] >> 1;
            }
        }
        if (cnt[31] < 0) return -1;
        return ans;
    }
};