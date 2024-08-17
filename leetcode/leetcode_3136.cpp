#ifdef Cattle_Horse
#include "leetcode.h" // IWYU pragma: keep
using namespace std;
#else
#define dbg(...) void(114514)
#endif

[[maybe_unused]] int __init_io__ = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cout << std::fixed << std::setprecision(20);
    return 0;
}();

class Solution {
public:
    bool isValid(string word) {
        std::set<char> vowels{'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};

        if (word.length() < 3) return false;
        bool vowel = false, consonant = false;
        for (char c : word) {
            if (vowels.contains(c)) {
                vowel = true;
            } else if ('0' <= (c) && (c) <= '9') {
                // do nothing
            } else if ('a' <= (c) && (c) <= 'z') {
                consonant = true;
            } else if ('A' <= (c) && (c) <= 'Z') {
                consonant = true;
            } else {
                return false;
            }
        }
        return vowel && consonant;
    }
};

#ifdef Cattle_Horse
int main() {
    //
}
#endif