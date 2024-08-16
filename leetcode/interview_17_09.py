# https://leetcode.cn/problems/get-kth-magic-number-lcci/description/

from math import inf


class Solution:
    def getKthMagicNumber(self, k: int) -> int:
        dp = [inf] * (k + 1)
        dp[1] = 1
        vs = (3, 5, 7)
        ps = [1] * len(vs)
        for i in range(2, k + 1):
            dp[i] = min(dp[p] * v for p, v in zip(ps, vs))
            for j in range(len(ps)):
                ps[j] += dp[i] == dp[ps[j]] * vs[j]
        return dp[k]
