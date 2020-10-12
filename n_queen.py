from numpy import matrix

BOARD_SIZE = 8
EMPTY = "_"
VISITED = "*"


def print_board(board):
    print()
    for row in board:
        for cell in row:
            print(cell, end="")
        print()


def check_valid_move(board: list, point: tuple):
    """Check if the move is legal"""

    j, i = point

    def is_coordinate_valid(x, y):
        row_no = len(board) - 1
        return x < BOARD_SIZE and x >= 0 and y <= row_no and y >= 0

    # check for column (i.e. in vertical direction)
    for row in board:
        if row[i] == VISITED:
            return False

    # check diagonal (first)
    x, y = i, j
    while is_coordinate_valid(x, y):
        if board[y][x] == VISITED:
            return False
        x += 1
        y -= 1

    x, y = i, j
    while is_coordinate_valid(x, y):
        if board[y][x] == VISITED:
            return False
        x -= 1
        y += 1

    # check diagonal (second)
    x, y = i, j
    while is_coordinate_valid(x, y):
        if board[y][x] == VISITED:
            return False
        x -= 1
        y -= 1

    x, y = i, j
    while is_coordinate_valid(x, y):
        if board[y][x] == VISITED:
            return False
        x += 1
        y += 1

    return True


def n_queen_recursive(board: list, row_no: int = 0):
    if row_no == len(board):
        print_board(board)
        return

    row = board[row_no]
    for i in range(len(row)):
        if check_valid_move(board[: row_no + 1], (row_no, i)):
            board[row_no][i] = VISITED
            n_queen_recursive(board, row_no + 1)

            # reset row
            board[row_no][i] = EMPTY


if __name__ == "__main__":
    board = [[EMPTY] * BOARD_SIZE for _ in range(BOARD_SIZE)]
    n_queen_recursive(board)
