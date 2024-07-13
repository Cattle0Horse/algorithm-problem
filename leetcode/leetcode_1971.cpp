/**
 * @file leetcode_1971.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/find-if-path-exists-in-graph/
 * @version 0.1
 * @date 2024-07-13
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifdef OY_LOCAL
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;
#endif

[[maybe_unused]] auto __init_io__ = []() {
    return std::cin.tie(nullptr)->sync_with_stdio(false);
}();

#include <cstdint>
#include <numeric>
#include <stdexcept>
#include <vector>
#include <sstream>
struct BaseUnionFind {
    std::vector<uint32_t> m_father;
    uint32_t m_initial_size;
    uint32_t m_current_size;
    explicit BaseUnionFind(uint32_t n) noexcept: m_father(n), m_initial_size(n), m_current_size(n) {
        std::iota(m_father.begin(), m_father.end(), 0);
    }
    [[nodiscard]] uint32_t find_uncheck(uint32_t id) {
        return m_father[id] == id ? id : m_father[id] = find(m_father[id]);
    }
    [[nodiscard]] uint32_t find(uint32_t id) {
        if (id >= m_initial_size) {
            std::stringstream ss;
            ss << "id should be in the range [0, " << m_initial_size << "), but id is " << id;
            throw std::out_of_range(ss.str());
        }
        return find_uncheck(id);
    }
    bool merge(uint32_t x, uint32_t y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        m_father[x] = y;
        return true;
    }
    [[nodiscard]] bool same(uint32_t x, uint32_t y) { return find(x) == find(y); }
};

struct UnionFind : public BaseUnionFind {
    std::vector<uint32_t> m_node_count;
    explicit UnionFind(uint32_t n) noexcept: BaseUnionFind(n), m_node_count(n, 1) {}
    bool merge(uint32_t x, uint32_t y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        // 如果x的节点个数小于y，则将x合并到y中，否则将y合并到x中
        if (m_node_count[x] < m_node_count[y]) {
            m_father[x] = y;
            m_node_count[y] += m_node_count[x];
        } else {
            m_father[y] = x;
            m_node_count[x] += m_node_count[y];
        }
        --m_current_size;
        return true;
    }
    uint32_t getSize(uint32_t id) {
        return m_node_count[find_uncheck(id)];
    }
};

class Solution {
public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        BaseUnionFind dsu(n);
        for (auto&& edge : edges) {
            dsu.merge(edge[0], edge[1]);
        }
        return dsu.same(source, destination);
    }
};