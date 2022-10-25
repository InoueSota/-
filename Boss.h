#pragma once
#include "Figure.h"
#include "Matrix.h"

class Boss;

const int MAX_BULLET=8;
const int MAX_BULLET_t = 4;
const int MAX_ZAN = 20;

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

	static struct Blade
	{

		Vector2 top_left = { 0,0};
		Vector2 top_right = { 0,0 };
		Vector2 bottom_left = { 0,0 };
		Vector2 bottom_right = { 0,0 };
		float theta=0;
		float t = 0;
		
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
	void Result(Player& player, Screen& screen,int rand);
	void Keep_Up(Player& player);
	void Init();
	
	int rand_num;
	int shild;
	float theta;

	//ÇœÇΩÅ[ÇÒÇP

	bool dekaku;
	float dekaku_t;
	bool dekaku_tback;
	Vec2 bullet_t_pos[MAX_BULLET_t];
	bool bullet_t_flag[MAX_BULLET_t];
	bool pattern_1;
	float theta_1;
	int flame_zan;
	Vec2 zanpos[MAX_ZAN];
	int zanrad[MAX_ZAN];
	float zan_time[MAX_ZAN];
	bool zan_flag[MAX_ZAN];

	bool bakuha;
	bool bakuha_back;

	float bakuha_T;
	float bakuha_Tback;
	float radius_f;

	//ÇœÇΩÅ[ÇÒ2

	Vec2 bullet_pos[MAX_BULLET];
	int bullet_rad[MAX_BULLET];
	float Ease_t_rad[MAX_BULLET];
	float Ease_t_radback[MAX_BULLET];
	float EaseT_bullet[MAX_BULLET];
	bool bullet_flag[MAX_BULLET];
	float lifetime[MAX_BULLET];
	bool pattern_2;
	int flame_2;

	//ÇœÇΩÅ[ÇÒ3

	Blade blade;
	bool pattern_3;
	bool keep;
	


	unsigned int color[MAX_BULLET];


	int count;
	int cooltime;



	
};



