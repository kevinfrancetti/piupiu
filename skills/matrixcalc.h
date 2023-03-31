#ifndef MATRIXCALC_H
#define MATRIXCALC_H

#define COL_MAJOR 0
#define ROW_MAJOR 1



typedef struct {
	float x;
	float y;
	float z;
	float w;
} Vec4;

typedef struct {
	float data[16];
} Mat4x4;


void matrix_hello();
void test_matrix();
void vec_print(const Vec4 *v);
void mat4x4_print(const Mat4x4 *m);
Mat4x4 mat4x4_mult(Mat4x4 m1, Mat4x4 m2);
Vec4 mat4x4_vec4_mult(Mat4x4 m, Vec4 v);

Mat4x4 mat4x4_transpose(const Mat4x4 *m);
Mat4x4 mat4x4_transalte(Mat4x4 m, Vec4 v);
Mat4x4 mat4x4_scale(Mat4x4 m, Vec4 v);

#endif // MATRIXCALC_H
