#include <algorithm>
#include <unordered_map>
#include <vector>
class Solution {
public:
    int maxSelectedElements(std::vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        std::unordered_map<int, int> dp;
        for (int num : nums) {
            // num可以接在num-1后
            // 也可以+1再接在num后
            dp[num + 1] = dp[num] + 1;
            dp[num] = dp.contains(num - 1) ? dp[num - 1] + 1 : 1;
        }
        int ans = 0;
        for (auto&& [key, val] : dp) {
            ans = std::max(ans, val);
        }
        return ans;
    }
};