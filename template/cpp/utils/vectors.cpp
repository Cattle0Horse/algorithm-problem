#include <algorithm>
#include <deque>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

namespace OI::Vectors {
// premise: the arr in [begin, end) is ordered
//    {1, 1, 2, 3, 3, 3, 3, 3, 3}
// -> {{1, 2}, {2, 1}, {3, 6}}
template<typename T, typename Iterator>
std::vector<std::pair<T, int>> toPairCount(Iterator begin, Iterator end) {
    std::vector<std::pair<T, int>> res;
    // [left, begin)
    for (Iterator left = begin; begin != end; left = begin) {
        while (begin != end && *begin == *left) ++begin;
        res.emplace_back(*left, static_cast<int>(std::distance(left, begin)));
    }
    return res;
}
} // namespace OI::Vectors

namespace OI::Vectors {
// find the first index before index whose cmp is equal to false (return -1 if not present)
// (ans[i], i) all is cmp = true
template<typename T, typename Compare>
std::vector<int32_t> firstBeforeIndex(const std::vector<T>& arr, Compare cmp) {
    int32_t n = arr.size();
    std::vector<int32_t> before(n);
    std::deque<int32_t> stack{};
    for (int32_t i{0}; i < n; ++i) {
        while (!stack.empty() && cmp(arr[i], arr[stack.back()])) {
            stack.pop_back();
        }
        before[i] = (stack.empty() ? -1 : stack.back());
        stack.push_back(i);
    }
    return before;
}
// find the first index After index whose cmp is equal to false (return arr.size() if not present)
// (i, ans[i]) all is cmp = true
template<typename T, typename Compare>
std::vector<int32_t> firstAfterIndex(const std::vector<T>& arr, Compare cmp) {
    int32_t n = arr.size();
    std::vector<int32_t> after(n, n);
    std::deque<int32_t> stack{};
    for (int32_t i{0}; i < n; ++i) {
        while (!stack.empty() && !cmp(arr[stack.back()], arr[i])) {
            after[stack.back()] = i;
            stack.pop_back();
        }
        stack.push_back(i);
    }
    // for (int32_t back : stack) {
    //     after[back] = n;
    // }
    return after;
}

// bug:
// (ans[i].first, ans[i].second) all is cmp = true
// template<typename T, typename Compare>
// std::vector<std::pair<int32_t, int32_t>> firstBeforeAndAfterIndex(const std::vector<T>& arr, Compare cmp) {
//     int32_t n = arr.size();
//     std::vector<std::pair<int32_t, int32_t>> ans(n, {-1, n});
//     std::deque<int32_t> stack{};
//     for (int32_t i{0}; i < n; ++i) {
//         while (!stack.empty() && cmp(arr[i], arr[stack.back()])) {
//             ans[stack.back()].second = i;
//             stack.pop_back();
//         }
//         if (!stack.empty()) ans[i].first = stack.back();
//         stack.push_back(i);
//     }
//     return ans;
// }

template<typename K, typename V>
std::vector<K> keys(const std::unordered_map<K, V>& vals) {
    std::vector<K> ans(vals.size());
    std::transform(vals.begin(), vals.end(), ans.begin(), [](const auto& pair) {
        return pair.first;
    });
    return ans;
}

template<typename K, typename V>
std::vector<K> keys(const std::map<K, V>& vals) {
    std::vector<K> ans(vals.size());
    std::transform(vals.begin(), vals.end(), ans.begin(), [](const auto& pair) {
        return pair.first;
    });
    return ans;
}

template<typename K, typename V>
std::vector<K> keys(const std::unordered_multimap<K, V>& vals) {
    std::vector<K> ans(vals.size());
    std::transform(vals.begin(), vals.end(), ans.begin(), [](const auto& pair) {
        return pair.first;
    });
    return ans;
}

template<typename K, typename V>
std::vector<K> keys(const std::multimap<K, V>& vals) {
    std::vector<K> ans(vals.size());
    std::transform(vals.begin(), vals.end(), ans.begin(), [](const auto& pair) {
        return pair.first;
    });
    return ans;
}

template<typename K, typename V>
std::vector<V> values(const std::unordered_map<K, V>& vals) {
    std::vector<V> ans(vals.size());
    std::transform(vals.begin(), vals.end(), ans.begin(), [](const auto& pair) {
        return pair.second;
    });
    return ans;
}

template<typename K, typename V>
std::vector<V> values(const std::map<K, V>& vals) {
    std::vector<V> ans(vals.size());
    std::transform(vals.begin(), vals.end(), ans.begin(), [](const auto& pair) {
        return pair.second;
    });
    return ans;
}

template<typename K, typename V>
std::vector<V> values(const std::unordered_multimap<K, V>& vals) {
    std::vector<V> ans(vals.size());
    std::transform(vals.begin(), vals.end(), ans.begin(), [](const auto& pair) {
        return pair.second;
    });
    return ans;
}

template<typename K, typename V>
std::vector<V> values(const std::multimap<K, V>& vals) {
    std::vector<V> ans(vals.size());
    std::transform(vals.begin(), vals.end(), ans.begin(), [](const auto& pair) {
        return pair.second;
    });
    return ans;
}

template<typename T>
std::vector<T>& operator+=(std::vector<T>& lhs, const std::vector<T>& rhs) {
    lhs.insert(lhs.end(), rhs.begin(), rhs.end());
    return lhs;
}

template<typename T>
std::vector<T> operator+(std::vector<T> lhs, const std::vector<T>& rhs) {
    return lhs += rhs;
}

template<typename T>
std::vector<T>& operator*=(std::vector<T>& vec, size_t k) {
    if (k == 0) {
        vec.clear();
    } else {
        size_t n = vec.size() * k;
        vec.reserve(n);
        while (vec.size() * 2 <= n) vec += vec;
        if (n != vec.size()) vec.insert(vec.end(), vec.begin(), vec.begin() + (n - vec.size()));
    }
    return vec;
}

template<typename T>
std::vector<T> operator*(std::vector<T> vec, size_t k) {
    return vec *= k;
}

template<typename T>
std::vector<T> sorted(std::vector<T> arr) {
    std::ranges::sort(arr);
    return arr;
}

template<typename T, typename... Args>
std::vector<T> sorted(std::vector<T> arr, Args&&... args) {
    std::ranges::sort(arr, args...);
    return arr;
}

template<typename T>
std::vector<T> uniqued(std::vector<T> arr) {
    const auto ret = std::ranges::unique(arr);
    arr.erase(ret.begin(), ret.end());
    return arr;
}

template<typename T, typename... Args>
std::vector<T> uniqued(std::vector<T> arr, Args&&... args) {
    const auto ret = std::ranges::unique(arr, args...);
    arr.erase(ret.begin(), ret.end());
    return arr;
}

template<typename T>
std::vector<T> reversed(std::vector<T> arr) {
    std::ranges::reverse(arr);
    return arr;
}

template<typename T, bool WITH_SIZE = false>
void println(const std::vector<T>& arr) {
    auto n{arr.size()};
    if constexpr (WITH_SIZE) {
        std::cout << n << '\n';
    }
    for (decltype(n) i{0}; i < n; i += 1) {
        std::cout << arr[i] << " \n"[i + 1 == n];
    }
}

} // namespace OI::Vectors