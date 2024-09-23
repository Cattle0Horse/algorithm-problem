#include <cstdint>
#include <utility>
namespace OI::Math {
template<typename T, uint32_t MAX_RANGE, T P>
struct Factorial {
    using temp_type = unsigned long long;
    static constexpr T inv(const T& x, const T& y = P) {
        assert(x != 0);
        T u = 0, v = 1, a = x, m = y, t;
        while (a != 0) {
            t = m / a;
            swap(a, m -= t * a);
            swap(u -= t * v, v);
        }
        assert(m == 1);
        return u;
    }
    static constexpr T mod() { return P; }

    static constexpr auto factorial_array() {
        T result[MAX_RANGE + 1];
        result[0] = 1 % P;
        for (uint32_t i = 1; i <= MAX_RANGE; ++i) {
            result[i] = static_cast<temp_type>(result[i - 1]) * i % P;
        }
        return result;
    }

    static constexpr auto factorial_inv_array() {
        T result[MAX_RANGE + 1];
        result[MAX_RANGE] = inv(factorial_array()[MAX_RANGE]);
        for (uint32_t i = MAX_RANGE - 1; ~i; --i) {
            result[i] = static_cast<temp_type>(result[i + 1]) * (i + 1) % P;
        }
        return result;
    }

    static constexpr auto m_factorial = factorial_array();
    static constexpr auto m_factorial_inv = factorial_inv_array();

    static constexpr T combination(uint32_t n, uint32_t m) {
        if (n < m) return 0;
        if (n == m) return 1 % P;
        return static_cast<temp_type>(m_factorial[n]) * m_factorial_inv[m] % P * m_factorial_inv[n - m] % P;
    }

    static constexpr T factorial(uint32_t n) { return m_factorial[n]; }

    static constexpr T permutation(uint32_t n, uint32_t m) {
        if (n < m) return 0;
        if (n == m) return m_factorial[n];
        return static_cast<temp_type>(m_factorial[n]) * m_factorial_inv[n - m] % P;
    }
};

template<typename Tp, uint32_t MAX_RANGE, Tp P>
struct CombinationTable {
    using temp_type = unsigned long long;
    template<Tp N>
    static constexpr Tp inv_exgcd() {
        Tp x = P, y = N, m0 = 0, m1 = 1;
        while (y) {
            Tp z = x / y;
            x -= y * z, m0 -= m1 * z, std::swap(x, y), std::swap(m0, m1);
        }
        if (m0 >= P) m0 += P / x;
        return m0;
    }
    static constexpr Tp m_factorial[MAX_RANGE + 1], m_factorial_inv[MAX_RANGE + 1];
    constexpr CombinationTable(uint32_t range = MAX_RANGE) {
        m_factorial[0] = Tp::raw(1);
        for (uint32_t i = 1; i <= range; i++) m_factorial[i] = m_factorial[i - 1] * Tp::raw(i);
        m_factorial_inv[range] = m_factorial[range].inv();
        for (uint32_t i = range - 1; ~i; i--) m_factorial_inv[i] = m_factorial_inv[i + 1] * Tp::raw(i + 1);
    }
    constexpr Tp comb(uint32_t n, uint32_t m) const {
        if (n < m) return Tp::raw(0);
        if (n == m) return Tp::raw(1);
        return m_factorial[n] * m_factorial_inv[m] * m_factorial_inv[n - m];
    }
    constexpr Tp factorial(uint32_t n) const { return m_factorial[n]; }
    constexpr Tp perm(uint32_t n, uint32_t m) const {
        if (n < m) return Tp::raw(0);
        if (n == m) return m_factorial[n];
        return m_factorial[n] * m_factorial_inv[n - m];
    }
};
} // namespace OI::Math
