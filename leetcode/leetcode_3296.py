"""
https://leetcode.cn/problems/minimum-number-of-seconds-to-make-mountain-height-zero/description/
3296. 移山所需的最少秒数
"""

"""
使插入后的数组最大值最小
"""


import heapq
from typing import List


class Solution:
    def minNumberOfSeconds(self, mountainHeight: int, workerTimes: List[int]) -> int:
        cnt = [1] * len(workerTimes)
        # 记录算上下一次消耗时间的总耗时
        arr = [(x, i) for i, x in enumerate(workerTimes)]
        heapq.heapify(arr)
        for _ in range(mountainHeight):
            x, i = heapq.heappop(arr)
            cnt[i] += 1
            heapq.heappush(arr, (x + workerTimes[i] * cnt[i], i))
        return max(x - workerTimes[i] * cnt[i] for x, i in arr)
