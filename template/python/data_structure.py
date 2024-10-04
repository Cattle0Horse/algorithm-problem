import collections
from typing import Callable, Generator, Generic, TypeVar


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
        return f"DSU({self.parent})"


class TrieNode:
    def __init__(self):
        self.children = {}
        self.is_end = False


class Trie:
    def __init__(self):
        self.root = TrieNode()

    def insert(self, word) -> None:
        node = self.root
        for ch in word:
            if ch not in node.children:
                node.children[ch] = TrieNode()
            node = node.children[ch]
        node.is_end = True

    def search(self, word) -> bool:
        node = self.root
        for ch in word:
            if ch not in node.children:
                return False
            node = node.children[ch]
        return node.is_end

    def starts_with(self, prefix) -> bool:
        node = self.root
        for ch in prefix:
            if ch not in node.children:
                return False
            node = node.children[ch]
        return True


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
        """[start, end)"""
        self.start = start
        self.end = end

    def slide_base_left(
        self, check: Callable[[int, int], bool], extend_right: Callable[[int], None], shrink_left: Callable[[int], None]
    ) -> Generator[tuple[int, int], None, None]:
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

    def slide_base_right(
        self, check: Callable[[int, int], bool], extend_right: Callable[[int], None], shrink_left: Callable[[int], None]
    ) -> Generator[tuple[int, int], None, None]:
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

    def slide_fixed_length(
        self, check: Callable[[int, int], bool], length: int, show_all_window: bool = False
    ) -> Generator[collections.deque, None, None]:
        """
        固定长度滑动窗口(单调队列)，定长子数组区间查询
        要求: 对于下标 i < j, 若满足 check(i, j), 则下标 i 将不会成为答案(即永远被 j 遮挡)

        def check(i: int, j: int) -> bool: # 判断下标 i 是否会永远 j 遮挡
        """
        q: collections.deque = collections.deque()
        for right in range(self.start, self.end):
            if q and right - q[0] + 1 > length:
                q.popleft()
            while q and check(q[-1], right):
                q.pop()
            q.append(right)
            if show_all_window or right - self.start + 1 >= length:
                yield q


class MonotonicStack:
    """单调栈: 及时去掉(或不加入)无用数据，保证栈中数据的有序性
    - 由于其单调性，为二分查找提供了良好的条件(单调栈上二分)
    - 可以选择通过 是否入栈 或 出栈 维护单调性，关键点在当前元素与栈顶元素的关系
    - 可以常用于查找上一或下一个满足条件元素(可以一次遍历同时确定), 也可以查找第一个和最后一个满足条件的元素(通过二分或第二次逆序遍历)
    - 有时逆序遍历可能更简单
    P.S. 由于可变性非常高，因此这里只提供常用的单调栈实现
    """

    def __init__(self, start: int, end: int) -> None:
        """[start, end)"""
        self.start = start
        self.end = end

    def before_index_generator(self, check: Callable[[int, int], bool]) -> Generator[tuple[int, int], None, list[int]]:
        """
        查找上一个满足check的元素，可以在生成器生成所有元素后，通过next方法并捕获StopIteration异常来获取剩余栈内元素

        def check(i: int, j: int) -> bool: # 对于 i < j 是否满足条件
        """
        stk: list[int] = []
        for j in range(self.start, self.end):
            while stk and not check(stk[-1], j):
                stk.pop()
            if stk:
                # 当前元素遇到了第一个满足条件的元素
                yield stk[-1], j
            stk.append(j)
        return stk

    def after_index_generator(self, check: Callable[[int, int], bool]) -> Generator[tuple[int, int], None, list[int]]:
        """
        查找下一个满足check的元素，可以在生成器生成所有元素后，通过next方法并捕获StopIteration异常来获取剩余栈内元素素

        def check(i: int, j: int) -> bool: # 对于 i < j 是否满足条件
        """
        stk: list[int] = []
        for j in range(self.start, self.end):
            # 栈内元素遇到了第一个满足条件的元素(出栈)
            while stk and check(stk[-1], j):
                yield stk.pop(), j
            stk.append(j)
        return stk

    def before_index(self, check: Callable[[int, int], bool], initial: None | int = None) -> list[None | int]:
        """
        查找上一个满足check的元素

        def check(i: int, j: int) -> bool: # 对于 i < j 是否满足条件
        """
        ans = [initial] * (self.end - self.start)
        for i, j in self.before_index_generator(check):
            ans[i - self.start] = j - self.start
        return ans

    def after_index(self, check: Callable[[int, int], bool], initial: None | int = None) -> list[None | int]:
        """
        查找下一个满足check的元素

        def check(i: int, j: int) -> bool: # 对于 i < j 是否满足条件
        """
        ans = [initial] * (self.end - self.start)
        for i, j in self.after_index_generator(check):
            ans[i - self.start] = j - self.start
        return ans


