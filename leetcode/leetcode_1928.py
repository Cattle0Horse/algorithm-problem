"""
https://leetcode.cn/problems/minimum-cost-to-reach-destination-in-time/?envType=daily-question&envId=2024-10-03
1928. 规定时间内到达终点的最小花费
"""

import math
from typing import List


class Solution:
    def minCost(self, maxTime: int, edges: List[List[int]], passingFees: List[int]) -> int:
        n = len(passingFees)
        # dp[t][i] : 在花费不超过t的时间下，0到i的最小消费
        dp = [[math.inf] * n for _ in range(maxTime + 1)]
        dp[0][0] = passingFees[0]

        for t in range(0, maxTime):
            for u, v, w in edges:
                time = t + w
                if time <= maxTime:
                    # 双向
                    dp[time][u] = min(dp[time][u], dp[t][v] + passingFees[u])
                    dp[time][v] = min(dp[time][v], dp[t][u] + passingFees[v])

        res = min(fees[n - 1] for fees in dp)
        return res if res != math.inf else -1
