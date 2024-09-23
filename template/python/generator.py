from typing import Generator


def permutation(chars: str | list[str], n: int) -> Generator[str, None, None]:
    """从chars中选出n个元素(每个元素可以多次选择)，生成长度为n的排列

    Args:
        chars (str | list[str]): 无重复元素的字符序列
    """
    # 不允许重复字符
    assert len(chars) != 0 and len(chars) == len(set(chars)) and n >= 0
    if n == 0:
        yield ""
    else:
        path: list[str] = []

        def dfs(i: int) -> Generator[str, None, None]:
            if i == n:
                yield "".join(path)
                return
            for c in chars:
                path.append(c)
                yield from dfs(i + 1)
                path.pop()

        yield from dfs(0)


def palindrome(chars: str | list[str], n: int) -> Generator[str, None, None]:
    """从chars中选出n个字符，生成长度为n的回文串"""
    for s in permutation(chars, (n + 1) >> 1):
        yield s + s[::-1][n & 1 :]


def palindrome_digits(n: int) -> Generator[str, None, None]:
    """生成长度为n的回文数字串(不含前导0)"""
    assert n >= 0
    if n == 0:
        yield ""
    elif n == 1:
        yield from "0123456789"
    else:
        base = 10 ** ((n - 1) // 2)
        for x in range(base, base * 10):
            s = str(x)
            yield s + s[::-1][n & 1 :]
