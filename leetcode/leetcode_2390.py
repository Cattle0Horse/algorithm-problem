"""
https://leetcode.cn/problems/removing-stars-from-a-string/?envType=daily-question&envId=2024-09-14
2390. 从字符串中移除星号
"""


class Solution:
    def removeStars(self, s: str) -> str:
        ans = []
        for c in s:
            if c == "*":
                ans.pop()
            else:
                ans.append(c)
        return "".join(ans)
