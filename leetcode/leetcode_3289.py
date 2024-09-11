"""
https://leetcode.cn/problems/the-two-sneaky-numbers-of-digitville/description/
3289. 数字小镇中的捣蛋鬼
"""

from collections import Counter
from typing import List


class Solution:
    def getSneakyNumbers(self, nums: List[int]) -> List[int]:
        cnt = Counter(nums)
        return [k for k, v in cnt.items() if v == 2]
