"""
3276. 选择矩阵中单元格的最大得分
https://leetcode.cn/problems/select-cells-in-grid-with-maximum-score/description/
"""

from collections import defaultdict
from functools import cache
from typing import List


class Solution:
    def maxScore(self, grid: List[List[int]]) -> int:
        mx = max(map(max, grid))
        pos = [[] for _ in range(mx + 1)]
        for i, row in enumerate(grid):
            for x in set(row):
                pos[x].append(i)

        # 枚举值域dp，限制选择行
        # val 目前枚举选择的数值，chosen 已经选择的行
        @cache
        def dfs(val: int, chosen: int) -> int:
            if val > mx:
                return 0
            # 不选择当前值
            res = dfs(val + 1, chosen)
            # 枚举选择当前值的行
            for i in pos[val]:
                if chosen & (1 << i):
                    continue
                res = max(res, val + dfs(val + 1, chosen | (1 << i)))
            return res

        ans = dfs(0, 0)
        dfs.cache_clear()
        return ans


class Solution:
    def maxScore(self, grid: List[List[int]]) -> int:
        pos = defaultdict(list)
        for i, row in enumerate(grid):
            for x in set(row):
                pos[x].append(i)

        n = len(grid)
        m = 1 << n
        dp = [0] * m
        for val, row in pos.items():
            for s in range(m):
                for i in row:
                    if s & (1 << i):
                        continue
                    dp[s] = max(dp[s], dp[s | (1 << i)] + val)
        return dp[0]
