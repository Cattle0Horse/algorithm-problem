"""
https://leetcode.cn/problems/minimum-element-after-replacement-with-digit-sum/description/
3300. 替换为数位和以后的最小元素
"""

from typing import List


def digit_sum(x: int) -> int:
    if x < 0:
        return -digit_sum(-x)
    s = 0
    while x != 0:
        s += x % 10
        x //= 10
    return s


class Solution:
    def minElement(self, nums: List[int]) -> int:
        return min(map(digit_sum, nums))
