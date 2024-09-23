#include <algorithm>

namespace OI {
namespace Operators {
template<typename T = void>
struct max {
    constexpr T operator()(const T& x, const T& y) const { return std::max(x, y); }
};
template<>
struct max<void> {
    template<class T1, class T2>
    constexpr auto operator()(T1&& x, T2&& y) const -> decltype(std::max(std::forward<T1>(x), std::forward<T2>(y))) {
        return std::max(std::forward<T1>(x), std::forward<T2>(y));
    }
};
template<typename T = void>
struct min {
    constexpr T operator()(const T& x, const T& y) const { return std::min(x, y); }
};
template<>
struct min<void> {
    template<class T1, class T2>
    constexpr auto operator()(T1&& x, T2&& y) const -> decltype(std::min(std::forward<T1>(x), std::forward<T2>(y))) {
        return std::min(std::forward<T1>(x), std::forward<T2>(y));
    }
};
} // namespace Operators
} // namespace OI