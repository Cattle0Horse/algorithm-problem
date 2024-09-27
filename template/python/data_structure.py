import collections
from typing import Generator


class DSU:
    """并查集
    - initial_size: 初始化时节点个数
    - parent: 每个节点的父节点
    - group_count: 连通分量个数
    - group_size: 每个连通分量的大小
    """

    __slots__ = ("initial_size", "group_count", "parent", "group_size")

    def __init__(self, n: int) -> None:
        self.resize(n)

    def resize(self, n: int) -> None:
        self.initial_size: int = n  # 节点总个数
        self.parent: list[int] = list(range(n))  # 节点i的父节点
        self.group_count: int = n  # 连通分量个数
        self.group_size: list[int] = [1] * n  # 连通分量大小

    def find(self, x: int, compression: bool = True) -> int:
        """获取节点 x 的根节点，compression表示是否进行路径压缩"""
        root = x
        while root != self.parent[root]:
            root = self.parent[root]
        if compression:
            while x != root:
                self.parent[x], x = root, self.parent[x]
        return root

    def size(self, x: int) -> int:
        """获取节点 x 所在连通分量的大小"""
        return self.group_size[self.find(x)]

    def unite_to(self, head_from: int, head_to: int) -> None:
        """将head_from所在的子树合并到head_to中(一般来说它们都是根节点)"""
        if head_from == head_to:
            return
        self.parent[head_from] = head_to
        self.group_size[head_to] += self.group_size[head_from]
        self.group_count -= 1

    def unite_by_size(self, a: int, b: int) -> bool:
        """将连通分量小的并入联通分量大的中，如果两个连通分量大小相等，则a合并至b中，返回值表示是否合并成功"""
        a, b = self.find(a), self.find(b)
        if a == b:
            return False
        if self.group_size[a] > self.group_size[b]:
            self.unite_to(b, a)
        else:
            self.unite_to(a, b)
        return True

    def unite_by_id(self, a: int, b: int) -> bool:
        """将id大的并入id小的连通分量中，返回值表示是否合并成功"""
        a, b = self.find(a), self.find(b)
        if a == b:
            return False
        if a < b:
            self.unite_to(b, a)
        else:
            self.unite_to(a, b)
        return True

    def is_same_group(self, a: int, b: int) -> bool:
        """判断a和b是否属于同一个连通分量"""
        return self.find(a) == self.find(b)

    def is_head(self, i: int) -> bool:
        """判断i是否是其连通分量的根节点"""
        return i == self.parent[i]

    def get_heads(self) -> list[int]:
        """获取所有连通分量的根节点"""
        return [i for i, p in enumerate(self.parent) if i == p]

    def get_groups(self) -> list[list[int]]:
        """获取每一个连通分量中的所有节点"""
        groups: list[list[int]] = [[] for _ in range(self.group_count)]
        # 根节点在groups中的下标(非根节点无效)
        index: list[int] = [0] * self.initial_size
        j: int = 0
        for i in range(self.initial_size):
            if self.is_head(i):
                # 如何优雅的为python列表预分配内存?
                # groups[j].reserve(self.group_size[i])
                index[i] = j
                j += 1
        for i in range(self.initial_size):
            groups[index[self.find(i)]].append(i)
        return groups

    def __repr__(self) -> str:
        return str(self.parent)


class TrieNode:
    def __init__(self):
        self.children = {}
        self.is_end = False


class Trie:
    def __init__(self):
        self.root = TrieNode()

    def insert(self, word) -> bool:
        node = self.root
        for ch in word:
            if ch not in node.children:
                node.children[ch] = TrieNode()
            node = node.children[ch]
        node.is_end = True

    def find_word(self, word) -> bool:
        node = self.root
        for ch in word:
            if ch not in node.children:
                return False
            node = node.children[ch]
        return node.is_end

    def find_prefix(self, prefix) -> bool:
        node = self.root
        for ch in prefix:
            if ch not in node.children:
                return False
            node = node.children[ch]
        return True

    def find(self, text, as_prefix=False) -> bool:
        node = self.root
        for ch in text:
            if ch not in node.children:
                return False
            node = node.children[ch]
        return as_prefix or node.is_end


class TargetNumber:
    """
    用于判断目标字符串是否可以由给定的字符重新排列组成
    即只需拥有足够的目标数量
    """

    def __init__(self, target: str | list) -> None:
        self.need = collections.Counter(target)
        self.less = len(self.need)

    def acquire(self, v, cnt: int = 1) -> None:
        """获得字符，减少需要的个数"""
        before = self.need[v]
        self.need[v] -= cnt
        if before > 0 and self.need[v] <= 0:
            self.less -= 1

    def release(self, v, cnt: int = 1) -> None:
        """释放字符，增加需要的个数(请确保释放的是通过acquire方法获得的字符)"""
        before = self.need[v]
        self.need[v] += cnt
        if before <= 0 and self.need[v] > 0:
            self.less += 1

    def enough(self) -> bool:
        """判断需要的字符是否足够"""
        return self.less == 0

    def __repr__(self) -> str:
        return f"need = {self.need}, less = {self.less}"


class SlidingWindow:
    """滑动窗口"""

    def __init__(self, start: int, end: int) -> None:
        self.start = start
        self.end = end

    def slide_base_left(self, check, extend_right, shrink_left) -> Generator[tuple[int, int], None, None]:
        """
        返回以left为起点的最长的满足check条件的区间[left, right]
        表示区间[left, right]均满足check, (right, end)均不满足check
        要求: 若区间[left, right]不满足check，则[left, right+1]也不满足check

        def check(left: int, right: int)-> bool: # 判断[left, right]窗口是否满足条件
        def extend_right(right: int) -> None: # 扩展右边界
        def shrink_left(left: int) -> None: # 收缩左边界
        """
        right = self.start
        for left in range(self.start, self.end):
            while right < self.end and check(left, right - 1):
                extend_right(right)
                right += 1
            yield left, right - 1
            shrink_left(left)

    def slide_base_right(self, check, extend_right, shrink_left) -> Generator[tuple[int, int], None, None]:
        """
        返回以right为终点的最长的满足check条件的区间[left, right]
        表示区间[start, left)均不满足check, [left, right]均满足check
        要求: 若区间[left, right]满足check，则[left+1, right]也满足check

        def check(left: int, right: int)-> bool: # 判断[left, right]窗口是否满足条件
        def extend_right(right: int) -> None: # 扩展右边界
        def shrink_left(left: int) -> None: # 收缩左边界
        """
        left = self.start
        for right in range(self.start, self.end):
            extend_right(right)
            while left <= right and not check(left, right):
                shrink_left(left)
                left += 1
            yield left, right

    def slide_fixed_length(self, check, length: int, show_all_window: bool = False) -> Generator[collections.deque, None, None]:
        """
        固定长度滑动窗口(单调队列)，定长子数组区间查询
        要求: 对于下标 i < j, 若满足 check(i, j), 则下标 i 将不会成为答案(即永远被 j 遮挡)

        def check(i: int, j: int) -> bool: # 判断下标 i 是否会永远 j 遮挡
        """
        q = collections.deque()
        for right in range(self.start, self.end):
            if q and right - q[0] + 1 > length:
                q.popleft()
            while q and check(q[-1], right):
                q.pop()
            q.append(right)
            if show_all_window or right - self.start + 1 >= length:
                yield q
