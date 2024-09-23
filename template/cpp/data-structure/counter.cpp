/**
 * @file counter.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief
 * @version 0.1
 * @date 2024-07-01
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <unordered_map>
#include <vector>
namespace OI::DataStructure {
template<typename K, std::integral V>
struct Counter : std::unordered_map<K, V> {
    Counter(const std::unordered_map<K, V>& _unordered_map): std::unordered_map<K, V>(_unordered_map) {}
    template<class InputIterator>
    Counter(InputIterator first, InputIterator last): std::unordered_map<K, V>() {
        for (; first != last; ++first) ++(*this)[first];
    }
    template<class InputIterator>
    Counter(const std::vector<K>& arr): std::unordered_map<K, V>() {
        for (auto&& v : arr) ++(*this)[v];
    }
    Counter& operator+=(const Counter& rhs) {
        for (auto&& [k, v] : rhs) (*this)[k] += v;
        return *this;
    }
    Counter& operator-=(const Counter& rhs) {
        for (auto&& [k, v] : rhs) (*this)[k] -= v;
        return *this;
    }
    friend Counter& operator+(const Counter& lhs, const Counter& rhs) {
        return Counter(lhs) += rhs;
    }
    friend Counter& operator-(Counter& lhs, const Counter& rhs) {
        return Counter(lhs) -= rhs;
    }
};
} // namespace OI::DataStructure