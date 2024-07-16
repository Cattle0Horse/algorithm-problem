/**
 * @file leetcode_721.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/accounts-merge/description/?envType=daily-question&envId=2024-07-15
 * @version 0.1
 * @date 2024-07-15
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifdef Cattle_Horse
#include "leetcode.h" // IWYU pragma: keep
using namespace std;
#else
#define dbg(...) void(114514)
#endif

[[maybe_unused]] auto __init_io__ = []() {
    return std::cin.tie(nullptr)->sync_with_stdio(false);
}();

/**
 * @file union_find_v2.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief 支持带权的并查集
 * @version 0.1
 * @date 2024-07-13
 *
 * @copyright Copyright (c) 2024
 * fork from https://github.com/old-yan/CP-template
 * 若要使用带权并查集, 请定义一个拥有默认构造函数与unite合并两个节点的对象
 * struct Node {
 *     size_t vertex_size = 1, edge_size = 0;
 *     void unite(const Node& o) {
 *         vertex_size += o.vertex_size;
 *         edge_size += o.edge_size + 1;
 *     }
 * };
 **/
#include <algorithm>
#include <cstdint>
#include <numeric>
#include <vector>

namespace OI::DataStructure {
namespace DSU {
struct Ignore {};
using size_type = uint32_t;
template<bool MaintainGroupSize, typename ValueType = Ignore>
struct Table {
    mutable std::vector<size_type> m_father, m_group_size;
    mutable std::vector<ValueType> m_value;
    size_type m_init_size, m_cur_size, m_group_cnt;
    explicit Table(size_type n = 0, const ValueType& value = ValueType()) { resize(n, value); }
    void resize(size_type n, const ValueType& value = ValueType()) {
        if (!(m_init_size = m_cur_size = m_group_cnt = n)) return;
        m_father.resize(m_cur_size);
        if constexpr (MaintainGroupSize) m_group_size.resize(m_cur_size, 1);
        if constexpr (!std::is_same<ValueType, Ignore>::value) m_value.resize(m_cur_size, value);
        std::iota(m_father.begin(), m_father.end(), 0);
    }
    [[nodiscard]] size_type find(size_type i) const { return m_father[i] == i ? i : m_father[i] = find(m_father[i]); }
    template<bool IsHead = false>
    [[nodiscard]] size_type size(size_type i) const {
        static_assert(MaintainGroupSize, "MaintainGroupSize Must Be True");
        if constexpr (IsHead) return m_group_size[i];
        else return m_group_size[find(i)];
    }
    template<bool IsHead = false>
    [[nodiscard]] ValueType& value(size_type i) const {
        static_assert(!std::is_same<ValueType, Ignore>::value, "MaintainGroupSize Must Be True");
        if constexpr (IsHead) return m_value[i];
        else return m_value[find(i)];
    }
    void unite_to(size_type head_from, size_type head_to) {
        if (head_from == head_to) return;
        m_father[head_from] = head_to;
        if constexpr (MaintainGroupSize) m_group_size[head_to] += m_group_size[head_from];
        if constexpr (!std::is_same<ValueType, Ignore>::value) m_value[head_to].unite(m_value[head_from]);
        m_group_cnt--;
    }
    bool unite_by_size(size_type a, size_type b) {
        static_assert(MaintainGroupSize, "MaintainGroupSize Must Be True");
        a = find(a), b = find(b);
        if (a == b) return false;
        if (m_group_size[a] > m_group_size[b]) std::swap(a, b);
        unite_to(a, b);
        return true;
    }
    bool unite_by_id(size_type a, size_type b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (a < b) std::swap(a, b);
        unite_to(a, b);
        return true;
    }
    [[nodiscard]] bool in_same_group(size_type a, size_type b) const { return find(a) == find(b); }
    [[nodiscard]] bool is_head(size_type i) const { return i == m_father[i]; }
    std::vector<size_type> heads() const {
        std::vector<size_type> ret;
        ret.reserve(m_group_cnt);
        for (size_type i = 0; i != m_cur_size; i++)
            if (is_head(i)) ret.push_back(i);
        return ret;
    }
    std::vector<std::vector<size_type>> groups() const {
        if constexpr (MaintainGroupSize) {
            std::vector<std::vector<size_type>> ret(m_group_cnt);
            std::vector<size_type> index(m_cur_size);
            for (size_type i = 0, j = 0; i != m_cur_size; i++)
                if (is_head(i)) ret[j].reserve(m_group_size[i]), index[i] = j++;
            for (size_type i = 0; i != m_cur_size; i++) ret[index[find(i)]].push_back(i);
            return ret;
        } else {
            std::vector<std::vector<size_type>> ret(m_group_cnt);
            std::vector<size_type> index(m_cur_size), cnt(m_group_cnt);
            for (size_type i = 0, j = 0; i != m_cur_size; i++)
                if (is_head(i)) index[i] = j++;
            for (size_type i = 0; i != m_cur_size; i++) cnt[index[find(i)]]++;
            for (size_type i = 0; i != m_group_cnt; i++) ret[i].reserve(cnt[i]);
            for (size_type i = 0; i != m_cur_size; i++) ret[index[find(i)]].push_back(i);
            return ret;
        }
    }
};
template<typename Ostream, bool MaintainGroupSize, typename ValueType>
Ostream& operator<<(Ostream& out, const Table<MaintainGroupSize, ValueType>& x) {
    out << "[";
    for (size_type i = 0; i != x.m_cur_size; i++) {
        if (i) out << ", ";
        out << x.m_father[i];
    }
    return out << "]";
}
} // namespace DSU
template<bool MaintainGroupSize, typename ValueType = DSU::Ignore>
using DSUTable = DSU::Table<MaintainGroupSize, ValueType>;
} // namespace OI::DataStructure

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        int n = accounts.size();
        OI::DataStructure::DSUTable<false> dsu(n);
        std::unordered_map<std::string, int> belong;
        for (auto i{0}; i < n; i += 1) {
            auto& account{accounts[i]};
            for (auto j{1u}; j < account.size(); j += 1) {
                std::string& email = account[j];
                if (auto it = belong.find(email); it != belong.end()) {
                    // 合并两个节点
                    dsu.unite_by_id(it->second, i);
                } else {
                    belong[email] = i;
                }
            }
        }
        std::vector<std::vector<std::string>> ans;
        std::unordered_map<int, int> index;
        for (auto i{0}; i < n; i += 1) {
            auto root = dsu.find(i);
            if (auto it = index.find(root); it != index.end()) {
                auto& vec = ans[it->second];
                vec.insert(vec.end(), accounts[i].begin() + 1, accounts[i].end());
            } else {
                index[root] = ans.size();
                ans.push_back(accounts[i]);
            }
        }
        for (auto&& row : ans) {
            std::sort(row.begin() + 1, row.end());
            row.erase(std::unique(row.begin(), row.end()), row.end());
        }
        return ans;
    }
};

#ifdef Cattle_Horse
int main() {
    //
}
#endif