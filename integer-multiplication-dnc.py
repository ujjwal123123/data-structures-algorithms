import time


def split_at(num: int, low_len: int):
    """
    Return (high, low)
    """
    snum = str(num)

    # so that we do not find substring of an empty string
    if num_len(snum) <= low_len:
        high = 0
    else:
        high = int(snum[:-low_len])

    low = int(snum[-low_len:])
    return high, low


def num_len(num: int):
    return len(str(num))


def multiply(numA: int, numB: int):
    """
    Calculate numA*numB using simple divide and conquer
    """
    length = max(num_len(numA), num_len(numB))
    half_length = length // 2

    if num_len(numA) == 1 or num_len(numB) == 1:
        return numA * numB

    highA, lowA = split_at(numA, half_length)
    highB, lowB = split_at(numB, half_length)

    high = multiply(highA, highB)
    mid = multiply(highA, lowB) + multiply(highB, lowA)
    low = multiply(lowA, lowB)

    return high * 10 ** (2 * half_length) + mid * 10 ** half_length + low


def karatsuba(numA: int, numB: int):
    """
    Calculate numA * numB using Karatsuba algorithm
    """
    length = max(num_len(numA), num_len(numB))
    half_length = length // 2

    if num_len(numA) == 1 or num_len(numB) == 1:
        return numA * numB

    highA, lowA = split_at(numA, half_length)
    highB, lowB = split_at(numB, half_length)

    high = karatsuba(highA, highB)
    mid = karatsuba(highA + lowA, highB + lowB)
    low = karatsuba(lowA, lowB)

    return high * 10 ** (2 * half_length) + (mid - low - high) * 10 ** half_length + low


if __name__ == "__main__":
    a, b = map(int, input().split())
    t0 = time.time()
    dnc_product = multiply(a, b)
    t1 = time.time()
    karatsuba_product = multiply(a, b)
    t2 = time.time()
    assert dnc_product == karatsuba_product
    assert dnc_product == a * b
    print(karatsuba_product)
    print("Karatsuba timing:", t2 - t1)
    print("dnc timing:", t1 - t0)
