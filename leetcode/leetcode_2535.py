"""
https://leetcode.cn/problems/difference-between-element-sum-and-digit-sum-of-an-array/?envType=daily-question&envId=2024-09-26
2535. 数组元素和与数字和的绝对差
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
    def differenceOfSum(self, nums: List[int]) -> int:
        return sum(nums) - sum(map(digit_sum, nums))
