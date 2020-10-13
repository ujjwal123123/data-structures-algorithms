#include <iostream>
#include <vector>
using namespace std;

int check_validity(vector<unsigned long> board) {
    // check columns
    for (unsigned long i = 0; i < board.size() - 1; i++) {
        if (board[i] == board.back()) {
            return 1;
        }

        if (board[i] - board.back() == board.size() - i - 1) {
            // eg {1, 0}
            return 2;
        }

        if (board.back() - board[i] == board.size() - i - 1) {
            // eg {0, 1}
            return 3;
        }
    }

    return 0;
}

void print_board(vector<unsigned long> board) {
    for (unsigned long ele : board) {
        cout << ele << " ";
    }
    cout << endl;
}

void try_permutations(vector<unsigned long> board,
                      unsigned long board_size) {
    // base case
    if (check_validity(board)) {
        return;
    }
    if (board_size == board.size()) {
        if (check_validity(board) == 0) {
            cout << "Solution: ";
            print_board(board);
        }
        return;
    }

    vector<unsigned long> temp_vector = board;
    temp_vector.push_back(-1);
    for (unsigned long i = 0; i < board_size; i++) {
        temp_vector.back() = i;
        try_permutations(temp_vector, board_size);
    }
}

int main() {
    vector<unsigned long> board;
    try_permutations(board, 8);
}
