# calculate ith order statistic in expected linear time

import random


def randomized_select(array, index):
    if len(array) == 1:
        return array[0]

    # also the number of elements before the pivot
    pivot_index = randomized_partition(array)

    if pivot_index == index:
        return array[pivot_index]
    elif index < pivot_index:
        new_array = array[:pivot_index]
        return randomized_select(new_array, index)
    else:
        new_index = index - pivot_index - 1
        new_array = array[pivot_index + 1 :]
        return randomized_select(new_array, new_index)


def randomized_partition(array):
    """
    Randomly partition `array` after randomly selecting pivot element and returns
    index of pivot
    """
    i = random.randint(0, len(array) - 1)
    array[i], array[-1] = array[-1], array[i]
    return partition(array)


def partition(array):
    """
    Partition using the last element as a pivot (inplace) and return the new
    index of pivot (i.e. location of the pivot)
    """
    # TODO: Understand this function
    pivot = array[-1]
    i = 0
    for j in range(0, len(array)):
        if array[j] < pivot:
            array[i], array[j] = array[j], array[i]
            i += 1
    array[i], array[-1] = array[-1], array[i]
    return i


if __name__ == "__main__":
    while True:
        array = list(map(int, input("Array: ").split()))
        index = int(input("Index you wish to find: "))
        print(randomized_select(array, index))
