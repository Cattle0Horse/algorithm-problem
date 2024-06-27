/**
 * @file leetcode_979.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/distribute-coins-in-binary-tree/description/
 * @version 0.1
 * @date 2024-06-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <cstdlib>
#ifdef OY_LOCAL
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;
#endif

[[maybe_unused]] auto _ = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();

#ifdef OY_LOCAL
// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode* next;
    ListNode(): val(0), next(nullptr) {}
    ListNode(int x): val(x), next(nullptr) {}
    ListNode(int x, ListNode* next): val(x), next(next) {}
};
// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(): val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right): val(x), left(left), right(right) {}
};
#endif

class Solution {
public:
    // 从叶子向上归, 返回需要的硬币个数x, 每向上一层,代价就多x
    int distributeCoins(TreeNode* root) {
        int ans{0};
        // 返回子节点向当前节点借(或者还)的硬币数量
        auto dfs = [&](auto&& self, TreeNode* cur) -> int {
            int cur_val = cur->val;
            if (cur->left != nullptr) cur_val += self(self, cur->left);
            if (cur->right != nullptr) cur_val += self(self, cur->right);
            ans += std::abs(cur_val - 1);
            return cur_val - 1;
        };
        dfs(dfs, root);
        return ans;
    }
};