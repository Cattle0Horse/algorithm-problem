#include <vector>

namespace OI::Math {
// 逆元
template<typename T>
T inv(const T& x, const T& y) {
    assert(x != 0);
    T u = 0, v = 1, a = x, m = y, t;
    while (a != 0) {
        t = m / a;
        swap(a, m -= t * a);
        swap(u -= t * v, v);
    }
    assert(m == 1);
    if (u < 0) u += y;
    return u;
}
/*
long long inv(long long a, long long b = mod) {
    long long ans = 1;
    for (b -= 2; b; b >>= 1, a = (a * a) % mod)
        if (b & 1) ans = (ans * a) % mod;
    return ans;
}*/
// long long inv(long long a, long long p=mod) { return (a == 1 ? 1 : (1 - p * inv(p % a, a)) / a + p); }
template<typename T>
struct Inverse {
    int n;
    T MOD;
    std::vector<T> inv;
    Inverse() = default;
    Inverse(int _n, T _MOD): n(_n + 1), MOD(_MOD), inv(_n + 1 >= 2 ? _n + 1 : 2) {
        inv[1] = 1;
        for (int i = 2; i <= n; ++i) {
            inv[i] = (long long) (MOD - MOD / i) * inv[MOD % i] % MOD;
        }
    }
};

} // namespace OI::Math
