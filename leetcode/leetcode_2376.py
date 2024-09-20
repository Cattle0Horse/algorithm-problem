"""
https://leetcode.cn/problems/count-special-integers/?envType=daily-question&envId=2024-09-20
2376. 统计特殊整数
"""

from functools import cache


class Solution:
    def countSpecialNumbers(self, n: int) -> int:
        num = str(n)
        m = len(num)

        # 前导0会影响条件判断，因此单独处理
        @cache
        def dfs(i: int, mask: int, limit: bool, have: bool) -> int:
            if i == m:
                return 1
            ans = 0
            # 当前位为前导位，选0不计mask
            if not have:
                ans += dfs(i + 1, mask, False, False)
            down = 0 if have else 1
            up = int(num[i]) if limit else 9
            for j in range(down, up + 1):
                if mask >> j & 1:
                    continue
                ans += dfs(i + 1, mask | (1 << j), limit and j == up, True)
            return ans

        res = dfs(0, 0, True, False)
        dfs.cache_clear()
        # 0也是合法数字，但不算入答案
        return res - 1


sol = Solution()
print(sol.countSpecialNumbers(20) == 19)
print(sol.countSpecialNumbers(5) == 5)
print(sol.countSpecialNumbers(135) == 110)
