"""
https://leetcode.cn/problems/maximum-width-ramp/description/
962. 最大宽度坡
"""

from typing import List


class Solution:
    """
    对于下标 k < i < j, 若 A[k] < A[i], 则i是无用的
    若从左向右遍历，则栈内元素应该是降序的(按列表来看)
        对于当前元素，若栈内有比当前元素小的元素，则当前元素是无用的

    o
        o               o
            o       o       o
                o
    """

    def maxWidthRamp(self, nums: List[int]) -> int:
        ans = 0
        stk = []
        for j, x in enumerate(nums):
            if not stk or nums[stk[-1]] > x:
                stk.append(j)
            if nums[stk[-1]] <= x:
                # 在栈内二分查找第一个<=当前元素 的下标
                l, r = -1, len(stk)
                while l + 1 < r:
                    m = (l + r) >> 1
                    if nums[stk[m]] <= x:
                        r = m
                    else:
                        l = m
                ans = max(ans, j - stk[r])
        return ans