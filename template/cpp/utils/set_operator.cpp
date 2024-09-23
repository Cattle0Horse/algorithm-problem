#include <set>
#include <algorithm>

template<typename V>
std::set<V> operator&(const std::set<V>& lhs, const std::set<V>& rhs) {
    std::set<V> intersection;
#ifdef __cpp_lib_ranges
    std::ranges::set_intersection(lhs, rhs, back_inserter(intersection));
#else
    std::set_intersection(lhs.begin(), lhs.end(),
                          rhs.begin(), rhs.end(),
                          back_inserter(intersection));
#endif
    return intersection;
}
template<typename V>
std::set<V>& operator&=(std::set<V>& lhs, const std::set<V>& rhs) {
    return lhs = lhs & rhs;
}
template<typename V>
std::set<V>& operator-=(std::set<V>& lhs, const std::set<V>& rhs) {
    return lhs = lhs - rhs;
}
template<typename V>
std::set<V> operator|(const std::set<V>& lhs, const std::set<V>& rhs) {
    std::set<V> _union;
#ifdef __cpp_lib_ranges
    std::ranges::set_union(lhs, rhs, inserter(_union, _union.begin()));
#else
    std::set_union(lhs.begin(), lhs.end(),
                   rhs.begin(), rhs.end(),
                   back_inserter(_union, _union.begin()));
#endif
    return _union;
}
template<typename V>
std::set<V>& operator|=(std::set<V>& lhs, const std::set<V>& rhs) {
    return lhs = lhs | rhs;
}
template<typename V>
std::set<V> operator-(const std::set<V>& lhs, const std::set<V>& rhs) {
    std::set<V> difference;
#ifdef __cpp_lib_ranges
    std::ranges::set_difference(lhs, rhs, back_inserter(difference, difference.begin()));
#else
    std::set_difference(lhs.begin(), lhs.end(),
                        rhs.begin(), rhs.end(),
                        back_inserter(difference, difference.begin()));
#endif
    return difference;
}
template<typename V>
std::set<V> operator^(const std::set<V>& lhs, const std::set<V>& rhs) {
    std::set<V> _symmetric_difference;
#ifdef __cpp_lib_ranges
    std::ranges::set_symmetric_difference(lhs, rhs, back_inserter(_symmetric_difference));
#else
    std::set_symmetric_difference(lhs.begin(), lhs.end(),
                                  rhs.begin(), rhs.end(),
                                  back_inserter(_symmetric_difference));
#endif
    return _symmetric_difference;
}
template<typename V>
std::set<V>& operator^=(std::set<V>& lhs, const std::set<V>& rhs) {
    return lhs = lhs ^ rhs;
}