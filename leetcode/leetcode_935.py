"""
https://leetcode.cn/problems/knight-dialer/description/?envType=daily-question&envId=2024-12-10
935. 骑士拨号器
"""

from functools import cache


NEXT = ((4, 6), (6, 8), (7, 9), (4, 8), (0, 3, 9), (), (0, 1, 7), (2, 6), (1, 3), (2, 4))
MOD = 10**9 + 7


@cache
def dfs(n: int, number: int) -> int:
    if n == 0:
        return 1
    return sum(dfs(n - 1, next_number) for next_number in NEXT[number]) % MOD


class Solution:
    def knightDialer(self, n: int) -> int:
        if n == 1:
            return 10
        return sum(dfs(n - 1, number) for number in range(10)) % MOD


"""
DIRECTIONS = ((1, 2), (1, -2), (-1, 2), (-1, -2), (2, 1), (2, -1), (-2, 1), (-2, -1))
GRID = ((1, 2, 3), (4, 5, 6), (7, 8, 9), (-1, 0, -1))
MOD = 10**9 + 7


@cache
def check(x: int, y: int) -> bool:
    return 0 <= x < len(GRID) and 0 <= y < len(GRID[0]) and GRID[x][y] != -1


@cache
def dfs(n: int, x: int, y: int) -> int:
    if n == 0:
        return 1
    ans = 0
    for dx, dy in DIRECTIONS:
        nx, ny = x + dx, y + dy
        if check(nx, ny):
            ans = (ans + dfs(n - 1, nx, ny)) % MOD
    return ans


class Solution:
    def knightDialer(self, n: int) -> int:
        if n == 1:
            return 10
        return sum(dfs(n - 1, x, y) for x in range(len(GRID)) for y in range(len(GRID[0])) if check(x, y)) % MOD
"""
