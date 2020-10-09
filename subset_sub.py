def find_subset(array, required_sum, selected=[]):
    """
    Return list of subsets which product sum of required_sum
    """
    # base case
    if required_sum < 0 or not array:
        return False
    elif required_sum == 0:
        return [selected]

    result = []

    # include the first element
    result1 = find_subset(array[1:], required_sum - array[0], selected + [array[0]])
    if result1:
        result += result1

    # do not include the first element
    result2 = find_subset(array[1:], required_sum, selected)
    if result2:
        result += result2

    return result


if __name__ == "__main__":
    array = [1, 2, 3, 4, 5]
    required_sum = 10
    print(find_subset(array, required_sum))
