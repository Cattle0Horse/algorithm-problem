/**
 * @file leetcode_1000.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/minimum-cost-to-merge-stones/
 * @version 0.1
 * @date 2024-06-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <limits>
#include <numeric>
#include <vector>

/*
最后修改:
20240517
测试环境:
gcc11.2,c++14
clang12.0,C++14
msvc14.2,C++14
*/

#include <bitset>
#include <chrono>
#include <cstdint>
#include <vector>

namespace OY {
namespace GHASH {
using size_type = uint32_t;
template<size_type N>
struct ModLevel : std::integral_constant<size_type, N % 2 == 0 && ~ModLevel<N / 2>::value ? ModLevel<N / 2>::value + 1 : -1> {};
template<>
struct ModLevel<1> : std::integral_constant<size_type, 0> {};
template<size_type N, bool = ModLevel<N>::value != -1>
struct Moder {
    static constexpr size_type L = 64 - ModLevel<N>::value;
    size_type operator()(uint64_t a) const { return a >> L; }
};
template<size_type N>
struct Moder<N, false> {
    size_type operator()(uint64_t a) const { return a % N; }
};
struct HashCombine {
    uint64_t operator()(uint64_t a, uint64_t b) const { return a ^ (b + 0x9e3779b9 + (a << 6) + (a >> 2)); }
    template<typename... Args>
    uint64_t operator()(uint64_t a, uint64_t b, Args... args) const { return operator()(operator()(a, b), args...); }
};
template<typename Tp>
struct Hash {
    static uint64_t s_bias;
    uint64_t operator()(const Tp& x) const { return (x + s_bias) * 11995408973635179863ULL; }
};
template<typename Tp>
uint64_t Hash<Tp>::s_bias = std::chrono::steady_clock::now().time_since_epoch().count();
template<>
struct Hash<std::string> {
    uint64_t operator()(const std::string& x) const { return std::hash<std::string>()(x); }
};
template<typename KeyType, typename MappedType>
struct Node {
    KeyType m_key;
    MappedType m_mapped;
};
template<typename KeyType>
struct Node<KeyType, void> {
    KeyType m_key;
};
template<bool Record>
struct Recorder {};
template<>
struct Recorder<true> : std::vector<size_type> {};
template<typename KeyType, typename MappedType, bool MakeRecord, size_type BUFFER>
struct TableBase {
    using node = Node<KeyType, MappedType>;
    struct pair {
        node* m_ptr;
        bool m_flag;
    };
    node m_pool[BUFFER];
    std::bitset<BUFFER> m_occupied;
    Recorder<MakeRecord> m_recs;
    size_type m_size;
    void reserve(size_type count) {
        if constexpr (MakeRecord) m_recs.reserve(count);
    }
    size_type size() const { return m_size; }
    bool empty() const { return !size(); }
    void clear() {
        static_assert(MakeRecord, "MakeRecord Must Be True");
        for (auto i : m_recs) m_occupied[i] = false;
        m_recs.clear(), m_size = 0;
    }
    template<typename Callback>
    void do_for_each(Callback&& call) {
        static_assert(MakeRecord, "MakeRecord Must Be True");
        for (auto i : m_recs)
            if (m_occupied[i]) call(m_pool + i);
    }
    pair insert(const KeyType& key) {
        size_type ha = Moder<BUFFER>()(Hash<KeyType>()(key)), i = ha;
        while (m_occupied[i]) {
            if (key == m_pool[i].m_key) return {m_pool + i, false};
            i = i != BUFFER - 1 ? i + 1 : 0;
        }
        m_pool[i].m_key = key, m_occupied[i] = true, m_size++;
        if constexpr (MakeRecord) m_recs.push_back(i);
        return {m_pool + i, true};
    }
    bool erase(const KeyType& key) {
        size_type ha = Moder<BUFFER>()(Hash<KeyType>()(key)), i = ha;
        while (m_occupied[i]) {
            if (key == m_pool[i].m_key) {
                m_occupied[i] = false, m_size--;
                return true;
            }
            i = i != BUFFER - 1 ? i + 1 : 0;
        }
        return false;
    }
    node* find(const KeyType& key) const {
        size_type ha = Moder<BUFFER>()(Hash<KeyType>()(key)), i = ha;
        while (m_occupied[i]) {
            if (key == m_pool[i].m_key) return (node*) (m_pool + i);
            i = i != BUFFER - 1 ? i + 1 : 0;
        }
        return nullptr;
    }
};
template<typename KeyType, bool MakeRecord, size_type BUFFER>
struct UnorderedSet : TableBase<KeyType, void, MakeRecord, BUFFER> {};
template<typename KeyType, typename MappedType, bool MakeRecord, size_type BUFFER>
struct UnorderedMap : TableBase<KeyType, MappedType, MakeRecord, BUFFER> {
    using typename TableBase<KeyType, MappedType, MakeRecord, BUFFER>::pair;
    pair insert_or_assign(const KeyType& key, const MappedType& mapped) {
        pair res = this->insert(key);
        res.m_ptr->m_mapped = mapped;
        return res;
    }
    pair insert_or_ignore(const KeyType& key, const MappedType& mapped) {
        pair res = this->insert(key);
        if (res.m_flag) res.m_ptr->m_mapped = mapped;
        return res;
    }
    MappedType get(const KeyType& key, const MappedType& _default) const {
        auto res = this->find(key);
        return res ? res->m_mapped : _default;
    }
    const MappedType& get(const KeyType& key) const { return this->find(key)->m_mapped; }
};
} // namespace GHASH
} // namespace OY

