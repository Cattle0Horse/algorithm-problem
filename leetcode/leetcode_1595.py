# https://leetcode.cn/problems/minimum-cost-to-connect-two-groups-of-points/

from cmath import inf
from functools import cache
from typing import List


class Solution:
    def connectTwoGroups(self, cost: List[List[int]]) -> int:
        n, m = len(cost), len(cost[0])
        S = (1 << m) - 1
        # i号节点连接状态为s所需要的成本
        linkCost = [[0]*(S+1) for _ in range(n)]
        for i in range(n):
            for s in range(1, S+1):
                linkCost[i][s] = \
                    linkCost[i][s & (s-1)] + cost[i][(s&-s).bit_length()-1]
        
        @cache
        def dfs(i: int, s: int) -> int:
            if s == 0:
                return inf
            # 最后一组直接连接剩余的全部
            if i == n-1:
                return linkCost[n-1][s]
            ans = inf
            sub = s
            while sub != 0:
                ans = min(ans, dfs(i+1, s ^ sub)+linkCost[i][sub])
                sub = (sub-1) & s
            return ans

        return dfs(0, S)


print(Solution().connectTwoGroups([[2,5,1],[3,4,7],[8,1,2],[6,2,4],[3,8,8]]))
