"""
https://leetcode.cn/problems/report-spam-message/description/
3295. 举报垃圾信息
"""

from typing import List


class Solution:
    def reportSpam(self, message: List[str], bannedWords: List[str]) -> bool:
        has = set(bannedWords)
        return sum(w in has for w in message) >= 2
