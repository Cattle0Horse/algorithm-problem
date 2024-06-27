# https://leetcode.cn/problems/guess-number-higher-or-lower-ii/
'''
使得 从根节点到达叶子节点父节点的路径的最大值 最小
'''
from functools import cache


@cache
def dfs(l: int, r: int) -> int:
    if l == r:
        return 0
    if l+1 == r:
        return l
    return min(root + max(dfs(l, root-1), dfs(root+1, r)) for root in range(l+1, r))


class Solution:
    def getMoneyAmount(self, n: int) -> int:
        return dfs(1, n)
