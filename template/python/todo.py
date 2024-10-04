r"""
# todo: 线段树二分
https://codeforces.com/blog/entry/18051
https://blog.csdn.net/liuliangcan/article/details/128703213
https://github.com/amomorning/algorithm-py/blob/master/template/data_structures.py
https://github.com/liupengsay/PyIsTheBestLang/blob/main/src/data_structure/zkw_segment_tree/template.py
https://www.bilibili.com/video/BV1gy4y1D7dx/
非递归线段树:
是一颗完全二叉树，它是自下而上计算的
若原数组有n个节点，则线段树有2n-1个节点(0号下标不使用，共2n个空间)
若原数组为 [1, 2, 3]，则线段树为 [zero, 6, 5, 1, 2, 3]，其中 0号节点为空
即前半部分存储内部表示区间节点，后半部分存储叶子节点
树形结构如下:
            1
           / \
          /   \
         2     3
        / \   
       /   \  
      4     5
      
[3, 5] 是叶子节点，即是 原数组

            001
    010             011
100     101

性质:
1. 树的节点数为 2n - 1
2. 若一个节点的编号为p，则它的父节点为 p >> 1，左子结点 为 p << 1，右子节点为 p << 1 | 1
3. 若两个节点编号分别为p和q，则它们是兄弟节点等价于 p ^ q == 1
4. 左节点为偶数，右节点为奇数
"""

import operator


class SegmentTree:
    """基础非递归线段树
    支持单点修改、区间询问
    """

    __slots__ = ("size", "combine", "initial", "cover")

    def __init__(self, size: int, combine, initial=0):
        """初始化线段树
        size: 原数组最大长度(预分配内存，构建逻辑在build方法中)
        combine: 合并函数，用于合并左右子节点的值，这决定了询问时的结果
        initial: 初始值，默认为0
        """
        self.size = size
        self.combine = combine
        self.initial = initial
        self.cover = [initial] * (2 * self.size)
        return

    @property
    def data(self):
        """获取叶子节点(原数组)"""
        return self.cover[self.size :]

    @data.setter
    def data(self, nums: list):
        """设置叶子节点(原数组)
        在设置后，应调用build方法才能继续使用该数据结构
        """
        # assert len(nums) >= self.size
        for i in range(self.size):
            self.cover[i + self.size] = nums[i]
        return

    def push_up(self, index: int):
        self.cover[index] = self.combine(self.cover[index << 1], self.cover[index << 1 | 1])
        return

    def build(self, nums: None | list = None):
        """自底向上建树，可指定叶子节点数组"""
        if nums:
            # assert len(nums) >= self.size
            for i in range(self.size):
                self.cover[i + self.size] = nums[i]
        for i in range(self.size - 1, 0, -1):
            self.push_up(i)
        return

    def single_push_up(self, index: int):
        """单点向上更新，用于单点更新的工具，可配合data使用，就像这样:
        index = 1
        seg.data[index] += 1
        seg.single_push_up(index)
        """
        index += self.size
        while index > 1:
            index >>= 1
            self.push_up(index)
        return

    def single_update(self, index: int, func):
        self.cover[index + self.size] = func(self.cover[index + self.size])
        self.single_push_up(index)
        return

    def single_set(self, index: int, val):
        self.cover[index + self.size] = val
        self.single_push_up(index)
        return

    def single_add(self, index: int, val):
        """对于加法这种与区间长度无关的操作，可以循环向上更新，不用使用 push_up
        单点乘法及单点设置则不行，除非转化为加法
        """
        index += self.size
        while index > 0:
            self.cover[index] += val
            index >>= 1
        return

    def single_query(self, index: int):
        return self.cover[index + self.size]

    def range_query(self, left: int, right: int):
        """ 区间询问，左闭右开 [left, right)
            支持不满足交换律的 combine 操作
            左右两边向内收缩区间
            在满二叉树的情况下
            对于left:
                若当前节点是右节点(即奇数)，则询问区间包含当前节点但不包含它的父节点，移动到父节点的右侧
                若当前节点是左节点(即偶数)且询问区间包括其父节点，那么只需要移动到父节点
            right同理
            直到 left 和 right 相遇
            在非满二叉树的情况下，将树的右侧部分向左移动来表示，就像这样，3的父节点的右侧为2，详见https://codeforces.com/blog/entry/18051
                1                       1
               / \                     / \
              /   \                   /   \
             2     3    ->           2
            / \                     / \
           /   \                   /   \
          4     5             3   4     5
        """
        ans_left = ans_right = 0
        left += self.size
        right += self.size
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

    def all_query(self):
        """区间询问，返回整个区间的值"""
        return self.cover[1]

    def __repr__(self) -> str:
        return str(self.data)


