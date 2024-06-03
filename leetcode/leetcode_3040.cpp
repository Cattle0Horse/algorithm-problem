#include <algorithm>
#include <functional>
#include <unordered_map>
#include <vector>
class Solution {
private:
    constexpr static long long OFFSET = 1e4;

public:
    int maxOperations(std::vector<int>& nums) {
        int n = nums.size();
        std::unordered_map<long long, int> memo;
        // [l, r]
        std::function<int(int, int, int)> dfs = [&](int sum, int l, int r) {
            if (r - l + 1 < 2) {
                return 0;
            }
            long long key = sum + l * OFFSET + r * OFFSET * OFFSET;
            if (memo.contains(key)) {
                return memo[key];
            }
            int ans = 0;
            if (nums[l] + nums[l + 1] == sum) {
                ans = std::max(ans, dfs(sum, l + 2, r) + 1);
            }
            if (nums[r - 1] + nums[r] == sum) {
                ans = std::max(ans, dfs(sum, l, r - 2) + 1);
            }
            if (nums[l] + nums[r] == sum) {
                ans = std::max(ans, dfs(sum, l + 1, r - 1) + 1);
            }
            return memo[key] = ans;
        };
        return std::max({dfs(nums[0] + nums[1], 2, n - 1),
                         dfs(nums[n - 2] + nums[n - 1], 0, n - 3),
                         dfs(nums[0] + nums[n - 1], 1, n - 2)}) +
               1;
    }
};