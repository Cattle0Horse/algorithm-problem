/**
 * @file leetcode_165.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/compare-version-numbers/description/
 * @version 0.1
 * @date 2024-06-16
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <cstdint>
#include <cstdlib>
#include <string>
using namespace std;

class Solution {
private:
    // 闭包: 实际就是一个类, 将变量作为属性
    struct Closure {
        uint32_t l;
        const std::string& s;

        Closure(const std::string& str): l(0), s(str) {}

        int get() {
            uint32_t r = l;
            while (r < s.length() && s[r] != '.') ++r;
            if (l == r) return 0;
            int ans = std::stoi(s.substr(l, r - l));
            l = r + 1;
            return ans;
        }

        bool has() {
            return l < s.length();
        }
    };

public:
    int compareVersion(string version1, string version2) {
        Closure closure1(version1);
        Closure closure2(version2);
        while (closure1.has() || closure2.has()) {
            int v1{closure1.get()};
            int v2{closure2.get()};
            if (v1 < v2) return -1;
            if (v1 > v2) return 1;
        }
        return 0;
    }
};

int main() {
    Solution().compareVersion("1.2", "1.10");
    return 0;
}