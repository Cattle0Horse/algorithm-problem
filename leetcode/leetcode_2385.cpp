/**
 * @file leetcode_2385.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/amount-of-time-for-binary-tree-to-be-infected/description/?envType=daily-question&envId=2024-04-24
 * @version 0.1
 * @date 2024-04-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <algorithm>
#include <utility>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x = 0, TreeNode* left = nullptr, TreeNode* right = nullptr): val(x), left(left), right(right) {}
};

class Solution {
private:
    int sickVal, sickDepth, ans;

public:
    std::pair<bool, int> dfs(TreeNode* root, int depth) {
        if (root == nullptr) return {false, depth - 1};
        auto l = dfs(root->left, depth + 1);
        auto r = dfs(root->right, depth + 1);
        int max_depth = std::max(l.second, r.second);
        if (root->val != sickVal && !l.first && !r.first) {
            return {false, max_depth};
        }
        if (root->val == sickVal) {
            sickDepth = depth;
            ans = std::max(ans, max_depth - depth);
        } else if (l.first) {
            ans = std::max(ans, r.second + sickDepth - 2 * depth);
        } else {
            ans = std::max(ans, l.second + sickDepth - 2 * depth);
        }
        return {true, max_depth};
    }

    int amountOfTime(TreeNode* root, int start) {
        ans = 0;
        sickVal = start;
        dfs(root, 0);
        return ans;
    }
};