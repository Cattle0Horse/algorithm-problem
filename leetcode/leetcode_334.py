# https://leetcode.cn/problems/increasing-triplet-subsequence/description/
from ast import List


class Solution:
    def increasingTriplet(self, nums: List[int]) -> bool:
        # 前缀最小值, 后缀最大值
        n = len(nums)
        mn, mx = [nums[0]] * n, [nums[-1]] * n
        for i in range(1, n):
            mn[i] = min(mn[i-1], nums[i])
        for i in range(n-2, -1, -1):
            mx[i] = max(mx[i+1], nums[i])
        for j in range(1, n-1):
            if mn[j-1] < nums[j] < mx[j+1]:
                return True
        return False
