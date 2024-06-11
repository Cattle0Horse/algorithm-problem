/**
 * @file leetcode_139.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/word-break/
 * @version 1.0
 * @date 2024-06-11
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <unordered_set>
#include <vector>
class Solution {
public:
    bool wordBreak(std::string s, std::vector<std::string>& wordDict) {
        std::unordered_set<std::string> words(wordDict.begin(), wordDict.end());
        int n = s.length();
        std::vector<bool> dp(n + 1, false);
        dp[0] = true;
        for (int i{0}; i < n; ++i) {
            if (!dp[i]) continue;
            for (int j{i + 1}; j <= n; ++j) {
                if (words.contains(s.substr(i, j - i))) {
                    dp[j] = true;
                }
            }
        }
        return dp[n];
    }
};

/**
 * @file leetcode_139.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/word-break/
 * @version 0.1
 * @date 2024-06-11
 *
 * @copyright Copyright (c) 2024
 * KMP
 */

// #include <map>
// #include <vector>
// #include <iterator>
// #include <vector>

// namespace OI::String::KMP {

// template<typename _InputIt>
// std::vector<int> getMaxMatchLength(_InputIt first, _InputIt last) {
//     int n = std::distance(first, last);
//     std::vector<int> maxMatchLength(n, 0);
//     for (int i = 1, j = 0; i < n; ++i) {
//         while (j > 0 && first[i] != first[j]) j = maxMatchLength[j - 1];
//         if (first[i] == first[j]) ++j;
//         maxMatchLength[i] = j;
//     }
//     return maxMatchLength;
// }

// template<typename _InputIt>
// std::vector<int> getAllIndex(_InputIt _text_first, _InputIt _text_last, _InputIt _patter_first, _InputIt _patter_last) {
//     std::vector<int> ans;
//     std::vector<int> maxMatchLength(getMaxMatchLength(_patter_first, _patter_last));
//     int n = std::distance(_text_first, _text_last);
//     int m = std::distance(_patter_first, _patter_last);
//     for (int i = 0, j = 0; i < n; ++i) {
//         while (j > 0 && _text_first[i] != _patter_first[j]) j = maxMatchLength[j - 1];
//         if (_text_first[i] == _patter_first[j]) ++j;
//         if (j == m) {
//             ans.push_back(i - m + 1);
//             j = maxMatchLength[j - 1];
//         }
//     }
//     return ans;
// }
// template<typename _InputIt>
// int getFirstIndex(_InputIt _text_first, _InputIt _text_last, _InputIt _patter_first, _InputIt _patter_last) {
//     std::vector<int> maxMatchLength(getMaxMatchLength(_patter_first, _patter_last));
//     int n = std::distance(_text_first, _text_last);
//     int m = std::distance(_patter_first, _patter_last);
//     for (int i = 0, j = 0; i < n; ++i) {
//         while (j > 0 && _text_first[i] != _patter_first[j]) j = maxMatchLength[j - 1];
//         if (_text_first[i] == _patter_first[j]) ++j;
//         if (j == m) return i - m + 1;
//     }
//     return -1;
// }

// } // namespace OI::String::KMP
// class Solution {
// public:
//     // 字典中的字符串转化为对应在s中的 下标区间
//     // 看这些下标区间能否连成s
//     bool wordBreak(std::string s, std::vector<std::string>& wordDict) {
//         // [l, r)
//         // std::vector<std::pair<int, int>> intervals;
//         std::map<int, std::vector<int>> intervals;
//         for (auto&& str : wordDict) {
//             for (int l : OI::String::KMP::getAllIndex(s.begin(), s.end(), str.begin(), str.end())) {
//                 // intervals.emplace_back(l, l + str.length());
//                 intervals[l].push_back(l + str.length());
//             }
//         }
//         int n = s.length();
//         // [l, r)
//         std::vector<bool> have(n + 1);
//         auto it = intervals.find(0);
//         if (it == intervals.end()) return false;
//         have[0] = true;
//         for (int r : intervals[0]) {
//             have[r] = true;
//         }
//         for (; ++it != intervals.end();) {
//             if (have[it->first]) {
//                 for (int r : it->second) {
//                     have[r] = true;
//                 }
//             }
//         }
//         return have[n];
//     }
// };