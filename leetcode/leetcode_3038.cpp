
#include <vector>
class Solution {
public:
    int maxOperations(std::vector<int>& nums) {
        int n = nums.size(), ans = 1;
        int sum = nums[0] + nums[1];
        for (int i = 2; i + 1 < n; i++) {
            if (nums[i] + nums[i + 1] != sum) {
                break;
            }
            ++ans;
        }
        return ans;
    }
};