// @date 2024/7/20 14:32:22
// @author Cattle_Horse (CattleHorse@duck.com)
// @problem 2850. 将石头分散到网格图的最少移动次数
// @link https://leetcode.cn/classic/problems/minimum-moves-to-spread-stones-over-grid/description/

#ifdef Cattle_Horse
#include "leetcode.h" // IWYU pragma: keep
using namespace std;
#else
#define dbg(...) void(114514)
#endif

[[maybe_unused]] auto __init_io__ = []() {
    return std::cin.tie(nullptr)->sync_with_stdio(false);
}();

class Solution {
public:
    int minimumMoves(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        std::vector<int> less, more;
        for (auto i{0}; i < n; i += 1) {
            for (auto j{0}; j < m; j += 1) {
                int k = i * n + j;
                if (grid[i][j] == 0) {
                    less.push_back(k);
                } else {
                    for (; grid[i][j] > 1; grid[i][j] -= 1) {
                        more.push_back(k);
                    }
                }
            }
        }
        int ans = 0x3f3f3f3f;
        do {
            int res = 0;
            for (auto k{0u}; k < more.size(); k += 1) {
                res += std::abs(more[k]/n-less[k]/n) + std::abs(more[k]%n-less[k]%n);
            }
            ans = std::min(ans, res);
        } while (std::ranges::next_permutation(more).found);
        return ans;
    }
};

// int Solution::minimumMoves(vector<vector<int>> grid)

#ifdef Cattle_Horse
int main() {
    std::cout << "*** 2850. 将石头分散到网格图的最少移动次数 ***" << std::endl
              << std::endl;

    Solution s0;

    {
        std::cout << "Test 1: ";

        vector<vector<int>> grid = {{1, 1, 0}, {1, 1, 1}, {1, 2, 1}};
        int ans0 = s0.minimumMoves(grid);
        int exp0 = 3;

        if (ans0 == exp0) {
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
            std::cout << "  Answer: " << ans0 << std::endl;
            std::cout << "  Expect: " << exp0 << std::endl;
        }
    }

    {
        std::cout << "Test 2: ";

        vector<vector<int>> grid = {{1, 3, 0}, {1, 0, 0}, {1, 0, 3}};
        int ans1 = s0.minimumMoves(grid);
        int exp1 = 4;

        if (ans1 == exp1) {
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
            std::cout << "  Answer: " << ans1 << std::endl;
            std::cout << "  Expect: " << exp1 << std::endl;
        }
    }

    return 0;
}
#endif
