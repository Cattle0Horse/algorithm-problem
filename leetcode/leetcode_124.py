"""
https://leetcode.cn/problems/binary-tree-maximum-path-sum/description
124. 二叉树中的最大路径和
"""

from math import inf
from typing import Optional


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def maxPathSum(self, root: Optional[TreeNode]) -> int:
        assert root
        ans = -inf

        # 返回以当前节点的向下的最大值链
        def dfs(cur: Optional[TreeNode]) -> int:
            if cur is None:
                return 0
            left = dfs(cur.left)
            right = dfs(cur.right)
            nonlocal ans
            ans = max(ans, left + right + cur.val)
            return max(max(left, right) + cur.val, 0)

        dfs(root)
        return ans
