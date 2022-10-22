#include "Matrix2_2.h"

Matrix2_2::Matrix2_2() {
	
}

Matrix2_2::Matrix2_2(float a, float b, float c, float d) {
	m[0][0] = a;
	m[0][1] = b;
	m[1][0] = c;
	m[1][1] = d;
}

Matrix2_2 MakeRotateMatrix(float theta) {
	Matrix2_2 tmp;
	tmp.m[0][0] = cosf(theta);
	tmp.m[0][1] = sinf(theta);
	tmp.m[1][0] = -sinf(theta);
	tmp.m[1][1] = cosf(theta);
	return tmp;
}

Vec2 Multiply(Vec2 vector, Matrix2_2 matrix) {
	Vec2 tmp;
	tmp.x = matrix.m[0][0] * vector.x + matrix.m[1][0] * vector.y;
	tmp.y = matrix.m[0][1] * vector.x + matrix.m[1][1] * vector.y;
	return tmp;
}