"""
https://leetcode.cn/problems/daily-temperatures/description/
739. 每日温度
"""

from typing import Callable, List


class MonotonicStack:
    """单调栈: 及时去掉无用数据，保证栈中数据的有序性
    - 由于其单调性，为二分查找提供了良好的条件(单调栈上二分)
    - 可以选择通过入栈或出栈维护单调性，关键点在当前元素与栈顶元素的关系
    - 可以常用于查找上一或下一个满足条件元素(可以一次遍历同时确定), 也可以查找第一个和最后一个满足条件的元素(通过二分或第二次逆序遍历)
    - 有时逆序遍历可能更简单
    P.S. 由于可变性非常高，因此这里只提供常用的单调栈实现
    """

    def __init__(self, start: int, end: int) -> None:
        """[start, end)"""
        self.start = start
        self.end = end

    def get_before_index(self, check: Callable[[int, int], bool], initial: int = None) -> list[int]:
        """
        查找上一个满足check的元素

        def check(i: int, j: int) -> bool: # 对于 i < j 是否满足条件
        """

        if initial is None:
            initial = self.start - 1
        res = [initial] * (self.end - self.start)
        stk = []
        for j in range(self.start, self.end):
            while stk and not check(stk[-1], j):
                stk.pop()
            if stk:
                # 当前元素遇到了第一个满足条件的元素
                res[j - self.start] = stk[-1]
            stk.append(j)
        return res

    def get_after_index(self, check: Callable[[int, int], bool], initial: int = None) -> list[int]:
        """
        查找下一个满足check的元素

        def check(i: int, j: int) -> bool: # 对于 i < j 是否满足条件
        """
        if initial is None:
            initial = self.end
        res = [initial] * (self.end - self.start)
        stk = []
        for j in range(self.start, self.end):
            # 栈内元素遇到了第一个满足条件的元素(出栈)
            while stk and check(stk[-1], j):
                res[stk.pop() - self.start] = j
            stk.append(j)
        return res


class Solution:
    def dailyTemperatures(self, temperatures: List[int]) -> List[int]:
        n = len(temperatures)
        mono_stk = MonotonicStack(0, n)
        ans = [0] * n
        for i, v in enumerate(mono_stk.get_after_index(lambda i, j: temperatures[i] < temperatures[j], -1)):
            if v != -1:
                ans[i] = v - i
        return ans
