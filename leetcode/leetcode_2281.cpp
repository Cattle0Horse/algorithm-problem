/**
 * @file leetcode_2281.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/sum-of-total-strength-of-wizards/description/
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

#include <algorithm>
#include <cstdint>
#include <limits>
#include <numeric>

#if __cpp_constexpr >= 201304L
#define CONSTEXPR14 constexpr
#else
#define CONSTEXPR14
#endif

namespace OY {
template<uint32_t P, bool IsPrime, typename = typename std::enable_if<(P > 1 && P < uint32_t(1) << 31)>::type>
struct StaticModInt32 {
    using mint = StaticModInt32<P, IsPrime>;
    using mod_type = uint32_t;
    mod_type m_val;
    static constexpr mod_type _reduce_norm(int32_t x) { return x < 0 ? x + mod() : x; }
    static constexpr mod_type _mul(mod_type a, mod_type b) { return uint64_t(a) * b % mod(); }
    constexpr StaticModInt32() = default;
    template<typename Tp, typename std::enable_if<std::is_signed<Tp>::value>::type* = nullptr>
    constexpr StaticModInt32(Tp val): m_val(_reduce_norm(val % int32_t(mod()))) {}
    template<typename Tp, typename std::enable_if<std::is_unsigned<Tp>::value>::type* = nullptr>
    constexpr StaticModInt32(Tp val): m_val(val % mod()) {}
    static CONSTEXPR14 mint raw(mod_type val) {
        mint res{};
        res.m_val = val;
        return res;
    }
    static constexpr mod_type mod() { return P; }
    constexpr mod_type val() const { return m_val; }
    CONSTEXPR14 mint pow(uint64_t n) const {
        mod_type res = 1, b = m_val;
        while (n) {
            if (n & 1) res = _mul(res, b);
            b = _mul(b, b), n >>= 1;
        }
        return raw(res);
    }
    CONSTEXPR14 mint inv() const {
        if constexpr (IsPrime)
            return inv_Fermat();
        else
            return inv_exgcd();
    }
    CONSTEXPR14 mint inv_exgcd() const {
        mod_type x = mod(), y = m_val, m0 = 0, m1 = 1;
        while (y) {
            mod_type z = x / y;
            x -= y * z, m0 -= m1 * z, std::swap(x, y), std::swap(m0, m1);
        }
        if (m0 >= mod()) m0 += mod() / x;
        return raw(m0);
    }
    constexpr mint inv_Fermat() const { return pow(mod() - 2); }
    CONSTEXPR14 mint& operator++() {
        if (++m_val == mod()) m_val = 0;
        return *this;
    }
    CONSTEXPR14 mint& operator--() {
        if (!m_val) m_val = mod();
        m_val--;
        return *this;
    }
    CONSTEXPR14 mint operator++(int) {
        mint old(*this);
        ++*this;
        return old;
    }
    CONSTEXPR14 mint operator--(int) {
        mint old(*this);
        --*this;
        return old;
    }
    CONSTEXPR14 mint& operator+=(const mint& rhs) {
        m_val += rhs.m_val;
        if (m_val >= mod()) m_val -= mod();
        return *this;
    }
    CONSTEXPR14 mint& operator-=(const mint& rhs) {
        m_val += mod() - rhs.m_val;
        if (m_val >= mod()) m_val -= mod();
        return *this;
    }
    CONSTEXPR14 mint& operator*=(const mint& rhs) {
        m_val = _mul(m_val, rhs.m_val);
        return *this;
    }
    CONSTEXPR14 mint& operator/=(const mint& rhs) { return *this *= rhs.inv(); }
    constexpr mint operator+() const { return *this; }
    constexpr mint operator-() const { return raw(m_val ? mod() - m_val : 0); }
    constexpr bool operator==(const mint& rhs) const { return m_val == rhs.m_val; }
    constexpr bool operator!=(const mint& rhs) const { return m_val != rhs.m_val; }
    constexpr bool operator<(const mint& rhs) const { return m_val < rhs.m_val; }
    constexpr bool operator>(const mint& rhs) const { return m_val > rhs.m_val; }
    constexpr bool operator<=(const mint& rhs) const { return m_val <= rhs.m_val; }
    constexpr bool operator>=(const mint& rhs) const { return m_val <= rhs.m_val; }
    template<typename Tp>
    constexpr explicit operator Tp() const { return Tp(m_val); }
    friend CONSTEXPR14 mint operator+(const mint& a, const mint& b) { return mint(a) += b; }
    friend CONSTEXPR14 mint operator-(const mint& a, const mint& b) { return mint(a) -= b; }
    friend CONSTEXPR14 mint operator*(const mint& a, const mint& b) { return mint(a) *= b; }
    friend CONSTEXPR14 mint operator/(const mint& a, const mint& b) { return mint(a) /= b; }
};
template<typename Istream, uint32_t P, bool IsPrime>
Istream& operator>>(Istream& is, StaticModInt32<P, IsPrime>& x) { return is >> x.m_val; }
template<typename Ostream, uint32_t P, bool IsPrime>
Ostream& operator<<(Ostream& os, const StaticModInt32<P, IsPrime>& x) { return os << x.val(); }
using mint998244353 = StaticModInt32<998244353, true>;
using mint1000000007 = StaticModInt32<1000000007, true>;
} // namespace OY

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
using namespace OI::Vectors;
using mint = OY::mint1000000007;
class Solution {
public:
    // 连续子序列, 寻找其作为最小值的区间
    int totalStrength(vector<int>& strength) {
        auto range{firstBeforeAndAfterIndex(strength, std::greater_equal<>())};

        // 3, 1, 4, 2, 0
        // 若当前数字为1, 则
        //  {1}, {3, 1},
        //  {1, 4}, {3, 1, 4},
        //  {1, 4, 2}, {3, 1, 4, 2}

        // 前缀和 s[i] = a[0] + ... + a[i-1]
        // 前缀和的前缀和 ss[i] = s[0] + ... + s[i-1] = (i-1) * a[0] + (i-2) * a[1] + ... + a[i-1]

        int n = strength.size();
        mint s{0};
        std::vector<mint> ss(n + 2);
        for (auto i{1}; i <= n; ++i) {
            s += strength[i - 1];
            ss[i + 1] = ss[i] + s;
        }
        mint ans{0};
        for (auto i{0}; i < n; ++i) {
            // [l, r]
            int l = range[i].first + 1, r = range[i].second - 1;
            mint tot = (i - l + 1) * (ss[r + 2] - ss[i + 1]) - (r - i + 1) * (ss[i + 1] - ss[l]);
            ans += strength[i] * tot;
        }
        return ans.m_val;
    }
};