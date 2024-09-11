"""
https://leetcode.cn/problems/maximum-multiplication-score/description/
3290. 最高乘法得分
"""

import math
from typing import List


class Solution:
    def maxScore(self, a: List[int], b: List[int]) -> int:
        n = len(b)
        dp = [[0] * 5 for _ in range(n + 1)]
        for i in range(1, 5):
            dp[0][i] = -math.inf
        for i in range(1, n + 1):
            for j in range(1, 5):
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1] + a[j - 1] * b[i - 1])
        return dp[-1][-1]


class Solution:
    def maxScore(self, a: List[int], b: List[int]) -> int:
        dp = [0] + [-math.inf] * 4
        for x in b:
            for j in range(4, 0, -1):
                dp[j] = max(dp[j], dp[j - 1] + a[j - 1] * x)
        return dp[-1]
