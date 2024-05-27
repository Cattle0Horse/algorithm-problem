/**
 * @file LCR_177.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/shu-zu-zhong-shu-zi-chu-xian-de-ci-shu-lcof/
 * @version 0.1
 * @date 2024-05-28
 *
 * @copyright Copyright (c) 2024
 * 1. 数组的异或和 等于 两个结果数字的异或和
 * 2. 由于两个数字不同, 因此该异或和不为0
 * 3. 若某一bit位为1, 则可以将数分为两组, 这两组各包含一个结果数字
 */
#include <functional>
#include <numeric>
#include <vector>

class Solution {
public:
    std::vector<int> sockCollocation(std::vector<int>& sockets) {
        std::vector<int> ans(2);
        int xor_sum = std::reduce(sockets.begin(), sockets.end(), 0, std::bit_xor<int>());
        int one_bit = xor_sum & -xor_sum;
        for (int socket : sockets) {
            ans[(one_bit & socket) == 0] ^= socket;
        }
        return ans;
    }
};