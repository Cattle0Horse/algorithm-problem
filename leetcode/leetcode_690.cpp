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

class Employee {
public:
    int id;
    int importance;
    vector<int> subordinates;
};

class Solution {
public:
    int getImportance(vector<Employee*> employees, int id) {
        std::unordered_map<int, Employee*> mp(employees.size());
        for (auto&& e : employees) {
            mp[e->id] = e;
        }
        auto dfs = [&](auto&& self, Employee* cur) -> int {
            int sum = cur->importance;
            for (auto&& i : cur->subordinates) {
                sum += self(self, mp[i]);
            }
            return sum;
        };
        return dfs(dfs, mp[id]);
    }
};

#ifdef Cattle_Horse
int main() {
    //
}
#endif