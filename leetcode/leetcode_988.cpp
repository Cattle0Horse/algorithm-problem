// @date 2024/8/17 10:18:25
// @author Cattle_Horse (CattleHorse@duck.com)
// @problem 988. 从叶结点开始的最小字符串
// @link https://leetcode.cn/contest/weekly-contest-122/problems/smallest-string-starting-from-leaf/

#ifdef Cattle_Horse
#include "leetcode.h" // IWYU pragma: keep
using namespace std;
#else
#define dbg(...) void(114514)
#endif

[[maybe_unused]] auto __init_io__ = []() {
    return std::cin.tie(nullptr)->sync_with_stdio(false);
}();

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool compare(const std::string& a, const std::string& b) {
        if (a.length() != b.length()) return a.length() < b.length();
        for (size_t i = a.length(); i > 0; i -= 1) {
            if (a[i - 1] != b[i - 1]) return a[i - 1] < b[i - 1];
        }
        return false;
    }
    string smallestFromLeaf(TreeNode* root) {
        std::string ans{};
        std::string path{};
        auto dfs = [&](auto&& self, TreeNode* cur) -> void {
            path.push_back(static_cast<char>(cur->val + 'a'));
            if (cur->left == nullptr && cur->right == nullptr) {
                if (ans.empty() || compare(path, ans)) {
                    ans = path;
                }
            } else {
                if (cur->left) self(self, cur->left);
                if (cur->right) self(self, cur->right);
            }
            path.pop_back();
        };
        dfs(dfs, root);
        std::reverse(ans.begin(), ans.end());
        return ans;
    }
};

// string Solution::smallestFromLeaf(TreeNode* root)

#ifdef Cattle_Horse
int main() {
    std::cout << "*** 988. 从叶结点开始的最小字符串 ***" << std::endl
              << std::endl;

    Solution s0;

    {
        std::cout << "Test 1: ";

        vector<TreeNode> _root;
        TreeNode* root = TreeNode::create("[0,1,2,3,4,3,4]", _root);
        string ans0 = s0.smallestFromLeaf(root);
        string exp0 = "dba";

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

        vector<TreeNode> _root;
        TreeNode* root = TreeNode::create("[25,1,3,1,3,0,2]", _root);
        string ans1 = s0.smallestFromLeaf(root);
        string exp1 = "adz";

        if (ans1 == exp1) {
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
            std::cout << "  Answer: " << ans1 << std::endl;
            std::cout << "  Expect: " << exp1 << std::endl;
        }
    }

    {
        std::cout << "Test 3: ";

        vector<TreeNode> _root;
        TreeNode* root = TreeNode::create("[2,2,1,null,1,0,null,0]", _root);
        string ans2 = s0.smallestFromLeaf(root);
        string exp2 = "abc";

        if (ans2 == exp2) {
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
            std::cout << "  Answer: " << ans2 << std::endl;
            std::cout << "  Expect: " << exp2 << std::endl;
        }
    }

    return 0;
}
#endif
