/**
 * @file leetcode_1325.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/delete-leaves-with-a-given-value/description/?envType=problem-list-v2&envId=CpHNyXsu
 * @version 0.1
 * @date 2024-07-06
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <cstddef>
#ifdef OY_LOCAL
#include <vector>
#include <iostream>
using namespace std;
#endif

[[maybe_unused]] auto __init_io__ = []() {
    return std::cin.tie(nullptr)->sync_with_stdio(false);
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
    // TreeNode* removeLeafNodes(TreeNode* root, int target) {
    //     // 返回是否为叶子
    //     auto dfs = [&](auto&& self, TreeNode* cur) -> bool {
    //         if (cur->left != nullptr && self(self, cur->left) && cur->left->val == target) {
    //             cur->left = nullptr;
    //         }

    //         if (cur->right != nullptr && self(self, cur->right) && cur->right->val == target) {
    //             cur->right = nullptr;
    //         }

    //         if (cur->left == nullptr && cur->right == nullptr) {
    //             return true;
    //         }
    //         return false;
    //     };
    //     return dfs(dfs, root) && root->val == target ? nullptr : root;
    // }
    bool isLeaf(TreeNode* cur) {
        return cur->left == nullptr && cur->right == nullptr;
    }
    TreeNode* removeLeafNodes(TreeNode* root, int target) {
        if (root == nullptr) return nullptr;
        root->left = removeLeafNodes(root->left, target);
        root->right = removeLeafNodes(root->right, target);
        if (isLeaf(root) && root->val == target) return nullptr;
        return root;
    }
};