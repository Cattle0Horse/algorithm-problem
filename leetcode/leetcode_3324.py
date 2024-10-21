"""
https://leetcode.cn/problems/find-the-sequence-of-strings-appeared-on-the-screen/description/
3324. 出现在屏幕上的字符串序列
"""

from string import ascii_lowercase
from typing import List


class Solution:
    def stringSequence(self, target: str) -> List[str]:
        ans = []
        s = []
        for c in target:
            s.append("?") # 占位
            for s[-1] in ascii_lowercase[:ord(c) - ord("a") + 1]:
                ans.append("".join(s))
        return ans
