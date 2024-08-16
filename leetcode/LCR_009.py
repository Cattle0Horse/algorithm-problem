# https://leetcode.cn/problems/ZVAVXX/
from typing import List


class Solution:
    def numSubarrayProductLessThanK(self, nums: List[int], k: int) -> int:
        if k <= 1:
            return 0
        mul, ans = 1, 0
        l = 0
        for r, x in enumerate(nums):
            mul *= x
            while mul >= k:
                mul //= nums[l]
                l += 1
            # [l, r]
            ans += r - l + 1

        return ans
