/**
 * @file range.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief
 * @version 0.1
 * @date 2024-07-13
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <vector>
#include <cstdint>

namespace OI {
template<std::integral T = int32_t>
struct range {
    struct Iterator {
        using difference_type = ptrdiff_t;
        T val, d;
        Iterator() {}
        Iterator(T val, T d): val(val), d(d) {}
        T operator*() const { return val; }
        Iterator& operator++() { return val += d, *this; }
        difference_type operator-(const Iterator& other) const { return (val - other.val) / d; }
        bool operator==(const Iterator& other) const { return val == other.val; }
    };
    Iterator m_begin, m_end;
    range(T n): m_begin(0, 1), m_end(std::max(n, T{0}), 1) {}
    range(T a, T b, T d = T(1)): m_begin(a, d), m_end(a + std::max((b - a) / d + static_cast<bool>((b - a) % d), T(0)) * d, d) {}
    const Iterator begin() const { return m_begin; }
    const Iterator end() const { return m_end; }
    Iterator begin() { return m_begin; }
    Iterator end() { return m_end; }
    std::vector<T> to_vector() {
        std::vector<T> res;
        res.reserve(m_end - m_begin);
        for (T v = m_begin.val; v != m_end.val; v += m_end.d) res.push_back(v);
        return res;
    }
};
} // namespace OI