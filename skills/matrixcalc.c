#include"matrixcalc.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<X11/Xlib.h>

#define PI   3.14159265358979323846264338327950288
#define degToRad(angleInDegrees) ((angleInDegrees) * PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / PI)


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

void vec_print(const Vec4 *v) {
	printf("\nv.x = %.2f\n", (*v).x);
	printf("v.y = %.2f\n", (*v).y);
	printf("v.z = %.2f\n", (*v).z);
	printf("v.w = %.2f\n\n", (*v).w);
}

void mat4x4_print(const Mat4x4 *m) {
	printf("\n");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%.2f\t", *((*m).data + i * 4 + j));
		}
		printf("\n");
	}
	printf("\n");
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

Mat4x4 mat4x4_mult(Mat4x4 m1, Mat4x4 m2) {
	float sum = 0;
	Mat4x4 result;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				float row = *(m1.data + i * 4 + k);
				float col = *(m2.data + k * 4 + j);
				sum += col * row;
			}
			*(result.data + i * 4 + j) = sum;
			sum = 0;
		}
	}
	return result;
}

Vec4 mat4x4_vec4_mult(Mat4x4 m, Vec4 v) {
	Vec4 result;
	float tmp = 0;
	for (int i = 0; i < 16; i += 4) {
		tmp += m.data[i] * v.x;
		tmp += m.data[i + 1] * v.y;
		tmp += m.data[i + 2] * v.z;
		tmp += m.data[i + 3] * v.w;
		*(((float*) &result) + i / 4) = tmp;
		tmp = 0;
	}
	return result;
}

Mat4x4 mat4x4_transalte(Mat4x4 m, Vec4 v) {
	Mat4x4 trans = mat4x4_identity();
	trans.data[4 * 1 - 1] = v.x;
	trans.data[4 * 2 - 1] = v.y;
	trans.data[4 * 3 - 1] = v.z;
	trans.data[4 * 4 - 1] = 1;
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

//MAKE UNIT VEC!!
Mat4x4 mat4x4_rotate(Mat4x4 m, Vec4 v, float phi) {
	Mat4x4 rotate; // = mat4x4_zero();
	rotate.data[0] = cos(phi) + v.x * v.x * (1 - cos(phi));
	rotate.data[1] = v.x * v.y * (1 - cos(phi)) - v.z * sin(phi);
	rotate.data[2] = v.x * v.z * (1 - cos(phi)) + v.y * sin(phi);
	rotate.data[3] = 0;
	rotate.data[4] = v.x * v.y * (1 - cos(phi)) + v.z * sin(phi);
	rotate.data[5] = cos(phi) + v.y * v.y * (1 - cos(phi));
	rotate.data[6] = v.y * v.z * (1 - cos(phi)) - v.x * sin(phi);
	rotate.data[7] = 0;
	rotate.data[8] = v.x * v.z * (1 - cos(phi)) - v.y * sin(phi);
	rotate.data[9] = v.y * v.z * (1 - cos(phi)) + v.x * sin(phi);
	rotate.data[10] = cos(phi) + v.z * v.z * (1 - cos(phi));
	rotate.data[11] = 0;
	rotate.data[12] = 0;
	rotate.data[13] = 0;
	rotate.data[14] = 0;
	rotate.data[15] = 1;

	return mat4x4_mult(rotate, m);
}

void test_matrix() {
	Mat4x4 m1 = mat4x4_identity();
	mat4x4_print(&m1);
	float pi = 3.14159265359;
	printf("sin(pi/2) = %f\n", sin(pi / 2));

	//m1.data[1] = 3;
	//m1.data[2] = 3;

	//m1.data[3] = 4;
	Vec4 v1 = { 1, 1, 345, 1 };
	Vec4 v2 = { 2, 0, 0, 1 };
	Vec4 v3 = { 0.5, 0.5, 0.5 };
	Vec4 rot_axis = { 0, 0, 1, 1 };

	vec_print(&v1);
	//vec_print(&v2);

	//Mat4x4 trans = mat4x4_transalte(m1, v1);
	printf("yolo %f\n", degToRad(1));
	//MAKE THIS UNIT VECT!!!
	Mat4x4 rot = mat4x4_rotate(m1, rot_axis, degToRad(360*43+90));
	mat4x4_print(&rot);
	//m2 = mat4x4_transalte(m2, v2);
	//mat4x4_print(&m2);
	Vec4 v4 = mat4x4_vec4_mult(rot, v1);
	vec_print(&v4);

}

//private functions
void matrix_print(float *matrix, int rows, int cols, const short printType) {
	//printf("%d\n", **matrix);
	printf("printMatrix di merda \n");
	if (printType == COL_MAJOR) {
		int tmp = rows;
		rows = cols;
		cols = tmp;

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				printf("%.2f ", *(matrix + j * cols + i));
			}
			printf("\n");
		}

	} else {

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				printf("%.2f ", *(matrix + i * cols + j));
			}
			printf("\n");
		}
	}
}
