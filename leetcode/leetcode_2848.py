"""
https://leetcode.cn/problems/points-that-intersect-with-cars/description/
2848. 与车相交的点
"""

from typing import List


def merge_intervals(intervals: list | tuple) -> list[int]:
    arr = sorted(intervals)
    ans, i, n = [], 0, len(arr)
    while i < n:
        l, r = arr[i][0], arr[i][1]
        while i < n and arr[i][0] <= r:
            r = max(r, arr[i][1])
            i += 1
        ans.append([l, r])
    return ans


class Solution:
    def numberOfPoints(self, nums: List[List[int]]) -> int:
        print(merge_intervals(nums))
        return sum(r - l + 1 for l, r in merge_intervals(nums))
