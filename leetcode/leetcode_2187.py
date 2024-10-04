"""
https://leetcode.cn/problems/minimum-time-to-complete-trips/?envType=daily-question&envId=2024-10-05
2187. 完成旅途的最少时间
"""

from typing import List


class Solution:
    def minimumTime(self, time: List[int], totalTrips: int) -> int:
        def check(all_time: int) -> bool:
            return sum(all_time // t for t in time) >= totalTrips

        l, r = 0, min(time) * totalTrips + 1
        while l + 1 < r:
            mid = (l + r) >> 1
            if check(mid):
                r = mid
            else:
                l = mid
        return r
