#include <vector>
namespace OI::Math {
template<typename T, typename U = uint32_t>
std::vector<std::pair<T, U>> getFactorsWithCnt(T n) {
    std::vector<std::pair<T, U>> ans;
    for (T i{2}; i * i <= n; ++i) {
        if (n % i == 0) {
            int cnt = 0;
            while (n % i == 0) n /= i, ++cnt;
            ans.emplace_back(i, cnt);
        }
    }
    if (n != 1) ans.emplace_back(n, 1);
    return ans;
}
// template<std::integral T>
template<typename T>
std::vector<T> getFactors(T n) {
    std::vector<T> ans;
    for (T i{2}; i * i <= n; ++i) {
        if (n % i == 0) {
            while (n % i == 0) n /= i;
            ans.push_back(i);
        }
    }
    if (n != 1) ans.push_back(n);
    return ans;
}

template<typename T>
std::vector<bool> sieve(T n) {
    if (n == 0) return std::vector<bool>(1, false);
    std::vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    // note: Attention overflow
    for (T i{2}; i * i <= n; ++i) {
        if (is_prime[i]) {
            for (T j{i * i}; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return is_prime;
}
template<typename T>
std::pair<std::vector<bool>, std::vector<T>> sieve2(T n) {
    if (n == 0) return {std::vector<bool>(1, false), std::vector<T>()};
    std::vector<bool> is_prime(n + 1, true);
    std::vector<T> primes;
    is_prime[0] = is_prime[1] = false;
    for (T i{2}; i <= n; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
            // note: Attention overflow
            for (T j{i * i}; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return {is_prime, primes};
}
// 欧拉筛
template<typename T>
std::pair<std::vector<bool>, std::vector<T>> sieve3(T n) {
    if (n == 0) return {std::vector<bool>(1, false), std::vector<T>()};
    std::vector<bool> is_prime(n + 1, true);
    std::vector<T> primes;
    is_prime[0] = is_prime[1] = false;
    for (T i = 2; i <= n; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
        for (auto&& prime : primes) {
            if (prime * i > n) break;
            is_prime[prime * i] = false;
            if (i % prime == 0) break;
        }
    }
    return {is_prime, primes};
}
} // namespace OI::Math