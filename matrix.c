#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "matrix.h"

#define EPS 0.0000001
#define MAX_LENGTH 10

bool validate_input_as_uint(const char *input) {

    if (input == NULL)
        return false;

    if (input[0] == '\0') {
        printf("Empty character array.\n");
        return false;
    }

    if (MAX_LENGTH < strlen(input)) {
        printf("Input length is to large to be an unsigned integer.\n");
        return false;
    }

    if (input[0] == '-') {
        printf("Input is negative.\n");
        return false;
    }

    int i = 0;

    while (input[i] != '\0') {
        if (!isdigit(input[i++])) {
            printf("The input contains at least one non-numeric character.\n");
            return false;
        }
    }

    return true;

}

unsigned int parse_uint(const char *input) {

    return strtoul(input, NULL, 0);

}

Matrix *allocate_matrix(unsigned int row_num, unsigned int col_num) {

    if (row_num == 0 || col_num == 0) {
        printf("The sizes of the matrix must be greater than 0.\n");
        return NULL;
    }

    Matrix *matrix = (Matrix *) malloc(row_num * sizeof(Matrix));

    if (matrix == NULL) {
        printf("Unable to allocate memory.\n");
        return NULL;
    }

    matrix->row_num = row_num;
    matrix->col_num = col_num;

    matrix->matrix = (double **) malloc(row_num * sizeof(double *));

    for (int i = 0; i < row_num; i++) {

        matrix->matrix[i] = malloc(col_num * sizeof(double));

        if (matrix->matrix[i] == NULL) {

            printf("Unable to allocate memory.\n");

            for (int j = 0; j < i; j++)
                free(matrix->matrix[j]);

            free(matrix->matrix);
            matrix->matrix = NULL;
            free(matrix);
            matrix = NULL;

            return NULL;

        }

    }

    return matrix;

}

void initialize_matrix(Matrix *matrix) {

    if (matrix == NULL || matrix->row_num == 0 || matrix->col_num == 0)
        return;

    printf("Please type the elements of the matrix (%dx%d)!\n", matrix->row_num, matrix->col_num);

    for (int i = 0; i < matrix->row_num; i++) {

        for (int j = 0; j < matrix->col_num; j++) {

            printf("Row: %d Column: %d: \n", i, j);

            if (scanf("%lf", &matrix->matrix[i][j]) != 1) {
                printf("Invalid input. Try again!\n");
                fflush(stdin);
                j--;
            }

        }

    }

    printf("\nInitialization completed.\n");

}

void print_matrix(const Matrix *matrix) {

    if (matrix == NULL)
        return;

    printf("\nThe matrix is:\n\n");

    for (int i = 0; i < matrix->row_num; i++) {
        for (int j = 0; j < matrix->col_num; j++) {
            printf("%lf\t", matrix->matrix[i][j]);
        }
        printf("\n");
    }

}

void set_element(Matrix *matrix, unsigned int row, unsigned int col, double value) {

    if (matrix == NULL)
        return;

    if (row == 0 || col == 0 || matrix->row_num <= row || matrix->col_num <= col) {
        printf("Index is not valid.\n");
        return;
    }

    matrix->matrix[row][col] = value;

}

void swap(double *a, double *b) {

    double temp = *a;
    *a = *b;
    *b = temp;

}

Matrix *transpose_new(Matrix *matrix) {

    if (matrix == NULL)
        return NULL;

    Matrix *result = allocate_matrix(matrix->col_num, matrix->row_num);

    if (result == NULL)
        return NULL;

    for (int i = 0; i < result->row_num; i++)
        for (int j = 0; j < result->col_num; j++)
            result->matrix[i][j] = matrix->matrix[j][i];

    return result;

}

void transpose_sq_matrix(Matrix *matrix) {

    if (matrix == NULL)
        return;

    if (matrix->row_num == 0 || matrix->col_num == 0) {
        printf("The sizes of the matrix must be greater than 0.\n");
        return;
    }

    if (matrix->row_num != matrix->col_num) {
        printf("The input matrix is not a square matrix.\n");
        return;
    }

    for (int i = 0; i < matrix->row_num; i++)
        for (int j = i + 1; j < matrix->col_num; j++)
            swap(&matrix->matrix[i][j], &matrix->matrix[j][i]);

}


Matrix *add_matrices_new(const Matrix *a, const Matrix *b) {

    if (a == NULL || b == NULL)
        return NULL;

    if (a->row_num == 0 || a->col_num == 0 || b->row_num == 0 || b->col_num == 0) {
        printf("The sizes of the matrices must be greater than 0.\n");
        return NULL;
    }

    if (a->row_num != b->row_num || a->col_num != b->col_num) {
        printf("The input matrices have different sizes.\n");
        return NULL;
    }

    Matrix *result = allocate_matrix(a->row_num, a->col_num);

    if (result == NULL) {
        return NULL;
    }

    for (int i = 0; i < a->row_num; i++)
        for (int j = 0; j < b->col_num; j++)
            result->matrix[i][j] = a->matrix[i][j] + b->matrix[i][j];

    return result;

}

