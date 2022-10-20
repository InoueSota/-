#pragma once
#include "Figure.h"
#include "Matrix.h"

class Boss;

const int MAX_BULLET=4;

class Boss:public Figure
{
	//pos,radius,color,flag
	static struct Matrix2x2
	{
		float m[2][2];
	};

	static struct Vector2
	{
		float x;
		float y;
	};

	Matrix2x2 MakeRotateMatrix(float theta)
	{

		Matrix2x2 matrix;
		matrix.m[0][0] = cos(theta);
		matrix.m[0][1] = sin(theta);
		matrix.m[1][0] = -sin(theta);
		matrix.m[1][1] = cos(theta);

		return matrix;
	}

	Vector2 Multiply(Vector2 vector, Matrix2x2 matrix) {
		Vector2 matrix3 = { 0,0 };
		matrix3.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0];
		matrix3.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1];
		return matrix3;

	}

	float easing(float t, float start, float end) {

		return((1.0f - t) * start + t * end);
	};
public:
	Boss();
	void draw(Screen& screen);
	void set(Vec2 pos);
	void Rand_Move(int rand);
	void Rand_Move();
	void Result(Player& player, Screen& screen);
	
	void Keep_Up(Player& player);

	
	int rand_num;
	int shild;
	float theta;
	Vec2 bullet_pos[MAX_BULLET];
	int bullet_rad[MAX_BULLET];
	float EaseT_bullet[MAX_BULLET];
	bool bullet_flag[MAX_BULLET];
	unsigned int color[MAX_BULLET];
	float lifetime[MAX_BULLET];
	bool pattern_1;
	bool pattern_2;
	bool pattern_3;


	int count;
	int cooltime;



	
};



