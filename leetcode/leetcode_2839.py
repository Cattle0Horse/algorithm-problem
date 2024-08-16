from collections import Counter


class Solution:
    def canBeEqual(self, s1: str, s2: str) -> bool:
        return all(Counter(s1[i::2]) == Counter(s2[i::2]) for i in range(2))
