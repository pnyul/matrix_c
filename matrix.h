#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <stdbool.h>

typedef struct matrix {
    unsigned int row_num;
    unsigned int col_num;
    double **matrix;
} Matrix;

//checks null-terminated input for correctness as an unsigned integer
bool validate_input_as_uint(const char *input);

//converts array of characters to unsigned integer
unsigned int parse_uint(const char *input);

//allocates memory for matrix of the given size
Matrix *allocate_matrix(unsigned int row_num, unsigned int col_num);

//iterates over the matrix row by row and set the elements
void initialize_matrix(Matrix *matrix);

//displays the matrix in tabulated form
void print_matrix(const Matrix *matrix);

//sets the element with the given index
void set_element(Matrix *matrix, unsigned int row, unsigned int col, double value);

//transposes the given square matrix in place
void transpose_sq_matrix(Matrix *matrix);

//transposes the given matrix and the result is in a new Matrix
Matrix *transpose_new(Matrix *matrix);

//a + b, the result is in a new Matrix
Matrix *add_matrices_new(const Matrix *a, const Matrix *b);

//a + b, overwrites a->matrix
void add_matrices(Matrix *a, const Matrix *b);

//a - b, the result is in a new Matrix
Matrix *subtract_matrix_new(const Matrix *a, const Matrix *b);

//a - b, overwrites a->matrix
void subtract_matrix(Matrix *a, const Matrix *b);

//multiplies each element of the matrix with the given value
//the result is in a new Matrix
Matrix *multiplies_by_value_new(const Matrix *a, double value);

//multiplies each element of the matrix with the given value
void multiplies_by_value(Matrix *a, double value);

//a * b, the result is in a new Matrix
Matrix *multiplies_matrices(const Matrix *a, const Matrix *b);

//a[i][j] == b[i][j]
bool equals(const Matrix *a, const Matrix *b);

//frees all memory related to the given Matrix pointer
void free_matrix(Matrix *matrix);

#endif