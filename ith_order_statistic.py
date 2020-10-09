# calculate ith order statistic in expected linear time

import random


def randomized_select(array, index):
    if len(array) == 1:
        return array[0]

    # also the number of elements before the pivot
    pivot_index = randomized_partition(array)

    if pivot_index == index:
        # the pivot value is the answer
        return array[pivot_index]
    elif index < pivot_index:
        new_array = array[:pivot_index]
        assert len(new_array) == pivot_index
        return randomized_select(new_array, index)
    else:
        new_index = index - pivot_index - 1
        new_array = array[pivot_index + 1 :]
        assert len(new_array) == len(array) - 1 - pivot_index
        return randomized_select(new_array, new_index)


def randomized_partition(array):
    """
    Randomly partition `array` after randomly selecting pivot element and returns
    index of pivot
    """
    # i = random.randint(0, len(array) - 1)
    i = 0
    if len(array) > 2:
        i = 2
    array[0], array[i] = array[i], array[0]
    # print("Pivot:", array[0])
    return partition(array)


def partition(array):
    """
    Partition using the first element as a pivot (inplace) and return the new
    index of pivot (i.e. location of the pivot)
    """
    pivot_index = 0
    pivot = array[pivot_index]
    # array[index] is same as pivot

    while pivot_index + 1 < len(array) and array[pivot_index + 1] < pivot:
        array[pivot_index + 1], array[pivot_index] = (
            array[pivot_index],
            array[pivot_index + 1],
        )
        pivot_index += 1
        assert array[pivot_index] == pivot
    return pivot_index


if __name__ == "__main__":
    # while True:
    #     array = list(map(int, input("Array: ").split()))
    #     index = int(input("Index you wish to find: "))
    #     print(randomized_select(array, index))

    array = [5, 4, 3, 2, 1, 0]
    assert randomized_select(array, 5) == 5
