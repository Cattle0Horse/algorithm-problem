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


lower_vowel = "aeiou"
upper_vowel = "AEIOU"
vowel = lower_vowel + upper_vowel
to_chr = lambda x, a="a": chr(x + ord(a))
to_ord = lambda x, a="a": ord(x) - ord(a)
count_if = lambda func, arr: sum(1 for x in arr if func(x))
lower = lambda x: x.lower()
upper = lambda x: x.upper()
swapcase = lambda x: x.swapcase()
islower = lambda x: x.islower()
isupper = lambda x: x.isupper()
isdigit = lambda x: x.isdigit()
isalnum = lambda x: x.isalnum()  # 字母or数字
isalpha = lambda x: x.isalpha()  # 字母
is_lower_vowel = lambda x: x in lower_vowel
is_upper_vowel = lambda x: x in upper_vowel
isvowel = lambda x: x in vowel
is_even = lambda x: x % 2 == 0
is_odd = lambda x: x % 2 == 1

"""
123    ↖↑↗
456    ← o →
789    ↙↓↘
"""
direction_map = {
    "1": (-1, -1),
    "2": (-1, 0),
    "3": (-1, 1),
    "4": (0, -1),
    "5": (0, 0),
    "6": (0, 1),
    "7": (1, -1),
    "8": (1, 0),
    "9": (1, 1),
}


def get_directions(s: str) -> list[tuple[int, int]]:
    return [direction_map[x] for x in s]
