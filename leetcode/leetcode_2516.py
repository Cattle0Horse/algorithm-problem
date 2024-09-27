"""
https://leetcode.cn/problems/take-k-of-each-character-from-left-and-right/description/?envType=daily-question&envId=2024-09-27
2516. 每种字符至少取 K 个
"""

from collections import Counter


class SlidingWindow:
    """滑动窗口"""

    def __init__(self, start: int, end: int) -> None:
        self.start = start
        self.end = end

    def slide_base_left(self, check, acquire, release):
        """
        返回以left为起点的最长的满足check条件的区间[left, right]
        表示区间[left, right]均满足check, (right, end)均不满足check
        要求: 若区间[left, right]不满足check，则[left, right+1]也不满足check

        def check(left: int, right: int)-> bool: # 判断[left, right]窗口是否满足条件
        def acquire(right: int) -> None: # 获取对应下标的数据
        def release(left: int) -> None: # 释放对应下标的数据
        """
        right = self.start
        for left in range(self.start, self.end):
            # 向右扩展
            while right < self.end and check(left, right - 1):
                acquire(right)
                right += 1
            yield left, right - 1
            release(left)

    def slide_base_right(self, check, acquire, release):
        """
        返回以right为终点的最长的满足check条件的区间[left, right]
        表示区间[start, left)均不满足check, [left, right]均满足check
        要求: 若区间[left, right]满足check，则[left+1, right]也满足check

        def check(left: int, right: int)-> bool: # 判断[left, right]窗口是否满足条件
        def acquire(right: int) -> None: # 获取对应下标的数据
        def release(left: int) -> None: # 释放对应下标的数据
        """
        left = self.start
        for right in range(self.start, self.end):
            acquire(right)
            # 左边收缩
            while left <= right and not check(left, right):
                release(left)
                left += 1
            yield left, right

    def slide_fixed_length(self, acquire, release, length: int):
        """
        固定长度滑动窗口
        返回每一个长度为length的区间

        def acquire(right: int) -> None: # 获取对应下标的数据
        def release(left: int) -> None: # 释放对应下标的数据
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
    若需要取走每种字符至少k个 <=> 剩余字符是 (a-k)*'a', (b-k)*'b', (c-k)*'c' 的子串，即个数小于等于
    要使取走的字符总个数少 <=> 剩余字符尽可能多, 但是不能超过上面的上限
    滑动窗口
    """

    def takeCharacters(self, s: str, k: int) -> int:
        # 不能使limit任意一个字符小于0
        limit = Counter(s)
        for x in "abc":
            limit[x] -= k
            if limit[x] < 0:
                return -1

        def check(left: int, right: int) -> bool:
            return limit[s[right]] >= 0

        def acquire(right: int) -> None:  # 获取对应下标的数据
            limit[s[right]] -= 1

        def release(left: int) -> None:  # 释放对应下标的数据
            limit[s[left]] += 1

        n = len(s)
        ans = n
        window = SlidingWindow(0, n)
        for left, right in window.slide_base_right(check, acquire, release):
            ans = min(ans, n - (right - left + 1))
        return ans


class Solution:
    """
    若需要取走每种字符至少k个 <=> 剩余字符是 (a-k)*'a', (b-k)*'b', (c-k)*'c' 的子串，即个数小于等于
    要使取走的字符总个数少 <=> 剩余字符尽可能多, 但是不能超过上面的上限
    滑动窗口
    """

    def takeCharacters(self, s: str, k: int) -> int:
        # 不能使limit任意一个字符小于0
        limit = Counter(s)
        for x in "abc":
            limit[x] -= k
            if limit[x] < 0:
                return -1

        l, n = 0, len(s)
        ans = n
        for r, c in enumerate(s):
            limit[c] -= 1
            while limit[c] < 0:
                limit[s[l]] += 1
                l += 1
            ans = min(ans, n - (r - l + 1))
        return ans
