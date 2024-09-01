"""
2024. 考试的最大困扰度
https://leetcode.cn/problems/maximize-the-confusion-of-an-exam/description/?envType=daily-question&envId=2024-09-02
"""


class Solution:
    """
    双指针，滑动窗口
    保证区间F个数<=k
    """

    def maxConsecutiveAnswers(self, s: str, k: int) -> int:
        def solve(target: str) -> int:
            l, cnt = 0, 0
            ans = 0
            for r, c in enumerate(s):
                cnt += c == target
                # [l, r]
                while cnt > k:
                    cnt -= s[l] == target
                    l += 1
                ans = max(ans, r - l + 1)
            return ans

        return max(solve("F"), solve("T"))
