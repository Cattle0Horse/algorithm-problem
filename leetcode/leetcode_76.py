"""
https://leetcode.cn/problems/minimum-window-substring/description/
76. 最小覆盖子串
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


class Solution:
    def minWindow(self, s: str, t: str) -> str:
        need = TargetNumber(t)
        r, n = 0, len(s)
        ans = None
        for l, c in enumerate(s):
            while r < n and not need.enough():
                need.acquire(s[r])
                r += 1
            if need.enough() and (not ans or r - l < len(ans)):
                ans = s[l:r]
            need.release(c)
        return ans if ans else ""
