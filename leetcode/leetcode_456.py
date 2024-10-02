"""
https://leetcode.cn/problems/find-the-number-of-subarrays-where-boundary-elements-are-maximum/
3113. 边界元素是最大值的子数组数目
"""

from math import inf
from typing import List


class Solution:
    def numberOfSubarrays(self, nums: List[int]) -> int:
        ans = len(nums)
        stk = [[inf, 0]]
        for x in nums:
            while x > stk[-1][0]:
                stk.pop()
            top = stk[-1]
            if x == top[0]:
                ans += top[1]
                top[1] += 1
            else:
                stk.append([x, 1])
        return ans
