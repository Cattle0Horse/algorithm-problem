/**
 * @file leetcode_2818.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/apply-operations-to-maximize-score/description/?envType=problem-list-v2&envId=e9nOSekV
 * @version 0.1
 * @date 2024-06-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <array>
#include <cstddef>
#include <functional>
#ifdef OY_LOCAL
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;
#endif

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
using mint = OY::mint1000000007;

#include <queue>
namespace OI::Vectors {
// find the first index before index whose cmp is equal to false (return -1 if not present)
// (ans[i], i) all is cmp = true
template<typename T, typename Compare>
std::vector<int32_t> firstBeforeIndex(const std::vector<T>& arr, Compare cmp) {
    int32_t n = arr.size();
    std::vector<int32_t> before(n);
    std::deque<int32_t> stack{};
    for (int32_t i{0}; i < n; ++i) {
        while (!stack.empty() && cmp(arr[i], arr[stack.back()])) {
            stack.pop_back();
        }
        before[i] = (stack.empty() ? -1 : stack.back());
        stack.push_back(i);
    }
    return before;
}
// find the first index After index whose cmp is equal to false (return arr.size() if not present)
// (i, ans[i]) all is cmp = true
template<typename T, typename Compare>
std::vector<int32_t> firstAfterIndex(const std::vector<T>& arr, Compare cmp) {
    int32_t n = arr.size();
    std::vector<int32_t> after(n, n);
    std::deque<int32_t> stack{};
    for (int32_t i{0}; i < n; ++i) {
        while (!stack.empty() && !cmp(arr[stack.back()], arr[i])) {
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
} // namespace OI::Vectors
using namespace OI::Vectors;
constexpr int MOD = 1e9 + 7;
template<typename T, typename U, typename P>
T qpow(T _a, U b, P p) {
    long long ans{1};
    for (long long a = _a; b != 0; a = a * a % p, b >>= 1)
        if (b & 1) ans = (ans * a) % p;
    return ans % p;
}
constexpr int N = 1e5;
// int omiga[N + 1]{};
std::array<int, N + 1> omiga;
[[maybe_unused]] auto _ = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    for (int i = 2; i <= N; ++i) {
        if (omiga[i] == 0) {
            for (int j = i; j <= N; j += i) {
                ++omiga[j];
            }
        }
    }
    return 0;
}();

class Solution {
public:
    int maximumScore(vector<int>& nums, int k) {
        int n = nums.size();
        std::vector<int> cnt(n);
        for (auto i{0}; i < n; ++i) cnt[i] = omiga[nums[i]];
        auto left{firstBeforeIndex(cnt, std::greater<>())};
        auto right{firstAfterIndex(cnt, std::greater_equal<>())};

        std::vector<int> index(n);
        std::iota(index.begin(), index.end(), 0);
        std::sort(index.begin(), index.end(), [&](int a, int b) {
            return nums[a] > nums[b];
        });

        mint ans{1};
        for (int i : index) {
            // (l, r)
            long long tot = static_cast<long long>(i - left[i]) * (right[i] - i);
            ans *= qpow(nums[i], std::min<long long>(k, tot), MOD);
            k -= tot;
            if (k <= 0) break;
        }
        return ans.m_val;
    }
};

int main() {
    std::vector<int> nums{8, 3, 9, 3, 8};
    int k = 2;
    std::cout << Solution().maximumScore(nums, k);
}