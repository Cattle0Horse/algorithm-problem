/**
 * @file leetcode_437.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/path-sum-iii/?envType=problem-list-v2&envId=lzLsR4CI
 * @version 0.1
 * @date 2024-06-05
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <functional>
#include <unordered_map>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(): val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right): val(x), left(left), right(right) {}
};

class Solution {
public:
    int pathSum(TreeNode* root, int targetSum) {
        if (root == nullptr) return 0;
        int ans{0};
        std::unordered_map<long long, int> cnt{{0, 1}};
        std::function<void(TreeNode*, long long)> dfs = [&](TreeNode* cur, long long sum) {
            if (cur == nullptr) return;
            sum += cur->val;
            if (cnt.contains(sum - targetSum)) ans += cnt[sum - targetSum];
            ++cnt[sum];
            dfs(cur->left, sum);
            dfs(cur->right, sum);
            --cnt[sum];
        };
        dfs(root, 0);
        return ans;
    }
};