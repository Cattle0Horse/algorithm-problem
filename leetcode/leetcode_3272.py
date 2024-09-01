'''
3272. 统计好整数的数目
https://leetcode.cn/problems/find-the-count-of-good-integers/description/
'''
from collections import Counter
from functools import cache
import math
from typing import List


nums = [str(x) for x in range(10)]


@cache
def get_huiwen(n) -> List[str]:
    """输出所有数字长度为n的回文数"""
    if n == 1:
        return nums
    m = (n - 1) // 2
    base = 10**m
    lefts = [str(x) for x in range(base, base * 10)]
    return [s + s[::-1][n % 2 :] for s in lefts]


@cache
def fac(n: int) -> int:
    return math.factorial(n)


@cache
def solve(n: int, k: int) -> int:
    vis = {tuple(sorted(x)) for x in get_huiwen(n) if int(x) % k == 0}
    # 求vis中每个数的全排列(存在重复数字，需要去重)
    # 还需要注意排除0为首的情况
    # n为字符串长度，m为非0数字个数，cx 表示字符串中 x 个个数
    # 最高位有 n-c0 种方案，其余n-1个数字随便排列有 (n-1)! 种
    # 再排除重复数字的情况即 c0! c1! c2! ... c9!
    # 所以一个字符串对答案的贡献为 (n - c0) * (n-1)! / (c0!...c9!)
    ans = 0
    for s in vis:
        c = Counter(s)
        res = (n - c["0"]) * fac(n - 1)
        for cx in c.values():
            res //= fac(cx)
        ans += res
    return ans


class Solution:
    def countGoodIntegers(self, n: int, k: int) -> int:
        return solve(n, k)