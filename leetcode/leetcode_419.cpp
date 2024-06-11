/**
 * @file leetcode_419.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/battleships-in-a-board/?envType=daily-question&envId=2024-06-11
 * @version 0.1
 * @date 2024-06-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <vector>
class Solution {
public:
    // 以左/上的点作为战舰头部
    // 如果当前点(i,j)是x, 则(i-1,j)和(i,j-1)不能是x, 否则当前点不算一个单独的战舰
    int countBattleships(std::vector<std::vector<char>>& board) {
        int n = board.size(), m = board.front().size(), ans = 0;
        for (int i{0}; i < n; ++i) {
            for (int j{0}; j < m; ++j) {
                if (board[i][j] == 'X' && (i == 0 || board[i - 1][j] == '.') && (j == 0 || board[i][j - 1] == '.')) {
                    ++ans;
                }
            }
        }
        return ans;
    }
};