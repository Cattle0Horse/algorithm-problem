"""
https://leetcode.cn/problems/maximum-rows-covered-by-columns/description/
2397. 被列覆盖的最多行数
"""

from typing import List
from typing import Generator


def next_k_subset(s: int) -> int:
    """下一个k子集(用于k_subset方法)
    https://leetcode.cn/problems/maximum-rows-covered-by-columns
    Gosper's Hack : https://zhuanlan.zhihu.com/p/360512296
    https://programmingforinsomniacs.blogspot.com/2018/03/gospers-hack-explained.html
    """
    lb = s & -s
    r = s + lb
    return ((r ^ s) // lb >> 2) | r


def k_subset(S: int, k: int) -> Generator[int, None, None]:
    """生成子集(每一个集合都有k个元素)"""
    s = (1 << k) - 1
    while s <= S:
        yield s
        s = next_k_subset(s)


class Solution:
    def maximumRows(self, matrix: List[List[int]], numSelect: int) -> int:
        m, n = len(matrix), len(matrix[0])
        mask = [0] * m
        for i, row in enumerate(matrix):
            for j, val in enumerate(row):
                mask[i] |= val << j
        count_if = lambda s: sum(1 for v in mask if v & s == v)
        return max(map(count_if, k_subset(1 << n, numSelect)))
