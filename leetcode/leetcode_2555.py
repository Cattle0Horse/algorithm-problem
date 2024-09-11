'''
2555. 两个线段获得的最多奖品
https://leetcode.cn/problems/maximize-win-from-two-segments/description/?envType=daily-question&envId=2024-09-11
'''
from itertools import accumulate
from typing import List

"""
贪心思想:两线段不相交为最优
以某一点作为线段左端点
第一条线段限制右端点不超过的位置，第二条线段限制左端点不超过的位置
前缀最优线段与后缀最优线段
"""


class Solution:
    def maximizeWin(self, positions: List[int], k: int) -> int:
        n = len(positions)

        pre = [0] * n
        i, j = 0, 0
        while j < n:
            while i < j and positions[j] - positions[i] > k:
                i += 1
            pre[j] = j - i + 1
            j += 1
        pre = list(accumulate(pre, func=max))

        suf = [0] * n
        i, j = n - 1, n - 1
        while 0 <= j:
            while j < i and positions[i] - positions[j] > k:
                i -= 1
            suf[j] = i - j + 1
            j -= 1
        suf = list(accumulate(suf[::-1], func=max))[::-1]

        return max(pre[i] + suf[i + 1] for i in range(n - 1))