void add_matrices(Matrix *a, const Matrix *b) {

    if (a == NULL || b == NULL)
        return;

    if (a->row_num == 0 || a->col_num == 0 || b->row_num == 0 || b->col_num == 0) {
        printf("The sizes of the matrices must be greater than 0.\n");
        return;
    }

    if (a->row_num != b->row_num || a->col_num != b->col_num) {
        printf("The input matrices have different sizes.\n");
        return;
    }

    for (int i = 0; i < a->row_num; i++)
        for (int j = 0; j < b->col_num; j++)
            a->matrix[i][j] += b->matrix[i][j];

}

Matrix *subtract_matrix_new(const Matrix *a, const Matrix *b) {

    if (a == NULL || b == NULL)
        return NULL;

    if (a->row_num == 0 || a->col_num == 0 || b->row_num == 0 || b->col_num == 0) {
        printf("The sizes of the matrices must be greater than 0.\n");
        return NULL;
    }

    if (a->row_num != b->row_num || a->col_num != b->col_num) {
        printf("The input matrices have different sizes.\n");
        return NULL;
    }

    Matrix *result = allocate_matrix(a->row_num, a->col_num);

    for (int i = 0; i < a->row_num; i++)
        for (int j = 0; j < b->col_num; j++)
            result->matrix[i][j] = a->matrix[i][j] - b->matrix[i][j];

    return result;

}

void subtract_matrix(Matrix *a, const Matrix *b) {

    if (a == NULL || b == NULL)
        return;

    if (a->row_num == 0 || a->col_num == 0 || b->row_num == 0 || b->col_num == 0) {
        printf("The sizes of the matrices must be greater than 0.\n");
        return;
    }

    if (a->row_num != b->row_num || a->col_num != b->col_num) {
        printf("The input matrices have different sizes.\n");
        return;
    }

    for (int i = 0; i < a->row_num; i++)
        for (int j = 0; j < b->col_num; j++)
            a->matrix[i][j] -= b->matrix[i][j];

}

Matrix *multiplies_by_value_new(const Matrix *matrix, double value) {

    if (matrix == NULL)
        return NULL;

    if (matrix->row_num == 0 || matrix->col_num == 0) {
        printf("The sizes of the matrix must be greater than 0.\n");
        return NULL;
    }

    Matrix *result = allocate_matrix(matrix->row_num, matrix->col_num);

    if (result == NULL) {
        return NULL;
    }

    for (int i = 0; i < matrix->row_num; i++)
        for (int j = 0; j < matrix->col_num; j++)
            result->matrix[i][j] = matrix->matrix[i][j] * value;

    return result;

}

void multiplies_by_value(Matrix *matrix, double value) {

    if (matrix == NULL)
        return;

    if (matrix->row_num == 0 || matrix->col_num == 0) {
        printf("The sizes of the matrix must be greater than 0.\n");
        return;
    }

    for (int i = 0; i < matrix->row_num; i++)
        for (int j = 0; j < matrix->col_num; j++)
            matrix->matrix[i][j] *= value;

}

Matrix *multiplies_matrices(const Matrix *a, const Matrix *b) {

    if (a == NULL || b == NULL)
        return NULL;

    if (a->row_num == 0 || a->col_num == 0 || b->row_num == 0 || b->col_num == 0) {
        printf("The sizes of the matrices must be greater than 0.\n");
        return NULL;
    }

    if (a->col_num != b->row_num) {
        printf("The input matrices are not compatible.\n");
        return NULL;
    }

    Matrix *result = allocate_matrix(a->row_num, b->col_num);

    if (result == NULL) {
        return NULL;
    }

    for (int i = 0; i < result->row_num; i++) {

        for (int j = 0; j < result->col_num; j++) {

            result->matrix[i][j] = 0;

            for (int k = 0; k < a->col_num; k++) {

                result->matrix[i][j] += a->matrix[i][k] * b->matrix[k][j];

            }

        }

    }

    return result;

}


bool equals(const Matrix *a, const Matrix *b) {

    if (a == NULL || b == NULL)
        return false;

    if (a->row_num != b->row_num || a->col_num != b->col_num)
        return false;

    for (int i = 0; i < a->row_num; i++)
        for (int j = 0; j < b->col_num; j++)
            if (fabs(a->matrix[i][j] - b->matrix[i][j]) >= EPS)
                return false;

    return true;

}

void free_matrix(Matrix *matrix) {

    if (matrix == NULL)
        return;

    for (int i = 0; i < matrix->row_num; i++)
        free(matrix->matrix[i]);

    free(matrix->matrix);
    matrix->matrix = NULL;
    free(matrix);
    matrix = NULL;

}