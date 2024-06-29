# https://leetcode.cn/problems/car-fleet/

from typing import List


class Solution:
    def carFleet(self, target: int, position: List[int], speed: List[int]) -> int:
        
        n = len(position)
        index = position.index(max(position))

        # 判断有多少量车能够index在到达终点之前追上index

        # d1 / s1 > d2 / s2
        def compare(i: int, j: int) -> bool:
            return (target-position[i])*speed[j] >= (target-position[j])*speed[i]
        
        return [compare(i, index) for i in range(n)].count(True)

                