#include <algorithm>
#include <string>
namespace OI::Strings {
std::string& operator*=(std::string& s, size_t k) {
    if (k == 0) {
        s.clear();
    } else {
        size_t n = s.size() * k;
        s.reserve(n);
        while (s.size() * 2 <= n) s += s;
        if (n != s.size()) s.insert(s.end(), s.begin(), s.begin() + (n - s.size()));
    }
    return s;
}
std::string operator*(std::string s, size_t k) {
    return s *= k;
}
std::string sorted(std::string s) {
    std::ranges::sort(s);
    return s;
}
template<typename... Args>
std::string sorted(std::string s, Args&&... args) {
    std::ranges::sort(s, args...);
    return s;
}
std::string uniqued(std::string s) {
    const auto ret = std::ranges::unique(s);
    s.erase(ret.begin(), ret.end());
    return s;
}
template<typename... Args>
std::string uniqued(std::string s, Args&&... args) {
    const auto ret = std::ranges::unique(s, args...);
    s.erase(ret.begin(), ret.end());
    return s;
}
std::string reversed(std::string s) {
    std::ranges::reverse(s);
    return s;
}
} // namespace OI::Strings