"""
https://leetcode.cn/problems/find-the-town-judge/?envType=daily-question&envId=2024-09-22
997. 找到小镇的法官
"""

from typing import List


class Solution:
    def findJudge(self, n: int, trust: List[List[int]]) -> int:
        adj = [[] for _ in range(n)]
        for a, b in trust:
            adj[a - 1].append(b - 1)
        ans = []
        for i in range(n):
            if not adj[i] and sum(1 for row in adj if i in row) == n - 1:
                if ans:
                    return -1
                ans.append(i + 1)
        return ans[0] if ans else -1


sol = Solution()
print(sol.findJudge(2, [[1, 2]]))