namespace OY {
namespace GHASH {
template<size_t I, typename Tuple>
uint64_t HashGet(const Tuple& x) { return Hash<typename std::decay<decltype(std::get<I>(x))>::type>()(std::get<I>(x)); }
template<typename... Args>
struct Hash<std::tuple<Args...>> {
    template<size_t... Is>
    uint64_t operator()(const std::tuple<Args...>& x, std::index_sequence<Is...>) const {
        if constexpr (sizeof...(Args) == 1)
            return HashGet<0>(x);
        else
            return HashCombine()(HashGet<Is>(x)...);
    }
    uint64_t operator()(const std::tuple<Args...>& x) const { return operator()(x, std::make_index_sequence<sizeof...(Args)>()); }
};
} // namespace GHASH
namespace CACHE {
using size_type = uint32_t;
template<typename Func, bool MakeRecord, size_type BUFFER, typename KeyType, typename Ret, typename... Args>
struct Solver {
    Func m_func;
    GHASH::UnorderedMap<KeyType, Ret, MakeRecord, BUFFER> m_cache;
    template<size_type I, typename Fi, typename... RestArgs>
    uint64_t _hash(Fi&& first, RestArgs&&... args) {
        if constexpr (I == sizeof...(Args))
            return GHASH::HashCombine()(first, args...);
        else
            return _hash<I + 1>(args..., GHASH::Hash<Fi>()(first));
    }
    Solver(Func func): m_func(func) {}
    void set_initial_value(Args... args, Ret val) { m_cache.insert_or_assign(KeyType{std::forward<Args>(args)...}, val); }
    auto query(Args... args) { return operator()(*this, std::forward<Args>(args)...); }
    const Ret& operator()(Solver<Func, MakeRecord, BUFFER, KeyType, Ret, Args...>&, Args... args) {
        auto it = m_cache.insert(KeyType{std::forward<Args>(args)...});
        if (it.m_flag) it.m_ptr->m_mapped = m_func(*this, std::forward<Args>(args)...);
        return it.m_ptr->m_mapped;
    }
    void cache_clear() {
        static_assert(MakeRecord, "MakeRecord Must Be True");
        m_cache.clear();
    }
};
template<typename F>
struct RecursiveLambdaTraits : RecursiveLambdaTraits<decltype(&F::template operator()<F>)> {};
template<typename Cls, typename ReturnType, typename Self, typename... Args>
struct RecursiveLambdaTraits<ReturnType (Cls::*)(Self, Args...) const> {
    using tuple_type = std::tuple<typename std::decay<Args>::type...>;
    using return_type = ReturnType;
    template<typename Func, bool MakeRecord, size_type BUFFER, typename KeyType>
    using type = Solver<Func, MakeRecord, BUFFER, KeyType, ReturnType, Args...>;
};
} // namespace CACHE
template<bool MakeRecord, CACHE::size_type BUFFER, typename Func, typename KeyType = typename CACHE::RecursiveLambdaTraits<Func>::tuple_type, typename Solver = typename CACHE::RecursiveLambdaTraits<Func>::template type<Func, MakeRecord, BUFFER, KeyType>>
auto make_CacheSolver(Func func) -> Solver { return Solver(func); }
} // namespace OY

class Solution {
public:
    // 设移动了x次, 则 n-x*k+x = 1
    // n-1=x*(k-1)
    // (n-1)/(k-1)
    int mergeStones(std::vector<int>& stones, int k) {
        int n = stones.size();
        if ((n - 1) % (k - 1) != 0) return -1;
        std::vector<int> prefix(n + 1);
        // [0, i)
        std::partial_sum(stones.begin(), stones.end(), prefix.begin() + 1);
        auto getSum = [&](int l, int r) {
            return prefix[r + 1] - prefix[l];
        };
        // [l,r]合并为p堆的最小值
        auto dfs = [&](auto& self, int l, int r, int p) -> int {
            if (p == 1) {
                if (l == r) return 0;
                return self(self, l, r, k) + getSum(l, r);
            }
            int res = 0x3f3f3f3f;
            for (int i{l}; i < r; ++i) {
                // [l,i]合并为1堆
                res = std::min(res, self(self, l, i, 1) + self(self, i + 1, r, p - 1));
            }
            return res;
        };
        // return dfs(dfs, 0, n - 1, 1);
        auto cached_dfs = OY::make_CacheSolver<false, 30 * 30 * 30 * 2>(dfs);
        return cached_dfs.query(0, n - 1, 1);
    }
};