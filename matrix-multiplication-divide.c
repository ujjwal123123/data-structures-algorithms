#include "matrix.c"
#include <stdio.h>

int **muliply_matrix_naive(int **A, int height_A, int width_A,
                           int **B, int height_B, int width_B) {
    if (width_A != height_B) {
        return NULL;
    }

    int **product = (int **)calloc(height_A, sizeof(int *));

    for (int j = 0; j < height_A; j++) {
        product[j] = (int *)calloc(width_A, sizeof(int));
        for (int i = 0; i < width_B; i++) {
            int result = 0;
            for (int k = 0; k < width_A; k++) {
                result += A[j][k] * B[k][i];
            }
            product[j][i] = result;
        }
    }
    return product;
}

// helper function for recurcivly square matrix multiplication for use
// in divide and conquer method
void matrix_multiply_helper(int **Product, int **A, int **B, int size,
                            int A_y, int A_x, int B_y, int B_x) {
    // base case
    if (size == 1) {
        Product[A_y][B_x] += A[A_y][A_x] * B[B_y][B_x];
        return;
    }

    int s = size / 2;

    // C partition top left
    matrix_multiply_helper(Product, A, B, s, A_y, A_x, B_y, B_x);
    matrix_multiply_helper(Product, A, B, s, A_y, A_x + s, B_y + s,
                           B_x);
    // C partition top right
    matrix_multiply_helper(Product, A, B, s, A_y, A_x, B_y, B_x + s);
    matrix_multiply_helper(Product, A, B, s, A_y, A_x + s, B_y + s,
                           B_x + s);
    // C partition bottom left
    matrix_multiply_helper(Product, A, B, s, A_y + s, A_x, B_y, B_x);
    matrix_multiply_helper(Product, A, B, s, A_y + s, A_x + s,
                           B_y + s, B_x);
    // C partition bottom right
    matrix_multiply_helper(Product, A, B, s, A_y + s, A_x, B_y,
                           B_x + s);
    matrix_multiply_helper(Product, A, B, s, A_y + s, A_x + s,
                           B_y + s, B_x + s);
}

int **square_matrix_multiply_recusive(int **A, int **B, int size) {
    int **Product = alloc_matrix(size, size);
    matrix_multiply_helper(Product, A, B, size, 0, 0, 0, 0);
    return Product;
}

int main() {
    int size = 4;
    int **A = get_matrix(size, size);
    print_matrix(A, size, size);
    int **B = get_matrix(size, size);
    print_matrix(B, size, size);

    int **C = square_matrix_multiply_recusive(A, B, size);
    print_matrix(C, size, size);
}
