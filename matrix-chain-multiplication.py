import numpy as np


class matrix_dimensions:
    """Class for representing dimensions of a matrix"""

    def __init__(self, columns, rows):
        self.columns = columns
        self.rows = rows

    def __repr__(self):
        # representing using rows*columns
        return f"{self.rows}*{self.columns}"


class Point:
    """What did you think? Just a point with x and y coordinate"""

    def __init__(self, y, x):
        self.y = y
        self.x = x

    def __add__(self, other):
        self.x += other.x
        self.y += other.y
        return self

    def __repr__(self):
        return f"x: {self.x}, y: {self.y}"


def to_row_column(start, end):
    # column : start
    # row : end
    if end < start:
        raise ValueError
    row, column = end, start
    assert column <= row
    return end, start


class Memo:
    """Just a 2d memo"""

    def __init__(self, size):
        self.matrix = [[0] * matrix_count for _ in range(matrix_count)]
        for i, row in enumerate(self.matrix):
            row[i] = 0

    def __repr__(self):
        return str(np.matrix(self.matrix))

    def __len__(self):
        return len(self.matrix)

    def get(self, start, end):
        if end < start or end >= len(self):
            raise ValueError
        row, column = to_row_column(start, end)
        return self.matrix[row][column]

    def set(self, start, end, value):
        if end < start or end >= len(self):
            raise ValueError
        row, column = to_row_column(start, end)
        self.matrix[row][column] = value

    def result(self):
        return self.get(0, len(self) - 1)


def get_matrices(matrix_count):
    matrices = []
    for _ in range(matrix_count):
        columns, rows = map(int, input().split())
        matrices.append(matrix_dimensions(rows, columns))
    return matrices


#   1   2   3   4   5 x /y
# ---------------------
# | 0 |   |   |   |   |  1
# ---------------------
# |   | 0 |   |   |   |  2
# ---------------------
# |   |   | 0 |   |   |  3
# ---------------------
# |   |   |   | 0 |   |  4
# ---------------------
# | a |   |   |   | 0 |  5
# ---------------------
# Mulitplying from matrices[i] to matrices[j] (inclusive)
# or multiplying matrices from matrices[point.x] to matrices[point.y] (inclusive)


def minimize_cost(start: int, end: int):
    min_cost = float("inf")
    for mid in range(start, end):
        # do not include start and end
        temp_cost = (
            memo.get(start, mid)
            + memo.get(mid + 1, end)
            + matrices[start].rows * matrices[mid].columns * matrices[end].columns
        )
        min_cost = min(temp_cost, min_cost)
    return min_cost


def solve(memo):
    for diff in range(1, len(memo)):
        start, end = 0, diff
        while end < len(memo):
            memo.set(start, end, minimize_cost(start, end))
            start, end = start + 1, end + 1

    return memo.result()


if __name__ == "__main__":
    matrix_count = int(input())
    matrices = get_matrices(matrix_count)  # dimensions of matrices

    # initialize the memo
    memo = Memo(matrix_count)

    print(solve(memo))
