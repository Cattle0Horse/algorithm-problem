"""
https://leetcode.cn/problems/maximize-score-of-numbers-in-ranges/
3281. 范围内整数的最大得分
"""

from typing import List


class Solution:
    def maxPossibleScore(self, start: List[int], d: int) -> int:
        start.sort()

        def check(score: int) -> bool:
            prev = -(10**10)
            for left in start:
                right = left + d
                if prev + score > right:
                    return False
                prev = max(left, prev + score)
            return True

        l, r = -1, 10**10
        while l + 1 < r:
            m = (l + r) >> 1
            if check(m):
                l = m
            else:
                r = m
        return l