"""
ZKW线段树、非递归线段树:
1. 若管理长度为n的数组, 那么线段树长度为2n(下标0不使用), 区间数据为[1, n-1], 原数组数据为[n, 2n-1]
2. 对于基础线段树可以像区间查询一样进行区间修改, 然后可以累加直至根路径上的节点值进行单点查询, 但支持的区间操作有限
"""


CoverType = TypeVar("CoverType")
TagType = TypeVar("TagType")


class SegmentTree(Generic[CoverType]):
    """基础非递归线段树
    支持单点修改、区间询问
    """

    __slots__ = ("size", "combine", "cover_initial", "cover")

    def __init__(self, size: int, combine: Callable[[CoverType, CoverType], CoverType], cover_initial: CoverType) -> None:
        """初始化线段树
        size: 原数组最大长度(预分配内存，构建逻辑在build方法中)
        combine: 用于合并左右子节点的值，这决定了询问时的结果
        initial: 初始值
        """
        self.size = size
        self.combine = combine
        self.cover_initial = cover_initial
        self.cover = [cover_initial] * (2 * self.size)

    @property
    def data(self) -> list[CoverType]:
        """获取叶子节点(原数组)"""
        return self.cover[self.size :]

    @data.setter
    def data(self, nums: list[CoverType]):
        """设置叶子节点(原数组)
        在设置后，应调用build方法才能继续使用该数据结构
        """
        # assert len(nums) >= self.size
        for i in range(self.size):
            self.cover[i + self.size] = nums[i]

    def build(self, nums: None | list[CoverType] = None):
        """自底向上建树，可指定叶子节点数组"""
        if nums:
            # assert len(nums) >= self.size
            for i in range(self.size):
                self.cover[i + self.size] = nums[i]
        for i in range(self.size - 1, 0, -1):
            self.cover[i] = self.combine(self.cover[i << 1], self.cover[i << 1 | 1])

    def push_up(self, index: int):
        """从index向上更新节点值"""
        while index > 1:
            index >>= 1
            self.cover[index] = self.combine(self.cover[index << 1], self.cover[index << 1 | 1])

    def single_update_by_combine(self, index: int, func: Callable[[CoverType], CoverType]):
        """单点修改, 逐步向上合并子节点"""
        index += self.size
        self.cover[index] = func(self.cover[index])
        self.push_up(index)

    def single_update_by_func(self, index: int, func: Callable[[CoverType], CoverType]):
        """单点修改, 修改父节点直至根节点"""
        index += self.size
        while index > 0:
            self.cover[index] = func(self.cover[index])
            index >>= 1

    def single_query(self, index: int) -> CoverType:
        return self.cover[index + self.size]

    def range_query(self, left: int, right: int) -> CoverType:
        """区间查询, [left, right)"""
        ans_left = ans_right = self.cover_initial
        left += self.size
        right += self.size
        while left < right:
            if left & 1:  # left是右节点, 则记录答案并且移动至右侧父节点
                ans_left = self.combine(ans_left, self.cover[left])
                left += 1
            if right & 1:  # right是左节点, 则记录答案并移动至左侧父节点
                right -= 1
                ans_right = self.combine(self.cover[right], ans_right)
            left >>= 1
            right >>= 1
        return self.combine(ans_left, ans_right)

    def all_query(self) -> CoverType:
        """区间询问，返回整个区间的值"""
        return self.cover[1]

    def __repr__(self) -> str:
        return f"SegmentTree({self.cover})"


