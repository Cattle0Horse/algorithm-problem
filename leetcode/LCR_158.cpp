/**
 * @file LCR_158.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/shu-zu-zhong-chu-xian-ci-shu-chao-guo-yi-ban-de-shu-zi-lcof/description/
 *        https://leetcode-cn.com/problems/majority-element/
 * @version 0.1
 * @date 2024-05-27
 *
 * @copyright Copyright (c) 2024
 *
 */
// 定义  x:在数组中出现次数 大于 ⌊n/2⌋ 的元素
// 定义 sum 出现一次x数sum+1, 出现一次非x数sum-1
// 1. 若存在x数, 则最后 sum>0
// 2. 若前a个数的sum=0, 则后(n-a)个数的sum>0, 即x数与数组的x数相同
// 3. 非x数之间的抵消只会使得
// 摩尔投票: 票数正负抵消, 非x数之间的抵消不会影响结果
// 具体步骤: 1. 假设出现的第一个数为x数, 若sum为0, 则不考虑前面的数
// 			2. 数组可能不存在x数: 循环计算x出现次数, 若不大于 ⌊n/2⌋ 的元素, 则不存在, 否则返回x

#include <algorithm>
#include <vector>
class Solution {
public:
    int inventoryManagement(std::vector<int>& stock) {
        int sum = 0, x = 0;
        for (int num : stock) {
            if (sum == 0) {
                x = num;
            }
            sum += (num == x ? 1 : -1);
        }
        // return std::count(stock.begin(), stock.end(), x) > (stock.size() >> 1) ? x : -1;
        return x;
    }
};