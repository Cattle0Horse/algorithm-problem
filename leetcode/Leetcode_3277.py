"""
3277. 查询子数组最大异或值
https://leetcode.cn/problems/maximum-xor-score-subarray-queries/description/
"""

from typing import List


class Solution:
    """
    区间[l, r]的异或值为 dp[l, r]，则：
    dp[l, r] = dp[l+1, r] ^ dp[l, r-1]
    区间[l, r]的所有子数组的最大异或值为 ans[l, r]，则
    ans[l, r] = max(dp[l, r], ans[l+1, r], ans[l, r-1])

    观察abc三个数与abcd四个数的关系(即[0, 2]与[0,3]的关系)
    a,b,c         a,b,c,d
    a^b b^c       a^b b^c c^d
    a^b^b^c       a^b^b^c   b^c^c^d
    dp[0,2]       dp[0,2]  dp[1,3]
    可见: dp[0,3] =dp[0,2] ^ dp[1,3]
    因此递推式: dp[i][j]=dp[i][j-1] ^ dp[i+1][j]

    对于询问: [i, j] 最大异或值 dp[i][j] = max(dp[i][j], dp[i+1][j], dp[i][j-1])
    """

    def maximumSubarrayXor(self, nums: List[int], queries: List[List[int]]) -> List[int]:
        n, m = len(nums), len(queries)
        dp = [[0] * n for _ in range(n)]
        ans = [[0] * n for _ in range(n)]
        for i in range(n - 1, -1, -1):
            ans[i][i] = dp[i][i] = nums[i]
            for j in range(i + 1, n):
                dp[i][j] = dp[i][j - 1] ^ dp[i + 1][j]
                ans[i][j] = max(dp[i][j], ans[i][j - 1], ans[i + 1][j])
        return [ans[l][r] for l, r in queries]