class LazySegmentTree(Generic[CoverType, TagType]):
    """懒标记线段树
    支持区间修改、区间查询
    """

    def __init__(
        self,
        size: int,
        combine: Callable[[CoverType, CoverType], CoverType],
        cover_initial: CoverType,
        tag_initial: TagType,
        merge_cover_tag: Callable[[CoverType, TagType], CoverType],
        merge_tag_tag: Callable[[TagType, TagType], TagType],
    ) -> None:
        """初始化线段树
        size: 原数组最大长度(预分配内存，构建逻辑在build方法中)
        combine: 用于合并左右子节点的值，这决定了询问时的结果
        cover_initial: 树节点初始值
        tag_initial: 标记初始值
        merge_cover_tag: 标记合并至节点(用于标记下传)
        merge_tag_tag: 合并两个标记(用于标记下传)
        h: 树深度(用于快速查找一个节点的到根节点的路径, 自上而下的下传标记, 从0计数)
        """
        self.size = size
        self.combine = combine
        self.cover_initial = cover_initial
        self.cover = [cover_initial] * (2 * size)
        self.tag_initial = tag_initial
        self.merge_cover_tag = merge_cover_tag
        self.merge_tag_tag = merge_tag_tag
        self.lazy_tag = [tag_initial] * (2 * size)
        self.h = 0
        while (1 << self.h) < size:
            self.h += 1

    @property
    def data(self) -> list[CoverType]:
        """获取叶子节点(原数组)"""
        return self.cover[self.size :]

    @data.setter
    def data(self, nums: list[CoverType]):
        """设置叶子节点(原数组)
        在设置后，应调用build方法才能继续使用该数据结构
        """
        # assert len(nums) >= self.size
        for i in range(self.size):
            self.cover[i + self.size] = nums[i]

    def build(self, nums: None | list[CoverType] = None):
        """自底向上建树，可指定叶子节点数组"""
        if nums:
            # assert len(nums) >= self.size
            for i in range(self.size):
                self.cover[i + self.size] = nums[i]
        for i in range(self.size - 1, 0, -1):
            self.cover[i] = self.combine(self.cover[i << 1], self.cover[i << 1 | 1])

    def propagate_tag(self, index: int, tag: TagType) -> None:
        """传播标记至节点index"""
        self.cover[index] = self.merge_cover_tag(self.cover[index], tag)
        self.lazy_tag[index] = self.merge_tag_tag(tag, self.lazy_tag[index])

    def push_up(self, index: int) -> None:
        """从index向上更新节点值"""
        while index > 1:
            index >>= 1
            self.cover[index] = self.combine(self.cover[index << 1], self.cover[index << 1 | 1])

    def push_down(self, index) -> None:
        """从根节点下放标记直至index"""
        for s in range(self.h, 0, -1):
            i = index >> s
            if self.lazy_tag[i] != self.tag_initial:
                self.propagate_tag(i << 1, self.lazy_tag[i])
                self.propagate_tag(i << 1 | 1, self.lazy_tag[i])
                self.lazy_tag[i] = self.tag_initial
        # 叶子节点的tag不会再传播了, 不用处理
        # if self.lazy_tag[index] != self.tag_initial:
        #     if (index << 1) < 2 * self.size:
        #         self.propagate_tag(index << 1, self.lazy_tag[index])
        #     if (index << 1 | 1) < 2 * self.size:
        #         self.propagate_tag(index << 1 | 1, self.lazy_tag[index])
        #     self.lazy_tag[index] = self.tag_initial

    def push_down_all_tag(self) -> None:
        """下放所有标记，执行后可访问data查询数组值"""
        for i in range(1, self.size):
            if self.lazy_tag[i] != self.tag_initial:
                self.propagate_tag(i << 1, self.lazy_tag[i])
                self.propagate_tag(i << 1 | 1, self.lazy_tag[i])
                self.lazy_tag[i] = self.tag_initial

    def single_update(self, index: int, tag: TagType) -> None:
        """单点更新"""
        index += self.size
        self.push_down(index)
        self.propagate_tag(index, tag)
        self.push_up(index)

    def range_update(self, left: int, right: int, tag: TagType) -> None:
        """区间更新, [left, right)"""
        left += self.size
        right += self.size
        self.push_down(left)
        self.push_down(right - 1)
        l, r = left, right
        while l < r:
            if l & 1:
                self.propagate_tag(l, tag)
                l += 1
            if r & 1:
                r -= 1
                self.propagate_tag(r, tag)
            l >>= 1
            r >>= 1
        self.push_down(left)
        self.push_down(right - 1)
        self.push_up(left)
        self.push_up(right - 1)

    def single_query(self, index: int) -> CoverType:
        """单点查询"""
        index += self.size
        self.push_down(index)
        return self.cover[index]

    def range_query(self, left: int, right: int) -> CoverType:
        """区间查询, [left, right)"""
        ans_left = ans_right = self.cover_initial
        left += self.size
        right += self.size
        self.push_down(left)
        self.push_down(right - 1)
        while left < right:
            if left & 1:
                ans_left = self.combine(ans_left, self.cover[left])
                left += 1
            if right & 1:
                right -= 1
                ans_right = self.combine(self.cover[right], ans_right)
            left >>= 1
            right >>= 1
        return self.combine(ans_left, ans_right)

    def all_query(self) -> CoverType:
        """区间询问，返回整个区间的值"""
        return self.cover[1]

    def __repr__(self) -> str:
        return f"SegmentTree(cover: {self.cover}, lazy_tag: {self.lazy_tag})"


