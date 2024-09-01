"""
3273. 对 Bob 造成的最少伤害
https://leetcode.cn/problems/minimum-amount-of-damage-dealt-to-bob/
"""

from typing import List


class Solution:
    def minDamage(self, power: int, damage: List[int], health: List[int]) -> int:
        """
        对于两个敌人A，B，攻击分别记为dA，dB，需要攻击次数为kA，kB  (kx = ceil(hx / power))
        攻击顺序有两种，对应结果为：
        A->B: kA * dA + (kA + kB) * dB
        B->A: kB * dB + (kA + kB) * dA
        那么二者比较：
        kA * dA + (kA + kB) * dB  <=>  kB * dB + (kA + kB) * dA
        左右移项合并：
        kA * dB  <=>  kB * dA
        kA / dA  <=>  kB / dB
        即按照 k/d 排序，顺次攻击敌人
        """
        n = len(damage)
        cnt = [(h + power - 1) // power for h in health]
        idx = [i for i in range(n)]
        idx.sort(key=lambda i: cnt[i] / damage[i])

        ans = 0
        k = 0
        for id in idx:
            d, c = damage[id], cnt[id]
            k += c
            ans += k * d
        return ans
