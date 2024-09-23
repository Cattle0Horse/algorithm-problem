#include <cstdint>

namespace OI::Math {
template<typename T>
T qpow(T a, T b) {
    T ans{1};
    for (; b != 0; a *= a, b >>= 1)
        if (b & 1) ans *= a;
    return ans;
}
template<typename T, T P>
T qpow(T a, T b) {
    long long ans{1};
    for (; b != 0; a = (static_cast<long long>(a) * a) % P, b >>= 1)
        if (b & 1) ans = (ans * a) % P;
    return static_cast<T>(ans % P);
}
template<typename T>
T qpow(T a, T b, T p) {
    long long ans{1};
    for (; b != 0; a = (static_cast<long long>(a) * a) % p, b >>= 1)
        if (b & 1) ans = (ans * a) % p;
    return static_cast<T>(ans) % p;
}

template<typename R = uint32_t, typename T>
R digitSum(T num) {
    R ans{0};
    for (; num != 0; num /= 10) ans += num % 10;
    return ans;
}

} // namespace OI::Math