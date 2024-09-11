"""
https://leetcode.cn/problems/find-a-safe-walk-through-a-grid/description/
3286. 穿越网格图的安全路径
"""

from collections import deque
from math import inf
from typing import List


DISTANCE = ((0, 1), (1, 0), (-1, 0), (0, -1))


"""
最短路，BFS
优先走0消耗的路 or dijkstra
"""


class Solution:
    def findSafeWalk(self, grid: List[List[int]], health: int) -> bool:
        m, n = len(grid), len(grid[0])
        dis = [[inf] * n for _ in range(m)]
        dis[0][0] = grid[0][0]
        q = deque([(0, 0)])
        while q:
            x, y = q.popleft()
            for dx, dy in DISTANCE:
                nx, ny = x + dx, y + dy
                if 0 <= nx < m and 0 <= ny < n and dis[nx][ny] > dis[x][y] + grid[nx][ny]:
                    dis[nx][ny] = dis[x][y] + grid[nx][ny]
                    q.append((nx, ny))
        return dis[m - 1][n - 1] < health
