#ifndef MATRIXCALC_H
#define MATRIXCALC_H

#define COL_MAJOR 0
#define ROW_MAJOR 1

void matrix_hello();
void test_matrix();
void matrix_print(int *matrix, int rows, int cols, const short printType);
void matrix4x4_print(const int *matrix);
void translate(float *matrix, float *vector);
void init_matrix_123(int *matrix, const int rows, const int cols);
void matrix_square_mult(int *matrix1, int *matrix2, int *result, int size);
void matrix4x4_mult(int *matrix1, int *matrix2, int *result);
int* matrix4x4_multt(int *matrix1, int *matrix2);
void matrix4x4_transpose(const int *origin, int *dest);

#endif // MATRIXCALC_H
