"""
https://leetcode.cn/problems/minimum-number-of-valid-strings-to-form-target-ii/description/
3292. 形成目标字符串需要的最少字符串数 II
"""

from bisect import bisect_left
import random
from typing import List

"""
按前缀长度为i的字符串分组，target中某一位置开始出现不能匹配的字符串，则再增加字符也不能匹配(二段性)
如何快速求出target是否在前缀长度为i的字符串组中?
将所有字符串放在set中，字符串哈希预处理，O(1)时间查找
"""


class StringHashSingle:
    def __init__(self, s):
        """多项式字符串哈希
        哈希函数: hash(s) = s[0] * base^(n-1) + s[1] * base^(n-2) + ... + s[n-1]
        """
        self.n = len(s)
        # self.base = random.randint(8 * 10**8, 9 * 10**8)
        # self.mod = random.getrandbits(64)
        _base = max(self.n + 1, 150)
        self.base = random.randint(_base, 2 * _base)
        # self.mod = (1 << 32) - 1
        self.mod = 10**9 + 7
        # self.mod = 10**18 + 9

        self.pow_base = [1] * (self.n + 1)
        self.pre_hash = [0] * (self.n + 1)
        for j, w in enumerate(s):
            self.pow_base[j + 1] = (self.pow_base[j] * self.base) % self.mod
            self.pre_hash[j + 1] = (self.pre_hash[j] * self.base + ord(w)) % self.mod
        return

    def sub_hash(self, l, r):
        """substring s[l, r) hash value"""
        assert 0 <= l < r <= self.n
        ans = (self.pre_hash[r] - self.pre_hash[l] * self.pow_base[r - l]) % self.mod
        return ans

    def hash(self, s):
        """any string hash value"""
        ans = 0
        for c in s:
            ans = (ans * self.base + ord(c)) % self.mod
        return ans

    def prefix_seq_hash(self, s):
        """An array of hash values for the prefix string of any string"""
        ans = 0
        for c in s:
            ans = (ans * self.base + ord(c)) % self.mod
            yield ans


class Solution:
    def minValidStrings(self, words: List[str], target: str) -> int:
        str_hash = StringHashSingle(target)
        max_len = max(map(len, words))
        sets = [set() for _ in range(max_len)]
        for w in words:
            for j, h in enumerate(str_hash.prefix_seq_hash(w)):
                sets[j].add(h)
        ans = 0
        cur_r, nxt_r, n = 0, 0, len(target)
        for i in range(n):
            check = lambda sz: str_hash.sub_hash(i, i + sz + 1) not in sets[sz]
            sz = bisect_left(range(min(n - i, max_len)), True, key=check)
            nxt_r = max(nxt_r, i + sz)
            if i == cur_r:  # 到达已建造的桥的右端点
                if i == nxt_r:  # 无论怎么造桥，都无法从 i 到 i+1
                    return -1
                cur_r = nxt_r  # 建造下一座桥
                ans += 1
        return ans
