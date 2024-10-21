"""
https://leetcode.cn/problems/count-substrings-with-k-frequency-characters-i/description/
3325. 字符至少出现 K 次的子字符串 I
"""

import collections
from typing import Generator


class SlidingWindow:
    """滑动窗口"""

    def __init__(self, start: int, end: int) -> None:
        self.start = start
        self.end = end

    def slide_base_left(self, check, extend_right, shrink_left) -> Generator[tuple[int, int], None, None]:
        """
        返回以left为起点的最长的满足check条件的区间[left, right]
        表示区间[left, right]均满足check, (right, end)均不满足check
        要求: 若区间[left, right]不满足check，则[left, right+1]也不满足check

        def check(left: int, right: int)-> bool: # 判断[left, right]窗口是否满足条件
        def extend_right(right: int) -> None: # 扩展右边界
        def shrink_left(left: int) -> None: # 收缩左边界
        """
        right = self.start
        for left in range(self.start, self.end):
            while right < self.end and check(left, right - 1):
                extend_right(right)
                right += 1
            yield left, right - 1
            shrink_left(left)

    def slide_base_right(self, check, extend_right, shrink_left) -> Generator[tuple[int, int], None, None]:
        """
        返回以right为终点的最长的满足check条件的区间[left, right]
        表示区间[start, left)均不满足check, [left, right]均满足check
        要求: 若区间[left, right]满足check，则[left+1, right]也满足check

        def check(left: int, right: int)-> bool: # 判断[left, right]窗口是否满足条件
        def extend_right(right: int) -> None: # 扩展右边界
        def shrink_left(left: int) -> None: # 收缩左边界
        """
        left = self.start
        for right in range(self.start, self.end):
            extend_right(right)
            while left <= right and not check(left, right):
                shrink_left(left)
                left += 1
            yield left, right

    def slide_fixed_length(self, check, length: int, show_all_window: bool = False) -> Generator[collections.deque, None, None]:
        """
        固定长度滑动窗口(单调队列)，定长子数组区间查询
        要求: 对于下标 i < j, 若满足 check(i, j), 则下标 i 将不会成为答案(即永远被 j 遮挡)

        def check(i: int, j: int) -> bool: # 判断下标 i 是否会永远 j 遮挡
        """
        q = collections.deque()
        for right in range(self.start, self.end):
            if q and right - q[0] + 1 > length:
                q.popleft()
            while q and check(q[-1], right):
                q.pop()
            q.append(right)
            if show_all_window or right - self.start + 1 >= length:
                yield q


class Solution:
    def numberOfSubstrings(self, s: str, k: int) -> int:
        ans = 0
        n = len(s)
        window = SlidingWindow(0, n)
        cnt, num = collections.defaultdict(int), 0

        def check(left: int, right: int) -> bool:  # 判断[left, right]窗口是否满足条件
            return num == 0

        def extend_right(right: int) -> None:  # 扩展右边界
            nonlocal num
            cnt[s[right]] += 1
            if cnt[s[right]] == k:
                num += 1

        def shrink_left(left: int) -> None:  # 收缩左边界
            nonlocal num
            cnt[s[left]] -= 1
            if cnt[s[left]] == k - 1:
                num -= 1

        for left, right in window.slide_base_right(check, extend_right, shrink_left):
            # [0, left)
            ans += left
        return ans


class Solution:
    def numberOfSubstrings(self, s: str, k: int) -> int:
        ans = 0
        cnt = collections.defaultdict(int)
        left = 0
        for c in s:
            cnt[c] += 1
            # 左边界收缩，找到第一个不满足条件的下标
            while cnt[c] >= k:
                cnt[s[left]] -= 1
                left += 1
            ans += left
        return ans
