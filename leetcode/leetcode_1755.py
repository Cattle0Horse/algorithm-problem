"""
https://leetcode.cn/problems/closest-subsequence-sum/description/
1755. 最接近目标值的子序列和
折半搜索
"""

import functools
import math
import operator
from typing import List


def tail_zero_count(x: int) -> int:
    """计算x的尾部0的个数"""
    s = 0
    while x & 1 == 0:
        s += 1
        x >>= 1
    return s


def subsequence_list(arr: list, op, initial) -> list:
    """获得arr的子集运算结果表"""
    n = len(arr)
    S = 1 << n
    res = [initial] * S
    for s in range(1, S):
        res[s] = op(res[s & (s - 1)], arr[tail_zero_count(s)])
    return res


def subsequence_count_list(arr: list, op, initial) -> list[list]:
    """获得arr的子集运算结果表并按二进制1的个数分组"""
    n = len(arr)
    res = [[] for _ in range(n + 1)]
    res[0].append(initial)
    S = 1 << n
    temp = [initial] * S
    for s in range(1, S):
        temp[s] = op(temp[s & (s - 1)], arr[tail_zero_count(s)])
        res[s.bit_count()].append(temp[s])
    return res


class Solution:
    def minAbsDifference(self, nums: List[int], goal: int) -> int:
        n = len(nums)
        left_size = n >> 1
        sub_list = functools.partial(subsequence_list, op=operator.add, initial=0)
        left_sum = sub_list(nums[:left_size])
        right_sum = sub_list(nums[left_size:])
        left_sum.sort()
        right_sum.sort()
        ans = math.inf
        l, r = 0, len(right_sum) - 1
        while l < len(left_sum) and r >= 0:
            s = left_sum[l] + right_sum[r]
            ans = min(ans, abs(goal - s))
            if s > goal:
                r -= 1
            else:
                l += 1
        return ans
