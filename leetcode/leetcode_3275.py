"""
3275. 第 K 近障碍物查询
https://leetcode.cn/problems/k-th-nearest-obstacle-queries/description/
"""

import heapq
from typing import List
from sortedcontainers import SortedList


class Solution:
    '''
    SortedList 是B+树实现的
    '''
    def resultsArray(self, queries: List[List[int]], k: int) -> List[int]:
        arr = SortedList()
        ans = [-1] * len(queries)
        for i, q in enumerate(queries):
            arr.add(abs(q[0]) + abs(q[1]))
            if len(arr) >= k:
                ans[i] = arr[k - 1]
            else:
                ans[i] = -1
        return ans


class Solution:
    '''
    堆
    '''
    def resultsArray(self, queries: List[List[int]], k: int) -> List[int]:
        arr = []
        ans = [-1] * len(queries)
        for i, q in enumerate(queries):
            heapq.heappush(arr, -(abs(q[0]) + abs(q[1])))
            if len(arr) > k:
                heapq.heappop(arr)
            if len(arr) == k:
                ans[i] = -arr[0]
            else:
                ans[i] = -1
        return ans
