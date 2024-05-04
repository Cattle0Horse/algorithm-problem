/**
 * @file leetcode_2739.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/total-distance-traveled/description/?envType=daily-question&envId=2024-04-25
 * @version 0.1
 * @date 2024-04-25
 *
 * @copyright Copyright (c) 2024
 *
 */

class Solution {
public:
    int distanceTraveled(int mainTank, int additionalTank) {
        int ans = 0;
        while (mainTank >= 5 && additionalTank > 0) {
            ans += 50;
            mainTank -= 5;
            mainTank += 1;
            additionalTank -= 1;
        }
        return ans + mainTank * 10;
    }
};