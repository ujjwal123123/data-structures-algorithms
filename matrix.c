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

int **alloc_matrix(int height, int width) {
    int **matrix = (int **)calloc(height, sizeof(int *));
    for (int j = 0; j < height; j++) {
        matrix[j] = (int *)calloc(width, sizeof(int));
    }
    return matrix;
}

void free_matrix(int **matrix, int height, int width) {
    for (int j = 0; j < height; j++) {
        free(matrix[j]);
    }
    free(matrix);
}

int **matrix_add(int **A, int **B, int height, int width) {
    int **sum = (int **)calloc(height, sizeof(int *));
    for (int j = 0; j < height; j++) {
        sum[j] = (int *)calloc(width, sizeof(int));
        for (int i = 0; i < width; i++) {
            sum[j][i] = A[j][i] + B[j][i];
        }
    }
    return sum;
}

// returns A - B
int **matrix_sub(int **A, int **B, int height, int width) {
    int **diff = (int **)calloc(height, sizeof(int *));
    for (int j = 0; j < height; j++) {
        diff[j] = (int *)calloc(width, sizeof(int));
        for (int i = 0; i < width; i++) {
            diff[j][i] = A[j][i] - B[j][i];
        }
    }
    return diff;
}

int **add(int **A, int **B, int size, int A_y, int A_x, int B_y,
          int B_x) {
    int **sum = alloc_matrix(size, size);
    for (int j = 0; j < size; j++) {
        for (int i = 0; i < size; i++) {
            sum[j][i] = A[A_y + j][A_x + i] + B[B_y + j][B_y + i];
        }
    }
    return sum;
}

// returns A - B
int **sub(int **A, int **B, int size, int A_y, int A_x, int B_y,
          int B_x) {
    int **diff = alloc_matrix(size, size);
    for (int j = 0; j < size; j++) {
        for (int i = 0; i < size; i++) {
            diff[j][i] = A[A_y + j][A_x + i] - B[B_y + j][B_y + i];
        }
    }
    return diff;
}
