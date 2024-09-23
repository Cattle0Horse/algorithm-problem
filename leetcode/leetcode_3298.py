"""
https://leetcode.cn/problems/count-substrings-that-can-be-rearranged-to-contain-a-string-ii/description/
3298. 统计重新排列后包含另一个字符串的子字符串数目 II
双指针
- 枚举左端点，维护右端点
- 枚举右端点，维护左端点
"""

from collections import Counter


class TargetNumber:
    """
    用于判断目标字符串是否可以由给定的字符重新排列组成
    即只需拥有足够的目标数量
    """

    def __init__(self, target: str | list) -> None:
        self.need = Counter(target)
        self.less = len(self.need)

    def acquire(self, v, cnt: int = 1) -> None:
        """获得字符，减少需要的个数"""
        before = self.need[v]
        self.need[v] -= cnt
        if before > 0 and self.need[v] <= 0:
            self.less -= 1

    def release(self, v, cnt: int = 1) -> None:
        """释放字符，增加需要的个数(请确保释放的是通过acquire方法获得的字符)"""
        before = self.need[v]
        self.need[v] += cnt
        if before <= 0 and self.need[v] > 0:
            self.less += 1

    def enough(self) -> bool:
        """判断需要的字符是否足够"""
        return self.less == 0

    def __repr__(self) -> str:
        return f"need = {self.need}, less = {self.less}"


class SlideWindow:
    def __init__(self, start: int, end: int) -> None:
        self.start = start
        self.end = end

    def slide_base_left(self, check, acquire, release):
        """
        滑动窗口
        返回以left为起点的最长的满足check条件的区间[left, right]及其数据
        表示区间[left, right)均不满足check, [right, end)均满足check

        check(left: int, right: int)-> bool: # 判断[left, right]窗口是否满足条件
        acquire(right: int) -> None: # 获取对应下标的数据
        release(left: int) -> None: # 释放对应下标的数据
        """
        right = self.start
        for left in range(self.start, self.end):
            # 向右扩展，直到不满足check
            while right < self.end and check(left, right - 1):
                acquire(right)
                right += 1
            yield left, right - 1
            release(left)

    def slide_base_right(self, check, acquire, release):
        """
        滑动窗口
        返回以right为终点的最长的满足check条件的区间[left, right]及其数据
        表示区间[start, left)均不满足check, [left, right]均满足check

        check(left: int, right: int)-> bool: # 判断[left, right]窗口是否满足条件
        acquire(right: int) -> None: # 获取对应下标的数据
        release(left: int) -> None: # 释放对应下标的数据
        """
        left = self.start
        for right in range(self.start, self.end):
            acquire(right)
            # 左边收缩，直到满足check
            while left <= right and check(left, right):
                release(left)
                left += 1
            yield left, right

    def slide_fixed_length(self, acquire, release, length: int):
        """
        固定长度滑动窗口
        返回每一个长度为length的区间
        acquire(right: int) -> None: # 获取对应下标的数据
        release(left: int) -> None: # 释放对应下标的数据
        """
        left = self.start
        for right in range(self.start, self.end):
            acquire(right)
            if right - left + 1 == length:
                yield left, right
                release(left)
                left += 1


class Solution:
    """
    如果一个子字符串满足字符集合是word2的超集,那么左右任意扩展都是答案
    以当前下标为起点的字符串对答案的贡献
    """

    def validSubstringCount(self, word1: str, word2: str) -> int:
        need = TargetNumber(word2)
        window = SlideWindow(0, len(word1))

        def check(left: int, right: int) -> bool:
            return need.enough()

        def acquire(right: int) -> None:
            need.acquire(word1[right])

        def release(left: int) -> None:
            need.release(word1[left])

        ans = 0
        for left, right in window.slide_base_right(check, acquire, release):
            ans += left
        return ans
