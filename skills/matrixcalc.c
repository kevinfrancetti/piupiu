#include"matrixcalc.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct {
	int x;
	int y;
	int z;
	int w;
} Vec4;

typedef struct {
	int data[16];
} Mat4x4;

Mat4x4 mat4x4_zero() {
	Mat4x4 zero;
	for (int i = 0; i < 16; i++) {
		zero.data[i] = 0;
	}
	return zero;
}

Mat4x4 mat4x4_identity() {
	Mat4x4 m;
	for (int i = 0; i < 16; i++) {
		m.data[i] = 0;
	}
	m.data[0 * 4 + 0] = 1;
	m.data[1 * 4 + 1] = 1;
	m.data[2 * 4 + 2] = 1;
	m.data[3 * 4 + 3] = 1;
	return m;
}

void matrix_hello() {
	printf("Hello matrixxdwdwx\n");
}

Mat4x4 mat4x4_transpose(const Mat4x4 *m) {
	Mat4x4 transposed;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			*(transposed.data + i * 4 + j) = *((*m).data + j * 4 + i);
		}
	}
	return transposed;
}

void matrix4x4_transpose(const int *origin, int *dest) {
	printf("mat4x4 transpose\n");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			*(dest + i * 4 + j) = *(origin + j * 4 + i);
		}
	}
}

int* matrix4x4_multt(int *matrix1, int *matrix2) {
	int *result = malloc(sizeof(int) * 4 * 4);
	int sum = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				int row = *(matrix1 + i * 4 + k);
				int col = *(matrix2 + k * 4 + j);
				sum += col * row;
			}
			*(result + i * 4 + j) = sum;
			sum = 0;
		}
	}
	return result;
}

void matrix4x4_mult(int *matrix1, int *matrix2, int *result) {
	int sum = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				int row = *(matrix1 + i * 4 + k);
				int col = *(matrix2 + k * 4 + j);
				sum += col * row;
			}
			*(result + i * 4 + j) = sum;
			sum = 0;
		}
	}
}

Mat4x4 mat4x4_mult(Mat4x4 m1, Mat4x4 m2) {
	int sum = 0;
	Mat4x4 result;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				int row = *(m1.data + i * 4 + k);
				int col = *(m2.data + k * 4 + j);
				sum += col * row;
			}
			*(result.data + i * 4 + j) = sum;
			sum = 0;
		}
	}
	return result;
}

void mat4x4_print(const Mat4x4 *m){
	printf("\n");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%d\t", *( (*m).data + i * 4 + j));
		}
		printf("\n");
	}
	printf("\n");
}


void matrix_print(int *matrix, int rows, int cols, const short printType) {
	//printf("%d\n", **matrix);
	printf("printMatrix di merda \n");
	if (printType == COL_MAJOR) {
		int tmp = rows;
		rows = cols;
		cols = tmp;

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				printf("%d ", *(matrix + j * cols + i));
			}
			printf("\n");
		}

	} else {

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				printf("%d ", *(matrix + i * cols + j));
			}
			printf("\n");
		}
	}

}


void matrix_square_mult(int *matrix1, int *matrix2, int *result, int size) {
	int sum = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {

			for (int k = 0; k < size; k++) {
				int row = *(matrix1 + i * size + k);
				int col = *(matrix2 + k * size + j);
				/*
				 printf("i = %d, j = %d, k = %d, col = %d, row = %d, col*row = %d\n", i, j, k, col,
				 row, col * row);
				 */
				sum += col * row;
			}
//			printf("sum = %d\n", sum);
			*(result + i * size + j) = sum;
			sum = 0;
		}
	}
}

void init_matrix_123(int *matrix, const int rows, const int cols) {
	int count = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			*(matrix + i * cols + j) = count;
			count++;
		}
	}
}

int* matrix123_create(const int rows, const int cols) {
	int *matrix = malloc(sizeof(int) * rows * cols);
	int count = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			*(matrix + i * cols + j) = count;
			count++;
		}
	}
	return matrix;
}


Vec4 mat4x4_vec4_mult(Mat4x4 m, Vec4 v) {
	Vec4 result;
	int tmp = 0;
	for (int i = 0; i < 16; i+=4) {
		tmp += m.data[i] * v.x;
		tmp += m.data[i + 1] * v.y;
		tmp += m.data[i + 2] * v.z;
		tmp += m.data[i + 3] * v.w;
		*(((int*) &result) + i/4) = tmp;
		tmp = 0;
	}
	return result;
}

void vec_print(const Vec4 *v){
	printf("\nv.x = %d\n", (*v).x);
	printf("v.y = %d\n", (*v).y);
	printf("v.z = %d\n", (*v).z);
	printf("v.w = %d\n\n", (*v).w);
}

Mat4x4 mat4x4_transalte(Mat4x4 m, Vec4 v) {
	Mat4x4 trans = mat4x4_identity();
	trans.data[4*1-1] = v.x;
	trans.data[4*2-1] = v.y;
	trans.data[4*3-1] = v.z;
	trans.data[4*4-1] = 1;
	return mat4x4_mult(trans, m);
}


Mat4x4 mat4x4_scale(Mat4x4 m, Vec4 v) {
	Mat4x4 scale = mat4x4_zero();
	*(scale.data + 0 * 4 + 0) = v.x;
	*(scale.data + 1 * 4 + 1) = v.y;
	*(scale.data + 2 * 4 + 2) = v.z;
	*(scale.data + 3 * 4 + 3) = v.w;
	return mat4x4_mult(scale, m);
}


void test_matrix() {
	Mat4x4 m1 = mat4x4_identity();
	mat4x4_print(&m1);
	float pi = 3.14159265359;
	printf("sin(pi/2) = %f\n", sin(pi/2));

	//m1.data[1] = 3;
	//m1.data[2] = 3;

	//m1.data[3] = 4;
	Vec4 v1 = { 1, 2, 3, 1 };
	Vec4 v2 = { 2, 2, 2, 1 };

	vec_print(&v1);
	vec_print(&v2);

	Mat4x4 m2 = mat4x4_scale(m1, v1);
	mat4x4_print(&m2);
	m2 = mat4x4_transalte(m2, v2);
	mat4x4_print(&m2);
	Vec4 v3 = mat4x4_vec4_mult(m2, v2);
	vec_print(&v3);

}
