"""
https://hzhao.me/2019/08/16/python-leetcode-trick/
https://support.leetcode.com/hc/en-us/articles/360011833974-What-are-the-environments-for-the-programming-languages
Leetcode environments(2024-09-02):
    Python 3.11
    Python 2.7.12
    C++23 clang17 
    Java21 OpenJDK21
"""

from operator import *  # https://docs.python.org/zh-cn/3.12/library/operator.html
import sys
import functools  # https://docs.python.org/zh-cn/3.12/library/functools.html
import collections  # https://docs.python.org/zh-cn/3.12/library/collections.html
import itertools  # https://docs.python.org/zh-cn/3.12/library/itertools.html
import heapq  # https://docs.python.org/zh-cn/3.12/library/heapq.html
import bisect  # https://docs.python.org/zh-cn/3.12/library/bisect.html

# import array  # https://docs.python.org/zh-cn/3.12/library/array.html
import math  # https://docs.python.org/zh-cn/3.12/library/math.html
import sortedcontainers  # https://grantjenks.com/docs/sortedcontainers/

# seasons = ['Spring', 'Summer', 'Fall', 'Winter']

# print(list(enumerate(seasons[1:], 1)))


def is_upper_version(minor: int, major: int = 3) -> bool:
    return sys.version_info >= (major, minor)


"""builtins
"""
# int char 互相转换
print(ord("a"))
print(chr(97))
arr = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
print(list(filter(lambda x: x % 2 == 0, arr)))
print(sum(arr, start=5))

"""functools
['update_wrapper', 'wraps', 'WRAPPER_ASSIGNMENTS', 'WRAPPER_UPDATES',
    'total_ordering', 'cache', 'cmp_to_key', 'lru_cache', 'reduce',
    'partial', 'partialmethod', 'singledispatch', 'singledispatchmethod',
    'cached_property']
"""
print(functools.reduce(add, arr, 5))


def my_add(a: int, b: int) -> int:
    return a + b


# 参数绑定
my_add2 = functools.partial(my_add, b=2)
print(my_add2(1))


# 函数重载
@functools.singledispatch
def my_func(a: int):
    print("int", a)


@my_func.register
def _(a: str):
    print("str", a)


if is_upper_version(11):

    @my_func.register
    def _(a: list | set):  # python3.11开始
        print("list|set", a)


my_func(1)
my_func("abc")
my_func([1, 2, 3])
my_func({1, 2, 3, 4, 4})
print(my_func.registry.keys())

"""itertools
"""
# 无穷迭代器
itertools.count(10, 2)
# 笛卡尔积(相当于嵌套for循环)
print(list(itertools.product("abc", "123", repeat=1)))
print(list(itertools.product("abc", "123", "xyz")))
# 排列(不允许重复选择)
print(list(itertools.permutations("cab", 2)))
# 组合(不允许重复选择)
print(list(itertools.combinations("cab", 2)))
# 组合(允许重复选择)
print(list(itertools.combinations_with_replacement("cab", 2)))
print(list(itertools.accumulate(arr, mul)))
if is_upper_version(12):
    # 每n个元素作为一个元组，最后一个元组可能少于n
    print(list(itertools.batched("ABCDEFG", 3)))
# 将多个可迭代对象作为参数，返回一个迭代器
print(list(itertools.chain("ABC", "abc")))
# 同上，只不过需要本身是一个可迭代对象
print(list(itertools.chain.from_iterable(["ABC", "abc"])))
# 选择对应列表为真的元素
print(list(itertools.compress("ABCDEF", [1, 0, 1, 0, 1, 1])))  # A C E F
# 丢弃为真的元素，直到第一个为假
print(list(itertools.dropwhile(lambda x: x < 5, [1, 4, 6, 3, 8])))  # 6 3 8
# 丢弃所有为真的元素
print(list(itertools.filterfalse(lambda x: x < 5, [1, 4, 6, 3, 8])))  # 6 8
# 返回所有为真的元素
print(list(itertools.takewhile(lambda x: x < 5, [1, 4, 6, 3, 8])))  # 1 4
# 返回连续的二元组
print(list(itertools.pairwise("ABCDEFG")))  # AB BC CD DE EF FG
# 连续的相同元素作为一组 (基准元素，元素迭代器)
print([k for k, g in itertools.groupby("AAAABBBCCDAABBB")])  # A B C D A B
print([list(g) for k, g in itertools.groupby("AAAABBBCCD")])  # AAAA BBB CC D
# 类似于[start:stop:step]切片，只不过返回迭代器
itertools.islice("ABCDEFG", 2)  # A B
itertools.islice("ABCDEFG", 2, 4)  # C D
itertools.islice("ABCDEFG", 2, None)  # C D E F G
itertools.islice("ABCDEFG", 0, None, 2)  # A C E G

