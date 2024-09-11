"""
https://leetcode.cn/problems/reach-end-of-array-with-max-score/
3282. 到达数组末尾的最大得分
"""

from typing import List


class Solution:
    def findMaximumScore(self, nums: List[int]) -> int:
        """
        前缀最大值的和(除最后一项外)
        """
        ans = 0
        mx = 0
        for x in nums:
            ans += mx
            mx = max(mx, x)
        return ans
