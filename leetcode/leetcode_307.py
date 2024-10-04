"""
https://leetcode.cn/problems/range-sum-query-mutable/description/
307. 区域和检索 - 数组可修改
"""

import operator
from typing import Callable, Generic, List, TypeVar

CoverType = TypeVar("CoverType")


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


class NumArray:

    def __init__(self, nums: List[int]):
        self.seg = SegmentTree(len(nums), operator.add, 0)
        self.seg.build(nums)

    def update(self, index: int, val: int) -> None:
        self.seg.single_update_by_combine(index, lambda x: val)

    def sumRange(self, left: int, right: int) -> int:
        return self.seg.range_query(left, right + 1)
