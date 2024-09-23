/**
 * @file kmp.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief
 * @version 0.1
 * @date 2024-04-24
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iterator>
#include <vector>

namespace OI::KMP {
template<typename _InputIt>
std::vector<int> getMaxMatchLength(_InputIt first, _InputIt last) {
    int n = std::distance(first, last);
    std::vector<int> maxMatchLength(n, 0);
    for (int i = 1, j = 0; i < n; ++i) {
        while (j > 0 && first[i] != first[j]) j = maxMatchLength[j - 1];
        if (first[i] == first[j]) ++j;
        maxMatchLength[i] = j;
    }
    return maxMatchLength;
}
template<typename _InputIt1, typename _InputIt2>
std::vector<int> getAllIndex(_InputIt1 _text_first, _InputIt1 _text_last, _InputIt2 _patter_first, _InputIt2 _patter_last) {
    std::vector<int> ans;
    std::vector<int> maxMatchLength(getMaxMatchLength(_patter_first, _patter_last));
    int n = std::distance(_text_first, _text_last);
    int m = std::distance(_patter_first, _patter_last);
    for (int i = 0, j = 0; i < n; ++i) {
        while (j > 0 && _text_first[i] != _patter_first[j]) j = maxMatchLength[j - 1];
        if (_text_first[i] == _patter_first[j]) ++j;
        if (j == m) {
            ans.push_back(i - m + 1);
            j = maxMatchLength[j - 1];
        }
    }
    return ans;
}
template<typename _InputIt1, typename _InputIt2>
int getFirstIndex(_InputIt1 _text_first, _InputIt1 _text_last, _InputIt2 _patter_first, _InputIt2 _patter_last) {
    std::vector<int> maxMatchLength(getMaxMatchLength(_patter_first, _patter_last));
    int n = std::distance(_text_first, _text_last);
    int m = std::distance(_patter_first, _patter_last);
    for (int i = 0, j = 0; i < n; ++i) {
        while (j > 0 && _text_first[i] != _patter_first[j]) j = maxMatchLength[j - 1];
        if (_text_first[i] == _patter_first[j]) ++j;
        if (j == m) return i - m + 1;
    }
    return -1;
}
} // namespace OI::KMP