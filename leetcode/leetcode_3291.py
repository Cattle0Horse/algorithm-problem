"""
https://leetcode.cn/problems/minimum-number-of-valid-strings-to-form-target-i/description/
3291. 形成目标字符串需要的最少字符串数 I
"""

from functools import cache
from math import inf
from typing import List


class TrieNode:
    def __init__(self):
        self.children = {}
        self.is_end = False


class Trie:
    def __init__(self):
        self.root = TrieNode()

    def insert(self, word):
        node = self.root
        for ch in word:
            if ch not in node.children:
                node.children[ch] = TrieNode()
            node = node.children[ch]
        node.is_end = True

    def find_word(self, word):
        node = self.root
        for ch in word:
            if ch not in node.children:
                return False
            node = node.children[ch]
        return node.is_end

    def find_prefix(self, prefix):
        node = self.root
        for ch in prefix:
            if ch not in node.children:
                return False
            node = node.children[ch]
        return True

    def find(self, text, is_prefix=False):
        node = self.root
        for ch in text:
            if ch not in node.children:
                return False
            node = node.children[ch]
        return is_prefix or node.is_end


class Solution:
    def minValidStrings(self, words: List[str], target: str) -> int:
        n = len(target)
        trie = Trie()
        for w in words:
            trie.insert(w)

        @cache
        def dfs(i: int):
            if i == n:
                return 0
            ans = inf
            node = trie.root
            for j in range(i, n):
                if target[j] not in node.children:
                    break
                node = node.children[target[j]]
                ans = min(ans, dfs(j + 1) + 1)
            return ans

        res = dfs(0)
        dfs.cache_clear()
        return res if res < inf else -1
