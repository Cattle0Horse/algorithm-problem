/**
 * @file dynamic_bit_counter.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief
 * @version 0.1
 * @date 2024-06-25
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <vector>
namespace OI::DataStructure {
template<typename CntType = int32_t>
struct DynamicBitCounter : std::vector<CntType> {
    template<typename T>
    T getDecimal() const {
        T mask{0};
        for (size_t i{0}, n{this->size()}; i < n; ++i) mask |= (this->at(i) > 0) << i;
        return mask;
    }
    template<typename T>
    DynamicBitCounter& operator+=(T mask) {
        for (size_t i{0}, n{this->size()}; i < n; ++i) this->at(i) += (mask >> i & 1);
        return *this;
    }
    DynamicBitCounter& operator+=(const DynamicBitCounter& other) {
        size_t m = other.size();
        if (this->size() < m) this->resize(m);
        for (size_t i{0}, n{std::min(this->size(), m)}; i < n; ++i) this->at(i) += other.at(i);
        return *this;
    }
    template<typename T>
    DynamicBitCounter& operator-=(T mask) {
        for (size_t i{0}, n{this->size()}; i < n; ++i) this->at(i) -= (mask >> i & 1);
        return *this;
    }
    DynamicBitCounter& operator-=(const DynamicBitCounter& other) {
        size_t m = other.size();
        if (this->size() < m) this->resize(m);
        for (size_t i{0}, n{std::min(this->size(), m)}; i < n; ++i) this->at(i) += other.at(i);
        return *this;
    }
    template<typename T>
    friend DynamicBitCounter operator+(const DynamicBitCounter& lhs, const T& rhs) { return DynamicBitCounter{lhs} += rhs; }
    template<typename T>
    friend DynamicBitCounter operator+(const T& lhs, const DynamicBitCounter& rhs) { return DynamicBitCounter{rhs} += lhs; }
    friend DynamicBitCounter operator+(const DynamicBitCounter& lhs, const DynamicBitCounter& rhs) { return DynamicBitCounter{lhs} += rhs; }
    template<typename T>
    friend DynamicBitCounter operator-(const DynamicBitCounter& lhs, const T& rhs) { return DynamicBitCounter{lhs} += rhs; }
    template<typename T>
    friend DynamicBitCounter operator-(const T& lhs, const DynamicBitCounter& rhs) { return DynamicBitCounter{rhs} += lhs; }
    friend DynamicBitCounter operator-(const DynamicBitCounter& lhs, const DynamicBitCounter& rhs) { return DynamicBitCounter{lhs} += rhs; }
};
} // namespace OI::DataStructure