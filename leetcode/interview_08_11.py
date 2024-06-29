# https://leetcode.cn/problems/coin-lcci/description/

class Solution:
    def waysToChange(self, n: int) -> int:
        if n <= 1:
            return 1
        mod = 10**9+7
        coins = (25, 10, 5, 1)
        dp = [0] * (n+1)
        dp[0] = 1
        for coin in coins:
            for i in range(coin, n+1):
                dp[i] += dp[i-coin]
        return dp[n]
