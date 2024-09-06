from typing import List


"""
dp[i][j]: 以nums[i]结尾 满足相邻不等下标的个数不超过j 的好序列最长长度
需要快速求出i之前 等于nums[i] 以及 不等于nums[i] 的好序列最长长度
"""


class Solution:
    def maximumLength(self, nums: List[int], k: int) -> int:
        n = len(nums)
        dp = [[1] * (k + 1) for _ in range(n)]
        for i in range(1, n):
            for j in range(k + 1):
                for index, last in enumerate(nums[:i]):
                    if last == nums[i]:
                        dp[i][j] = max(dp[i][j], dp[index][j] + 1)
                    elif j - 1 >= 0:
                        dp[i][j] = max(dp[i][j], dp[index][j - 1] + 1)
        return max(map(max, dp))
