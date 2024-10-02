"""
https://leetcode.cn/problems/maximize-the-total-height-of-unique-towers/
3301. 高度互不相同的最大塔高和
"""

from typing import List


class Solution:
    def maximumTotalSum(self, maximumHeight: List[int]) -> int:
        maximumHeight.sort(reverse=True)
        n = len(maximumHeight)
        for i in range(1, n):
            if maximumHeight[i - 1] == maximumHeight[i]:
                maximumHeight[i] -= 1
                if maximumHeight[i] == 0:
                    return -1
        return maximumHeight[0]
