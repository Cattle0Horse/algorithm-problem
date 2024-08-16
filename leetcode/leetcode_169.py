# https://leetcode.cn/problems/majority-element/description/

from math import inf
from typing import List


class Solution:
    def majorityElement(self, nums: List[int]) -> int:
        n = len(nums)
        winner, hp = inf, 0
        for num in nums:
            if hp == 0:
                winner = num
                hp = 1
            else:
                hp += 1 if winner == num else -1
        if nums.count(winner) > n // 2:
            return winner
        return inf  # none
