import random

to_chr = lambda x, a="a": chr(x + ord(a))
to_ord = lambda x, a="a": ord(x) - ord(a)


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
