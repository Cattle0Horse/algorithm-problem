"""
https://leetcode.cn/problems/final-prices-with-a-special-discount-in-a-shop/submissions/526412450/
1475. 商品折扣后的最终价格
"""

from typing import Callable, Generator, List


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

    def before_index_generator(self, check: Callable[[int, int], bool]) -> Generator[int, None, list[int]]:
        """
        查找上一个满足check的元素

        def check(i: int, j: int) -> bool: # 对于 i < j 是否满足条件
        """
        stk = []
        for j in range(self.start, self.end):
            while stk and not check(stk[-1], j):
                stk.pop()
            if stk:
                # 当前元素遇到了第一个满足条件的元素
                yield stk[-1], j
            stk.append(j)
        return stk

    def after_index_generator(self, check: Callable[[int, int], bool]) -> Generator[int, None, list[int]]:
        """
        查找下一个满足check的元素

        def check(i: int, j: int) -> bool: # 对于 i < j 是否满足条件
        """
        stk = []
        for j in range(self.start, self.end):
            # 栈内元素遇到了第一个满足条件的元素(出栈)
            while stk and check(stk[-1], j):
                yield stk.pop(), j
            stk.append(j)
        return stk

    def before_index(self, check: Callable[[int, int], bool], initial: int = None) -> list[int]:
        """
        查找上一个满足check的元素

        def check(i: int, j: int) -> bool: # 对于 i < j 是否满足条件
        """
        ans = [initial] * (self.end - self.start)
        for i, j in self.before_index_generator(check):
            ans[i - self.start] = j - self.start
        return ans

    def after_index(self, check: Callable[[int, int], bool], initial: int = None) -> list[int]:
        """
        查找下一个满足check的元素

        def check(i: int, j: int) -> bool: # 对于 i < j 是否满足条件
        """
        ans = [initial] * (self.end - self.start)
        for i, j in self.after_index_generator(check):
            ans[i - self.start] = j - self.start
        return ans


class Solution:
    def finalPrices(self, prices: List[int]) -> List[int]:
        ans = prices.copy()
        for i, j in MonotonicStack(0, len(prices)).after_index_generator(lambda i, j: prices[i] >= prices[j]):
            ans[i] -= prices[j]
        return ans
