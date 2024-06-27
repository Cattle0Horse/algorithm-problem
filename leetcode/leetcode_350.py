# https://leetcode.cn/problems/intersection-of-two-arrays-ii/
from ast import List
from collections import Counter

class Solution:
    def intersect(self, nums1: List[int], nums2: List[int]) -> List[int]:
        b = Counter(nums2)
        ans = []
        for num, cnt in Counter(nums1).items():
            for _ in range(min(b[num], cnt)):
                ans.append(num)
        return ans
        
        