'''
   def max_right(self, l, f):
        """返回l右侧第一个不满足f的位置"""
        # assert 0 <= l and l <= self.n
        # assert f(self.e)
        if l == self.n:
            return self.n
        l += self.size

        sm, op, d, size = self.e, self.op, self.d, self.size
        while True:
            while l % 2 == 0:
                l >>= 1
            if not (f(op(sm, d[l]))):
                while l < size:
                    l = 2 * l
                    if f(op(sm, d[l])):
                        sm = op(sm, d[l])
                        l += 1
                return l - size
            sm = op(sm, d[l])
            l += 1
            if (l & -l) == l:
                break
        return self.n

    def min_left(self, r, f):
        """返回r左侧连续满足f的最远位置的位置"""
        # assert 0 <= r and r < self.n
        # assert f(self.e)
        if r == 0:
            return 0
        r += self.size
        sm, op, d, size = self.e, self.op, self.d, self.size

        while True:
            r -= 1
            while r > 1 and (r % 2):
                r >>= 1
            if not (f(op(d[r], sm))):
                while r < size:
                    r = (2 * r + 1)
                    if f(op(d[r], sm)):
                        sm = op(d[r], sm)
                        r -= 1
                return r + 1 - size
            sm = op(d[r], sm)
            if (r & -r) == r:
                break
        return 0
'''

seg = SegmentTree(3, operator.add)
seg.build([1, 2, 3])
print(seg.cover)
print(seg.range_query(0, 2))
print(seg.range_query(0, 3))
print(seg.range_query(1, 3))


class LazySegmentTree:
    """闭区间范围操作"""

    def __init__(self, n, combine, cover_initial, merge_cover, merge_tag, tag_initial, num_to_cover):
        self.n = n
        self.combine = combine  # method of cover push_up
        self.cover_initial = cover_initial  # cover_initial value of cover
        self.merge_cover = merge_cover  # method of tag to cover
        self.merge_tag = merge_tag  # method of tag merge
        self.tag_initial = tag_initial  # cover_initial value of tag
        self.num_to_cover = num_to_cover  # cover_initial value from num to cover
        self.lazy_tag = [self.tag_initial] * (2 * self.n)
        self.h = 0  # 树的高度-1, 用于快速找到上层节点，自上而下的push_down
        while (1 << self.h) < n:
            self.h += 1
        self.cover = [self.cover_initial] * (2 * self.n)
        self.cnt = [1] * (2 * self.n)  # 管理的数组数据个数, 即子树叶子节点个数
        for i in range(self.n - 1, 0, -1):
            self.cnt[i] = self.cnt[i << 1] + self.cnt[(i << 1) | 1]
        return

    def build(self, nums):
        for i in range(self.n):
            self.cover[i + self.n] = self.num_to_cover(nums[i])
        for i in range(self.n - 1, 0, -1):
            self.cover[i] = self.combine(self.cover[i << 1], self.cover[(i << 1) | 1])
        return

    def push_up(self, i):
        while i > 1:
            i >>= 1
            self.cover[i] = self.combine(self.cover[i << 1], self.cover[(i << 1) | 1])
        return

    def push_down(self, i):
        for s in range(self.h, 0, -1):
            x = i >> s
            if self.lazy_tag[x] != self.tag_initial:
                self.make_tag(x << 1, self.lazy_tag[x])
                self.make_tag((x << 1) | 1, self.lazy_tag[x])
                self.lazy_tag[x] = self.tag_initial
        x = i
        if self.lazy_tag[x] != self.tag_initial:
            if (i << 1) < self.n * 2:
                self.make_tag(x << 1, self.lazy_tag[x])
            if ((i << 1) | 1) < self.n * 2:
                self.make_tag((x << 1) | 1, self.lazy_tag[x])
            self.lazy_tag[x] = self.tag_initial
        return

    def make_tag(self, i, val):
        self.cover[i] = self.merge_cover(self.cover[i], val, self.cnt[i])  # cover val length
        self.lazy_tag[i] = self.merge_tag(val, self.lazy_tag[i])
        return

    def range_update(self, left, right, val):
        left += self.n
        right += self.n + 1
        ll = left
        rr = right
        self.push_down(ll)
        self.push_down(rr - 1)
        while left < right:
            if left & 1:
                self.make_tag(left, val)
                left += 1
            if right & 1:
                right -= 1
                self.make_tag(right, val)
            left >>= 1
            right >>= 1
        self.push_down(ll)
        self.push_down(rr - 1)
        self.push_up(ll)
        self.push_up(rr - 1)
        return

    def get(self):
        for i in range(1, self.n):
            if self.lazy_tag[i] != self.tag_initial:
                self.make_tag(i << 1, self.lazy_tag[i])
                self.make_tag((i << 1) | 1, self.lazy_tag[i])
                self.lazy_tag[i] = self.tag_initial
        return self.cover[self.n :]

    def point_get(self, ind):
        ans = 0
        ind += self.n
        while ind > 0:
            ans += self.lazy_tag[ind]
            ind //= 2
        return ans

    def range_query(self, left, right):
        ans_left = ans_right = self.cover_initial
        left += self.n
        right += self.n + 1
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


