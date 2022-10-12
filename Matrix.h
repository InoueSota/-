#pragma once
#include "Vec2.h"
#include "Vec3.h"

//３行３列の行列
class MATRIX2 {
public:
    float _11, _12, _13,
		  _21, _22, _23,
		  _31, _32, _33;

    //単位行列をつくる
    void identity();
    //拡大縮小行列をつくる
    void scaling(float x, float y);
    //回転行列をつくる
    void rotate(float angle);
    //平行移動行列をつくる
    void translate(float x, float y);
    //「３行３列行列」と「２行１列行列（２次元ベクトル）＋１行」の掛け算
    Vec2 operator*(const Vec2& v);
    //３行３列行列どうしの掛け算
    MATRIX2 operator*(const MATRIX2& m);
    void mulTranslate(float x, float y);
    void mulScaling(float x, float y);
	void mulRotate(float angle);
};

class MATRIX3
{
public:
	float	_11, _12, _13, _14,
	 		_21, _22, _23, _24,
			_31, _32, _33, _34,
			_41, _42, _43, _44;

	/*　行列をつくる　*/
	void Identity();
	void Translate(float x, float y, float z = 0);
	void Translate(class Vec3& t);
	void Scaling(float x, float y, float z = 1);
	void RotateZ(float angle);
	/*　ビュー、プロジェクションをつくる　*/
	void camera(const Vec3& campos, const Vec3& lookatpos, const Vec3& upvec);
	void pers(float angle, float aspect, float n, float f);
	/*　行列同士の掛け算　*/
	void MulTranslate(float x, float y, float z = 0);
	void MulTranslate(const Vec3& t);
	void MulScaling(float x, float y, float z = 1);
	void MulScaling(const Vec3& s);
	void MulRotateZ(float angle);
	/*　行列と行列の掛け算　*/
	MATRIX3 operator*(const MATRIX3& m)const;
	/*　行列とベクトルの掛け算　*/
	Vec3 operator*(const Vec3& v)const;

private:

};
