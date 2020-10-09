# find minimum and maximum element in an array in 3*floor(n/2)


def pairwise(it):
    it = iter(it)
    while True:
        try:
            yield next(it), next(it)
        except StopIteration:
            # no more elements in the iterator
            return


def min_max(array):
    minimum = array[0]
    maximum = array[0]

    for x, y in pairwise(array[len(array) % 1 :]):
        if x > y:
            minimum = min(minimum, y)
            maximum = max(maximum, x)
        else:
            minimum = min(minimum, x)
            maximum = max(maximum, y)

    return (minimum, maximum)


array = list(map(int, input().split()))
print(min_max(array))
