#include <algorithm>
#include <bit>
#include <cstdint>
namespace OI::Math {
// https://leetcode.cn/problems/maximum-rows-covered-by-columns
// Gosper's Hack : https://zhuanlan.zhihu.com/p/360512296
// https://programmingforinsomniacs.blogspot.com/2018/03/gospers-hack-explained.html
/*
int m = 1<<n
for (auto i{(1u << k) - 1}; i < m; i = next_k_subset(i)) {
    // Any i contains k ones
    ...
}
*/
#define next_k_subset(i)  (((i ^ (i + (i & -i))) >> (std::countr_zero(i & -i) + 2)) | (i + (i & -i)))
#define in(x, begin, end) ((begin) <= (x) && (x) < (end))

// 遍历子集(每一个集合都有k个元素)
template<typename F>
void for_each_k_subset(uint32_t S, uint32_t k, F f) {
    for (uint32_t s{(1u << k) - 1}; s <= S; s = next_k_subset(s)) {
        // Any s contains k ones
        f(s);
    }
}
// 遍历子集(每一个集合都有k个元素)
template<typename R, typename F, typename SF>
R for_each_k_subset(uint32_t S, uint32_t k, F f, SF sf, R init) {
    for (uint32_t s{(1u << k) - 1}; s <= S; s = next_k_subset(s)) {
        init = sf(std::move(init), f(s));
    }
    return init;
}
template<typename F>
void for_each_subset(uint32_t S, F f) {
    uint32_t s = 0;
    do {
        f(s);
        s = (s - 1) & S;
    } while (s != 0u);
}
template<typename R, typename F, typename SF>
R for_each_subset(uint32_t S, F f, SF sf, R init) {
    uint32_t s = 0;
    do {
        init = sf(std::move(init), f(s));
        s = (s - 1) & S;
    } while (s != 0u);
    return init;
}
template<typename F>
void for_each_nonempty_subset(uint32_t S, F f) {
    for (uint32_t s{S}; s != 0; s = (s - 1) & S) {
        f(s);
    }
}
template<typename R, typename F, typename SF>
R for_each_nonempty_subset(uint32_t S, F f, SF sf, R init) {
    for (uint32_t s{S}; s != 0; s = (s - 1) & S) {
        init = sf(std::move(init), f(s));
    }
    return init;
}
} // namespace OI::Math