"""
https://leetcode.cn/problems/find-the-maximum-sequence-value-of-array/description/
3287. 求出数组中最大序列值
"""

from typing import List

"""
动态规划的两种递推思路:
- 查表  y 由 x 推出
- 刷表: x 推出 y

前缀部分选k个数的或值 ^ 后缀选k个数的或值 最大
如何求出任意k个数的或值?
"""


def get_prefix(nums: List[int], k: int) -> List[set]:
    ans = [None] * len(nums)
    dp = [set() for _ in range(k + 1)]
    dp[0].add(0)
    for i, num in enumerate(nums):
        for j in range(k - 1, -1, -1):
            for v in dp[j]:
                dp[j + 1].add(num | v)
        ans[i] = dp[k].copy()
    return ans


class Solution:
    def maxValue(self, nums: List[int], k: int) -> int:
        prefix = get_prefix(nums, k)
        suffix = get_prefix(nums[::-1], k)[::-1]
        n = len(nums)
        ans = 0
        # 左边和右边都至少有k个数
        for i in range(k - 1, n - k):
            # 前i个数
            for x in prefix[i]:
                # 后n-i个数
                for y in suffix[i + 1]:
                    ans = max(ans, x ^ y)
        return ans


sol = Solution()
print(sol.maxValue([2, 6, 7], 1) == 5)
print(sol.maxValue([4, 2, 5, 6, 7], 2) == 2)
print(sol.maxValue([1, 89, 11, 90], 2) == 2)
print(sol.maxValue([3, 107, 124, 11, 18, 64], 2) == 112)
