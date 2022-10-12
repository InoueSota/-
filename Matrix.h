#pragma once
#include "Vec2.h"
#include "Vec3.h"

//�R�s�R��̍s��
class MATRIX2 {
public:
    float _11, _12, _13,
		  _21, _22, _23,
		  _31, _32, _33;

    //�P�ʍs�������
    void identity();
    //�g��k���s�������
    void scaling(float x, float y);
    //��]�s�������
    void rotate(float angle);
    //���s�ړ��s�������
    void translate(float x, float y);
    //�u�R�s�R��s��v�Ɓu�Q�s�P��s��i�Q�����x�N�g���j�{�P�s�v�̊|���Z
    Vec2 operator*(const Vec2& v);
    //�R�s�R��s��ǂ����̊|���Z
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

	/*�@�s�������@*/
	void Identity();
	void Translate(float x, float y, float z = 0);
	void Translate(class Vec3& t);
	void Scaling(float x, float y, float z = 1);
	void RotateZ(float angle);
	/*�@�r���[�A�v���W�F�N�V����������@*/
	void camera(const Vec3& campos, const Vec3& lookatpos, const Vec3& upvec);
	void pers(float angle, float aspect, float n, float f);
	/*�@�s�񓯎m�̊|���Z�@*/
	void MulTranslate(float x, float y, float z = 0);
	void MulTranslate(const Vec3& t);
	void MulScaling(float x, float y, float z = 1);
	void MulScaling(const Vec3& s);
	void MulRotateZ(float angle);
	/*�@�s��ƍs��̊|���Z�@*/
	MATRIX3 operator*(const MATRIX3& m)const;
	/*�@�s��ƃx�N�g���̊|���Z�@*/
	Vec3 operator*(const Vec3& v)const;

private:

};
