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
    """
    Check if the move is legal
    """
    j, i = point
    row_no = len(board) - 1

    def is_coordinate_valid(x, y):
        if x < BOARD_SIZE and x >= 0 and y <= row_no and y >= 0:
            return True
        return False

    # check for column (i.e. in vertical direction)
    for row in board:
        if row[i] == VISITED:
            # print("Not valid")
            return False

    # check diagonal (first)
    x, y = i, j
    while is_coordinate_valid(x, y):
        if board[y][x] == VISITED:
            # print("Not valid")
            return False
        x += 1
        y -= 1

    x, y = i, j
    while is_coordinate_valid(x, y):
        if board[y][x] == VISITED:
            # print("Not valid")
            return False
        x -= 1
        y += 1

    # check diagonal (second)
    x, y = i, j
    while is_coordinate_valid(x, y):
        if board[y][x] == VISITED:
            # print("Not valid")
            return False
        x -= 1
        y -= 1

    x, y = i, j
    while is_coordinate_valid(x, y):
        if board[y][x] == VISITED:
            # print("Not valid")
            return False
        x += 1
        y += 1

    return True


def n_queen_recursive(board: list, row_no: int = 0):
    if row_no == len(board):
        print_board(board)
        print("end")
        return

    j = row_no

    row = board[row_no]
    for i in range(len(row)):
        if check_valid_move(board[: row_no + 1], (j, i)):
            board[j][i] = VISITED
            n_queen_recursive(board, row_no + 1)

            # reset row
            board[j][i] = EMPTY


if __name__ == "__main__":
    board = [[EMPTY] * BOARD_SIZE for i in range(BOARD_SIZE)]
    n_queen_recursive(board)