"""collections
"""
# ChainMap
baseline = {"music": "bach", "art": "rembrandt"}
adjustments = {"art": "van gogh", "opera": "carmen"}
# 合并两个字典等同于 print(baseline | adjustments) Python3.9
print(collections.ChainMap(baseline, adjustments))
# Counter (按首次插入顺序排序)
c = collections.Counter("bcdeabcdabcaba")
print(c)  # Counter({'b': 4, 'a': 4, 'c': 3, 'd': 2, 'e': 1})
# 按顺序取出n组
print(c.most_common(3))  # [('b', 4), ('a', 4), ('c', 3)]
# 按数量返回每个元素，0与负数将忽略
c = collections.Counter(a=4, b=2, c=0, d=-2)
print(list(c.elements()))  # ['a', 'a', 'a', 'a', 'b', 'b']
# 计数值做差
c = collections.Counter(a=4, b=2, c=0, d=-2)
d = collections.Counter(a=1, b=2, c=3, d=4)
c.subtract(d)
print(c)  # Counter({'a': 3, 'b': 0, 'c': -3, 'd': -6})
# 总计数值
c = collections.Counter(a=10, b=5, c=0)
print(c.total())  # 15
# 加入元素
c.update(["a", "a", "a", "c"])
print(c)  # Counter({'a': 13, 'c': 1})
# 基本运算
c = collections.Counter(a=3, b=1)
d = collections.Counter(a=1, b=2)
print(c + d)  # add two counters together:  c[x] + d[x]
print(c - d)  # subtract (keeping only positive counts)
print(c & d)  # intersection:  min(c[x], d[x])
print(c | d)  # union:  max(c[x], d[x])
print(c == d)  # equality:  c[x] == d[x]
print(c <= d)  # inclusion:  c[x] <= d[x]

# deque
d = collections.deque("ghi")  # make a new deque with three items
for elem in d:  # iterate over the deque's elements
    print(elem.upper())
d.append("j")  # add a new entry to the right side
d.appendleft("f")  # add a new entry to the left side
d.pop()  # return and remove the rightmost item
d.popleft()  # return and remove the leftmost item
d[0]  # peek at leftmost item
d[-1]  # peek at rightmost item
"h" in d  # search the deque
d.extend("jkl")  # add multiple elements at once
d.rotate(1)  # right rotation
d.rotate(-1)  # left rotation
collections.deque(reversed(d))  # make a new deque in reverse order
d.clear()  # empty the deque
try:
    d.pop()  # cannot pop from an empty deque
except IndexError:
    print("cannot pop from an empty deque")
d.extendleft("abc")  # extendleft() reverses the input order

# defaultdict
# 提供字典默认值
s = [("yellow", 1), ("blue", 2), ("yellow", 3), ("blue", 4), ("red", 1)]
d = collections.defaultdict(list)
for k, v in s:
    d[k].append(v)
print(d.items())
# 自定义默认值
d = collections.defaultdict(lambda: 100)
for k, v in s:
    d[k] += v
print(d.items())


# namedtuple
# todo:
# UserDict，UserList, UserString
# 可以通过.data方便的获取原始dict，list，str数据，不需要手动转换了
class MyDict(collections.UserDict):
    ...
    # def __init__(self, *args, **kwargs):
    #     super().__init__(*args, **kwargs)
    #     print("MyDict initialized with:", args, kwargs)

    # def __setitem__(self, key, value):
    #     super().__setitem__(key, value)
    #     print(f"Item set: {key} = {value}")


# 使用自定义的 MyDict 类
my_dict = MyDict({"a": 1, "b": 2})
my_dict["c"] = 3
print(my_dict.data)

"""heapq
"""
arr = [40, 0, 3, 5, 10, 3, 4, 11, 20, 30, 2]
# 初始化堆
heapq.heapify(arr)
print(arr)
# 弹出最小值
print(heapq.heappop(arr))
# 访问最小值
print(arr[0])
# 插入一个元素
heapq.heappush(arr, 1)
# 先插入插入再弹出最小元素
print(heapq.heappushpop(arr, -1))
# 先弹出再插入(原理是替换堆顶元素，然后向下调整)
print(heapq.heapreplace(arr, -2))
# 其他三个通用函数
# 合并多个有序输入(升序)
print(list(heapq.merge([1, 3, 5], [2, 4, 6], [0, 7, 8])))
# 合并读个有序输入(倒序)
print(list(heapq.merge([5, 3, 1], [6, 4, 2], [8, 7, 0], reverse=True)))
arr = [40, 0, 3, 5, 10, 3, 4, 11, 20, 30, 2]
n = 3
# 返回前n个大的元素
print(list(heapq.nlargest(n, arr)))
# 返回前n个小的元素
print(list(heapq.nsmallest(n, arr)))

"""bisect
相应地，这些函数绝不会调用 __eq__() 方法来确定是否找到特定值。
相反，这些函数只会调用 __lt__() 方法并将返回一个数组的值之间的插入点。
params = (a, x, lo=0, hi=len(a), *, key=None)
若key为None，则直接比较元素
bisect_left:
    all(key(elem) < x for elem in a[lo : ip]) is True
bisect_right / bisect:
    all(elem <= x for elem in a[lo : ip]) is True (调用的是 x < key(elem))
insort_left:
    在bisect_left后，执行插入操作。
insort_right / insort:
    在bisect_right后，执行插入操作。
"""
arr = [0, 2, 4, 6, 8, 10, 10, 10, 10, 12, 14, 16, 18]
print(bisect.bisect_left(arr, 10))
print(bisect.bisect_right(arr, 10))
arr.reverse()
print(arr)
# 借助False与True的比较，找到降序数组中第一个小于等于10数的位置
# like: [False, False, False, False, True, True, True, True, True, True, True, True]
print(bisect.bisect_left(range(len(arr)), True, key=lambda x: arr[x] <= 10))
# 或负数表示
print(bisect.bisect_left(arr, -10, key=lambda x: -x))
print(bisect.bisect_left(arr, -10, key=neg))
