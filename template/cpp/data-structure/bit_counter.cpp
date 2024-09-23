/**
 * @file bit_counter.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief
 * @version 0.1
 * @date 2024-06-25
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <array>
#include <cstdint>
namespace OI::DataStructure {
template<size_t N, typename CntType = int32_t>
struct StaticBitCounter : std::array<CntType, N> {
    template<typename T>
    T getDecimal() const {
        T mask{0};
        for (size_t i{0}; i < N; ++i) mask |= (this->at(i) > 0) << i;
        return mask;
    }
    template<typename T>
    StaticBitCounter& operator+=(T mask) {
        for (size_t i{0}; i < N; ++i) this->at(i) += (mask >> i & 1);
        return *this;
    }
    StaticBitCounter& operator+=(const StaticBitCounter& other) {
        for (size_t i{0}; i < N; ++i) this->at(i) += other.at(i);
        return *this;
    }
    template<typename T>
    StaticBitCounter& operator-=(T mask) {
        for (size_t i{0}; i < N; ++i) this->at(i) -= (mask >> i & 1);
        return *this;
    }
    StaticBitCounter& operator-=(const StaticBitCounter& other) {
        for (size_t i{0}; i < N; ++i) this->at(i) -= other.at(i);
        return *this;
    }
    template<typename T>
    friend StaticBitCounter operator+(const StaticBitCounter& lhs, const T& rhs) { return StaticBitCounter{lhs} += rhs; }
    template<typename T>
    friend StaticBitCounter operator+(const T& lhs, const StaticBitCounter& rhs) { return StaticBitCounter{rhs} += lhs; }
    friend StaticBitCounter operator+(const StaticBitCounter& lhs, const StaticBitCounter& rhs) { return StaticBitCounter{lhs} += rhs; }
    template<typename T>
    friend StaticBitCounter operator-(const StaticBitCounter& lhs, const T& rhs) { return StaticBitCounter{lhs} += rhs; }
    template<typename T>
    friend StaticBitCounter operator-(const T& lhs, const StaticBitCounter& rhs) { return StaticBitCounter{rhs} += lhs; }
    friend StaticBitCounter operator-(const StaticBitCounter& lhs, const StaticBitCounter& rhs) { return StaticBitCounter{lhs} += rhs; }
};
} // namespace OI::DataStructure