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


def minimize_cost(memo: list, start: int, end: int):
    min_cost = float("inf")
    print("start:", start, "end:", end, end=" ")
    for mid in range(start, end):
        # do not include start and end
        temp_cost = (
            memo[start][mid]
            + memo[mid + 1][end]
            + matrices[start].rows * matrices[mid].columns * matrices[end].columns
        )
        min_cost = min(temp_cost, min_cost)
    print(min_cost, matrices[start], matrices[end])
    return min_cost


def solve(memo):
    for diagonal_index in range(1, len(memo)):
        # we need to fill len(m) - 1 diagonals
        # no need to 0th diagonal (which shall remain 0)
        point = Point(y=diagonal_index, x=0)
        for _ in range(len(memo) - diagonal_index):
            print(point, end="  ")
            assert point.x < len(memo) and point.y < len(memo)
            assert point.x < point.y
            memo[point.x][point.y] = minimize_cost(memo, point.x, point.y)
            point += Point(y=1, x=1)
            # print(np.matrix(memo))
        print()

    return memo[0][-1]


if __name__ == "__main__":
    matrix_count = int(input())
    matrices = get_matrices(matrix_count)
    print(matrices)

    # initialize the memo
    memo = [[float("inf")] * matrix_count for _ in range(matrix_count)]
    for i, row in enumerate(memo):
        row[i] = 0

    print(solve(memo))