class LazySegmentTreeLength:
    def __init__(self, n, combine_cover, cover_initial, merge_cover_tag, merge_tag_tag, tag_initial):
        self.n = n
        self.cover_initial = cover_initial
        self.merge_cover_tag = merge_cover_tag
        self.merge_tag_tag = merge_tag_tag
        self.tag_initial = tag_initial
        self.lazy_tag = [self.tag_initial] * (2 * self.n)
        self.h = 0
        while (1 << self.h) < n:
            self.h += 1
        self.combine_cover = combine_cover
        self.cover = [self.cover_initial] * (2 * self.n)
        return

    def build(self, nums):
        for i in range(self.n):
            if nums[i]:
                self.cover[i + self.n] = (1, 1, 0, 1, 1, 1)
            else:
                self.cover[i + self.n] = (-1, -1, 1, 0, 1, 0)
        for i in range(self.n - 1, 0, -1):
            self.cover[i] = self.combine_cover(self.cover[i << 1], self.cover[(i << 1) | 1])
        return

    def push_up(self, i):
        while i > 1:
            i >>= 1
            self.cover[i] = self.combine_cover(self.cover[i << 1], self.cover[(i << 1) | 1])
        return

    def push_down(self, i):
        for s in range(self.h, 0, -1):
            x = i >> s
            if self.lazy_tag[x] != self.tag_initial:
                self.make_tag(x << 1, self.lazy_tag[x])
                self.make_tag((x << 1) | 1, self.lazy_tag[x])
                self.lazy_tag[x] = self.tag_initial
        x = i
        if self.lazy_tag[x] != self.tag_initial:
            if (i << 1) < self.n * 2:
                self.make_tag(x << 1, self.lazy_tag[x])
            if ((i << 1) | 1) < self.n * 2:
                self.make_tag((x << 1) | 1, self.lazy_tag[x])
            self.lazy_tag[x] = self.tag_initial
        return

    def make_tag(self, i, val):
        self.cover[i] = self.merge_cover_tag(self.cover[i], val)
        self.lazy_tag[i] = self.merge_tag_tag(val, self.lazy_tag[i])
        return

    def range_update(self, left, right, val):
        left += self.n
        right += self.n + 1
        ll = left
        rr = right
        self.push_down(ll)
        self.push_down(rr - 1)
        while left < right:
            if left & 1:
                self.make_tag(left, val)
                left += 1
            if right & 1:
                right -= 1
                self.make_tag(right, val)
            left >>= 1
            right >>= 1
        self.push_down(ll)
        self.push_down(rr - 1)

        self.push_up(ll)
        self.push_up(rr - 1)
        return

    def get(self):
        for i in range(1, self.n):
            if self.lazy_tag[i] != self.tag_initial:
                self.make_tag(i << 1, self.lazy_tag[i])
                self.make_tag((i << 1) | 1, self.lazy_tag[i])
                self.lazy_tag[i] = self.tag_initial
        return self.cover[self.n :]

    def point_get(self, ind):
        ans = 0
        ind += self.n
        while ind > 0:
            ans += self.lazy_tag[ind]
            ind //= 2
        return ans

    def range_query(self, left, right):
        ans_left = ans_right = self.cover_initial
        left += self.n
        right += self.n + 1
        self.push_down(left)
        self.push_down(right - 1)
        while left < right:
            if left & 1:
                ans_left = self.combine_cover(ans_left, self.cover[left])
                left += 1
            if right & 1:
                right -= 1
                ans_right = self.combine_cover(self.cover[right], ans_right)
            left >>= 1
            right >>= 1
        return self.combine_cover(ans_left, ans_right)


if __name__ == "__main__":
    arr = [1, 2, 3]
    seg = LazySegmentTree(len(arr), None, None, None, None, None, None)
