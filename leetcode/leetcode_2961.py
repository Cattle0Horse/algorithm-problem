# https://leetcode.cn/problems/double-modular-exponentiation/?envType=daily-question&envId=2024-07-30
from typing import List


"""
(a^b % 10) ^ c % m = (a % 10 % m) ^ b % 10 % m
"""


class Solution:
    def getGoodIndices(self, variables: List[List[int]], target: int) -> List[int]:
        return [i for i, (a, b, c, m) in enumerate(variables) if pow(pow(a, b, 10), c, m) == target]
