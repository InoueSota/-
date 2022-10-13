#pragma once
#include "Vec2.h"
#include <math.h>

class Matrix33 {

private:
	float m[3][3];

public:
	Matrix33(
		float _11 = 1.0f, float _12 = 0.0f, float _13 = 0.0f,
		float _21 = 0.0f, float _22 = 1.0f, float _23 = 0.0f,
		float _31 = 0.0f, float _32 = 0.0f, float _33 = 1.0f) {
		m[0][0] = _11, m[0][1] = _12, m[0][2] = _13;
		m[1][0] = _21, m[1][1] = _22, m[1][2] = _23;
		m[2][0] = _31, m[2][1] = _32, m[2][2] = _33;
	}

	friend inline Matrix33 operator*(const Matrix33& mat1, const Matrix33& mat2) {
		return {
			mat1.m[0][0] * mat2.m[0][0] + mat1.m[0][1] * mat2.m[1][0] + mat1.m[0][2] * mat2.m[2][0],
			mat1.m[0][0] * mat2.m[0][1] + mat1.m[0][1] * mat2.m[1][1] + mat1.m[0][2] * mat2.m[2][1],
			mat1.m[0][0] * mat2.m[0][2] + mat1.m[0][1] * mat2.m[1][2] + mat1.m[0][2] * mat2.m[2][2],

			mat1.m[1][0] * mat2.m[0][0] + mat1.m[1][1] * mat2.m[1][0] + mat1.m[1][2] * mat2.m[2][0],
			mat1.m[1][0] * mat2.m[0][1] + mat1.m[1][1] * mat2.m[1][1] + mat1.m[1][2] * mat2.m[2][1],
			mat1.m[1][0] * mat2.m[0][2] + mat1.m[1][1] * mat2.m[1][2] + mat1.m[1][2] * mat2.m[2][2],

			mat1.m[2][0] * mat2.m[0][0] + mat1.m[2][1] * mat2.m[1][0] + mat1.m[2][2] * mat2.m[2][0],
			mat1.m[2][0] * mat2.m[0][1] + mat1.m[2][1] * mat2.m[1][1] + mat1.m[2][2] * mat2.m[2][1],
			mat1.m[2][0] * mat2.m[0][2] + mat1.m[2][1] * mat2.m[1][2] + mat1.m[2][2] * mat2.m[2][2]
		};
	}

	friend inline Vec2 operator*(const Vec2& vec, const Matrix33& mat) {
		return {
			vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + 1.0f * mat.m[2][0],
			vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + 1.0f * mat.m[2][1]
		};
	}

	inline Matrix33& operator*=(const Matrix33& mat) {
		*this = *this * mat;
		return *this;
	}

	// ’PˆÊs—ñ
	static inline Matrix33 Identity() {
		return {
			1,		0,		0,
			0,		1,		0,
			0,		0,		1
		};
	}
	// Šg‘åk¬s—ñ
	static inline Matrix33 MakeScaling(float scaleX, float scaleY) {
		return {
			scaleX, 0,		0,
			0,		scaleY,	0,
			0,		0,		1
		};
	}
	// Šg‘åk¬s—ñ
	static inline Matrix33 MakeScaling(float scale) {
		return MakeScaling(scale, scale);
	}
	// Šg‘åk¬s—ñ
	static inline Matrix33 MakeScaling(const Vec2& scale) {
		return MakeScaling(scale.x, scale.y);
	}
	// ‰ñ“]s—ñ
	static inline Matrix33 MakeRotation(float theta) {
		float s = sinf(theta);
		float c = cosf(theta);
		return {
			c,		s,		0,
			-s,		c,		0,
			0,		0,		1
		};
	}
	// •½sˆÚ“®s—ñ
	static inline Matrix33 MakeTranslation(float vecX, float vecY) {
		return {
			1,		0,		0,
			0,		1,		0,
			vecX,	vecY,	1
		};
	}
	// •½sˆÚ“®s—ñ
	static inline Matrix33 MakeTranslation(const Vec2& vector) {
		return MakeTranslation(vector.x, vector.y);
	}
	

	// ’PˆÊs—ñ‚É‚·‚é
	inline void SetIdentity() {
		*this = Identity();
	}
	// Šg‘åk¬s—ñ‚É‚·‚é
	inline void SetScaling(float scaleX, float scaleY) {
		*this = MakeScaling(scaleX, scaleY);
	}
	// Šg‘åk¬s—ñ‚É‚·‚é
	inline void SetScaling(float scale) {
		*this = MakeScaling(scale);
	}
	// Šg‘åk¬s—ñ‚É‚·‚é
	inline void SetScaling(const Vec2& scale) {
		*this = MakeScaling(scale);
	}
	// ‰ñ“]s—ñ‚É‚·‚é
	inline void SetRotation(float theta) {
		*this = MakeRotation(theta);
	}
	// •½sˆÚ“®s—ñ‚É‚·‚é
	inline void SetTranslation(float vecX, float vecY) {
		*this = MakeTranslation(vecX, vecY);
	}
	// •½sˆÚ“®s—ñ‚É‚·‚é
	inline void SetTranslation(const Vec2& vector) {
		*this = MakeTranslation(vector);
	}


};