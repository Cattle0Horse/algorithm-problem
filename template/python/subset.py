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


def subset(S: int) -> Generator[int, None, None]:
    """生成子集(含空集)"""
    s = 0
    while True:
        yield s
        s = (s - 1) & S
        if s == S:
            break


def nonempty_subset(S: int) -> Generator[int, None, None]:
    """生成非空子集"""
    s = S
    while s != 0:
        yield s
        s = (s - 1) & S


# 折半搜索
# https://leetcode.cn/problems/partition-array-into-two-arrays-to-minimize-sum-difference/description/
# https://leetcode.cn/problems/closest-subsequence-sum/description/


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
