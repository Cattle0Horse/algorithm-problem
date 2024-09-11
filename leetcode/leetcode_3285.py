"""
https://leetcode.cn/problems/find-indices-of-stable-mountains/description/
3285. 找到稳定山的下标
"""

from typing import List


class Solution:
    def stableMountains(self, height: List[int], threshold: int) -> List[int]:
        return [i + 1 for i in range(len(height) - 1) if height[i] > threshold]
