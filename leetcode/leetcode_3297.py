"""
https://leetcode.cn/problems/count-substrings-that-can-be-rearranged-to-contain-a-string-i/description/
3297. 统计重新排列后包含另一个字符串的子字符串数目 I
"""

"""
如果一个子字符串满足字符集合是word2的超集,那么左右任意扩展都是答案
以当前下标为起点的字符串对答案的贡献
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


class Solution:
    """
    如果一个子字符串满足字符集合是word2的超集,那么左右任意扩展都是答案
    以当前下标为起点的字符串对答案的贡献
    """

    def validSubstringCount(self, word1: str, word2: str) -> int:
        need = TargetNumber(word2)
        l, ans = 0, 0
        for c in word1:
            need.acquire(c)
            while need.enough():
                need.release(word1[l])
                l += 1
            ans += l
        return ans
