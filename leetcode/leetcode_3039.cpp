#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>
class Solution {
public:
    std::string lastNonEmptyString(std::string s) {
        std::string ans;

        std::unordered_map<char, int> cnt;
        int n = s.length(), max = 0;

        std::vector<int> nums(n, 0);
        for (int i = 0; i < n; i++) {
            nums[i] = ++cnt[s[i]];
            max = std::max(max, nums[i]);
        }
        for (int i{0}; i < n; ++i) {
            if (nums[i] == max) {
                ans += s[i];
            }
        }
        return ans;
    }
};