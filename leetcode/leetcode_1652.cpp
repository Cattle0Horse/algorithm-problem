/**
 * @file leetcode_1652.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/defuse-the-bomb/?envType=daily-question&envId=2024-05-05
 * @version 0.2
 * @date 2024-05-05
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <cstdlib>
#include <numeric>
#include <vector>
class Solution {
public:
    std::vector<int> decrypt(std::vector<int>& code, int k) {
        int n = code.size();
        std::vector<int> ans(n);
        int r = k > 0 ? k + 1 : n;
        k = std::abs(k);
        int s = std::reduce(code.begin() + r - k, code.begin() + r); // ans[0]
        for (int i = 0; i < n; i++) {
            ans[i] = s;
            s += code[r % n] - code[(r - k) % n];
            r++;
        }
        return ans;
    }
};

/**
 * @file leetcode_1652.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/defuse-the-bomb/?envType=daily-question&envId=2024-05-05
 * @version 0.1
 * @date 2024-05-05
 *
 * @copyright Copyright (c) 2024
 *
 */

// class Solution {
// public:
//     std::vector<int> decrypt(std::vector<int>& code, int k) {
//         int n = code.size();
//         std::vector<int> ans(n);
//         if (k == 0) return ans;
//         int sum = 0, r = 0, cnt = 0, dif = k < 0 ? -1 : 1;
//         k = std::abs(k);
//         // (l, r]
//         for (int l = 0, first = true; first || l != 0; sum -= code[l = (l + dif + n) % n], --cnt, first = false) {
//             while (cnt < k) {
//                 sum += code[r = (r + dif + n) % n];
//                 ++cnt;
//             }
//             ans[l] = sum;
//         }
//         return ans;
//     }
// };
int main() {
    std::vector<int> code{5, 7, 1, 4};
    int k = 3;
    Solution().decrypt(code, k);
    return 0;
}