class LazySegmentTreeWithLength(Generic[CoverType, TagType]):
    """懒标记线段树(包含区间长度信息)
    支持区间修改、区间查询
    """

    def __init__(
        self,
        size: int,
        combine: Callable[[CoverType, CoverType], CoverType],
        cover_initial: CoverType,
        tag_initial: TagType,
        merge_cover_tag: Callable[[CoverType, TagType, int], CoverType],
        merge_tag_tag: Callable[[TagType, TagType], TagType],
    ) -> None:
        """初始化线段树
        size: 原数组最大长度(预分配内存，构建逻辑在build方法中)
        combine: 用于合并左右子节点的值，这决定了询问时的结果
        cover_initial: 树节点初始值
        tag_initial: 标记初始值
        merge_cover_tag: 标记合并至节点(用于标记下传)
        merge_tag_tag: 合并两个标记(用于标记下传)
        h: 树深度(用于快速查找一个节点的到根节点的路径, 自上而下的下传标记, 从0计数)
        length: 节点管理原数组的数据个数(为了支持与区间长度有关的操作)
        """
        self.size = size
        self.combine = combine
        self.cover_initial = cover_initial
        self.cover = [cover_initial] * (2 * size)
        self.tag_initial = tag_initial
        self.merge_cover_tag = merge_cover_tag
        self.merge_tag_tag = merge_tag_tag
        self.lazy_tag = [tag_initial] * (2 * size)
        self.h = 0
        while (1 << self.h) < size:
            self.h += 1
        self.length = [1] * (2 * size)
        for i in range(size - 1, 0, -1):
            self.length[i] = self.length[i << 1] + self.length[i << 1 | 1]

    @property
    def data(self) -> list[CoverType]:
        """获取叶子节点(原数组)"""
        return self.cover[self.size :]

    @data.setter
    def data(self, nums: list[CoverType]):
        """设置叶子节点(原数组)
        在设置后，应调用build方法才能继续使用该数据结构
        """
        # assert len(nums) >= self.size
        for i in range(self.size):
            self.cover[i + self.size] = nums[i]

    def build(self, nums: None | list[CoverType] = None):
        """自底向上建树，可指定叶子节点数组"""
        if nums:
            # assert len(nums) >= self.size
            for i in range(self.size):
                self.cover[i + self.size] = nums[i]
        for i in range(self.size - 1, 0, -1):
            self.cover[i] = self.combine(self.cover[i << 1], self.cover[i << 1 | 1])

    def propagate_tag(self, index: int, tag: TagType) -> None:
        """传播标记至节点index"""
        self.cover[index] = self.merge_cover_tag(self.cover[index], tag, self.length[index])
        self.lazy_tag[index] = self.merge_tag_tag(tag, self.lazy_tag[index])

    def push_up(self, index: int) -> None:
        """从index向上更新节点值"""
        while index > 1:
            index >>= 1
            self.cover[index] = self.combine(self.cover[index << 1], self.cover[index << 1 | 1])

    def push_down(self, index) -> None:
        """从根节点下放标记直至index"""
        for s in range(self.h, 0, -1):
            i = index >> s
            if self.lazy_tag[i] != self.tag_initial:
                self.propagate_tag(i << 1, self.lazy_tag[i])
                self.propagate_tag(i << 1 | 1, self.lazy_tag[i])
                self.lazy_tag[i] = self.tag_initial
        # 叶子节点的tag不会再传播了, 不用处理
        # if self.lazy_tag[index] != self.tag_initial:
        #     if (index << 1) < 2 * self.size:
        #         self.propagate_tag(index << 1, self.lazy_tag[index])
        #     if (index << 1 | 1) < 2 * self.size:
        #         self.propagate_tag(index << 1 | 1, self.lazy_tag[index])
        #     self.lazy_tag[index] = self.tag_initial

    def push_down_all_tag(self) -> None:
        """下放所有标记，执行后可访问data查询数组值"""
        for i in range(1, self.size):
            if self.lazy_tag[i] != self.tag_initial:
                self.propagate_tag(i << 1, self.lazy_tag[i])
                self.propagate_tag(i << 1 | 1, self.lazy_tag[i])
                self.lazy_tag[i] = self.tag_initial

    def single_update(self, index: int, tag: TagType) -> None:
        """单点更新"""
        index += self.size
        self.push_down(index)
        self.propagate_tag(index, tag)
        self.push_up(index)

    def range_update(self, left: int, right: int, tag: TagType) -> None:
        """区间更新, [left, right)"""
        left += self.size
        right += self.size
        self.push_down(left)
        self.push_down(right - 1)
        l, r = left, right
        while l < r:
            if l & 1:
                self.propagate_tag(l, tag)
                l += 1
            if r & 1:
                r -= 1
                self.propagate_tag(r, tag)
            l >>= 1
            r >>= 1
        self.push_down(left)
        self.push_down(right - 1)
        self.push_up(left)
        self.push_up(right - 1)

    def single_query(self, index: int) -> CoverType:
        """单点查询"""
        index += self.size
        self.push_down(index)
        return self.cover[index]

    def range_query(self, left: int, right: int) -> CoverType:
        """区间查询, [left, right)"""
        ans_left = ans_right = self.cover_initial
        left += self.size
        right += self.size
        self.push_down(left)
        self.push_down(right - 1)
        while left < right:
            if left & 1:
                ans_left = self.combine(ans_left, self.cover[left])
                left += 1
            if right & 1:
                right -= 1
                ans_right = self.combine(self.cover[right], ans_right)
            left >>= 1
            right >>= 1
        return self.combine(ans_left, ans_right)

    def all_query(self) -> CoverType:
        """区间询问，返回整个区间的值"""
        return self.cover[1]

    def __repr__(self) -> str:
        return f"SegmentTree(cover: {self.cover}, lazy_tag: {self.lazy_tag})"
