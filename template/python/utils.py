def digit_sum(x: int) -> int:
    if x < 0:
        return -digit_sum(-x)
    s = 0
    while x != 0:
        s += x % 10
        x //= 10
    return s


def digit_reverse(x: int) -> int:
    if x < 0:
        return -digit_reverse(-x)
    s = 0
    while x != 0:
        s = s * 10 + x % 10
        x //= 10
    return s


to_chr = lambda x, a="a": chr(x + ord(a))
to_ord = lambda x, a="a": ord(x) - ord(a)
