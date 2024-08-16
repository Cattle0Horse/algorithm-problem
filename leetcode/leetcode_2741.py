"""
https://leetcode.cn/problems/special-permutations/description/?envType=daily-question&envId=2024-06-26
"""

from functools import cache
from typing import List


class Solution:
    def specialPerm(self, nums: List[int]) -> int:
        @cache
        def dfs(s: int, pre: int) -> int:
            if s == 0:
                return 1
            res = 0
            for j, x in enumerate(nums):
                if s >> j & 1 and (pre % x == 0 or x % pre == 0):
                    res += dfs(s ^ (1 << j), x)
            return res % 1_000_000_007

        S = (1 << len(nums)) - 1
        return sum(dfs(S ^ (1 << i), x) for i, x in enumerate(nums)) % 1_000_000_007
