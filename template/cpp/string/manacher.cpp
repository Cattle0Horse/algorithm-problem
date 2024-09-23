#include <algorithm>
#include <vector>

namespace OI::Strings {
template<typename T>
std::vector<int> manacher(const T& str, int n) { // the str.begin of idx is 0
    if (n == 0) return std::vector<int>();
    int N = 2 * n + 1;
    T s(N, '#'); // do init
    for (int i = 0; i < n; ++i) s[2 * i + 1] = str[i];
    // int ans = 0;
    std::vector<int> len(N, 1);
    for (int i = 0, l = 0, r = 0; i < N; ++i) {
        if (i < r) len[i] = std::min(len[l + r - i], r - i + 1);
        while (i - len[i] >= 0 && i + len[i] < N && s[i - len[i]] == s[i + len[i]]) ++len[i];
        if (i + len[i] - 1 > r) l = i - len[i] + 1, r = i + len[i] - 1;
        /*
        ans=max(ans,len[i]-1);//得最长回文串长度;
        int length = len[i]-1;  int x=i-length,y=i+length;//以拓展后的以i为中心的最长回文串左右端点
        string ans; for(int i=x+1;i<y;i+=2)ans+=str[i/2];
        */
    }
    return len;
}
template<typename T>
std::vector<int> manacher(const T& str) {
    return manacher(str, static_cast<int>(str.size()));
}
} // namespace OI::Strings