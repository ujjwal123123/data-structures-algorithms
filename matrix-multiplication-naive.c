#include <malloc.h>
#include <stdio.h>

void print_matrix(int **matrix, int height, int width) {
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            printf("%3d ", matrix[j][i]);
        }
        printf("\n");
    }
}

int **get_matrix(int height, int width) {
    int **matrix = (int **)calloc(height, sizeof(int *));
    for (int j = 0; j < height; j++) {
        matrix[j] = (int *)calloc(width, sizeof(int));
        for (int i = 0; i < width; i++) {
            scanf(" %d", &matrix[j][i]);
        }
    }
    return matrix;
}

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

int main() {
    int height_A, width_A;
    scanf(" %d %d", &height_A, &width_A);
    printf("\n");

    int **matrix_A = get_matrix(height_A, width_A);
    print_matrix(matrix_A, height_A, width_A);
    printf("\n");

    int height_B, width_B;
    scanf(" %d %d", &height_B, &width_B);
    printf("\n");

    int **matrix_B = get_matrix(height_B, width_B);
    print_matrix(matrix_B, height_B, width_B);
    printf("\n");

    int **product = muliply_matrix_naive(matrix_A, height_A, width_A,
                                         matrix_B, height_B, width_B);

    printf("\n");
    print_matrix(product, height_A, width_B);
}
