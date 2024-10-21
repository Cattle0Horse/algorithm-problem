"""
https://leetcode.cn/problems/minimum-division-operations-to-make-array-non-decreasing/description/
3326. 使数组非递减的最少除法操作次数
"""

from typing import List


def sieve(n: int) -> list[int]:
    """埃氏筛[0, n], 返回最小质因子列表"""
    if n == 0:
        return [-1]
    LPM = [i for i in range(n + 1)]
    LPM[0] = LPM[1] = -1
    for i in range(2, int(n**0.5) + 1):
        if LPM[i] == i:
            for j in range(i * i, n + 1, i):
                if LPM[j] == j:
                    LPM[j] = i
    return LPM


LPF = sieve(10**6 + 5)


class Solution:
    def minOperations(self, nums: List[int]) -> int:
        ans = 0
        for i in range(len(nums) - 2, -1, -1):
            if nums[i] > nums[i + 1]:
                nums[i] = LPF[nums[i]]
                if nums[i] > nums[i + 1]:
                    return -1
                ans += 1
        return ans
