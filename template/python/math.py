from typing import Generator


def is_prime(n: int) -> bool:
    """质数判断"""
    if n <= 1:
        return False
    for i in range(2, int(n**0.5) + 1):
        if n % i == 0:
            return False
    return True


def get_factor(n: int) -> Generator[tuple[int, int], None, None]:
    """质因子分解"""
    i = 2
    while i * i <= n:
        if n % i == 0:
            cnt = 0
            while n % i == 0:
                n //= i
                cnt += 1
            yield i, cnt
        i += 1
    if n != 1:
        yield n, 1


def sieve(n: int) -> list[bool]:
    """埃氏筛[0, n]"""
    if n == 0:
        return [False]
    is_prime = [True] * (n + 1)
    is_prime[0] = is_prime[1] = False
    for i in range(2, int(n**0.5) + 1):
        if is_prime[i]:
            for j in range(i * i, n + 1, i):
                is_prime[j] = False
    return is_prime


def sieve_with_primes(n: int) -> tuple[list[bool], list[int]]:
    """埃氏筛[0, n]"""
    if n == 0:
        return [False], []
    is_prime = [True] * (n + 1)
    primes = []
    is_prime[0] = is_prime[1] = False
    for i in range(2, n + 1):
        if is_prime[i]:
            primes.append(i)
            for j in range(i * i, n + 1, i):
                is_prime[j] = False
    return is_prime, primes


def sieve_euler(n: int) -> tuple[list[bool], list[int]]:
    """欧拉筛[0, n]"""
    if n == 0:
        return [False], []
    is_prime = [True] * (n + 1)
    primes = []
    is_prime[0] = is_prime[1] = False
    for i in range(2, n + 1):
        if is_prime[i]:
            primes.append(i)
        for p in primes:
            if p * i > n:
                break
            is_prime[p * i] = False
            if i % p == 0:
                break
    return is_prime, primes
