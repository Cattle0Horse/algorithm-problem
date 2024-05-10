/**
 * @file leetcode_2079.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/watering-plants/?envType=daily-question&envId=2024-05-08
 * @version 0.1
 * @date 2024-05-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <vector>
class Solution {
public:
    int wateringPlants(std::vector<int>& plants, int capacity) {
        int res = capacity, n = plants.size(), ans = 0;
        for (int i = 0; i < n; i++) {
            if (plants[i] > res) {
                res = capacity;
                // i-1 -> -1 -> i-1
                ans += 2 * i;
            }
            ans++;
            res -= plants[i];
        }
        return ans;
    }
};

int main() {
    std::vector<int> a{2, 2, 3, 3};
    int c = 5;
    Solution().wateringPlants(a, c);
    return 0;
}