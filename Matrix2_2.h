#pragma once
#include <math.h>
#include "Vec2.h"
class Matrix2_2
{
public:
	Matrix2_2();
	Matrix2_2(float a, float b, float c, float d);
	float m[2][2];

};

Matrix2_2 MakeRotateMatrix(float theta);
//ベクトルと行列の積
Vec2 Multiply(Vec2 vector, Matrix2_2 matrix);