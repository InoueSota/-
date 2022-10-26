#pragma once
#include "Figure.h"
#include "Matrix.h"
#include "Sound.h"

class Boss;

const int MAX_BULLET=8;
const int MAX_BULLET_t = 4;
const int MAX_ZAN = 20;
const int MAX_DAME = 20;
const int MAX_RUNE = 50;

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
	static struct dame {
		
		Vec2 pos[MAX_DAME];
		Vec2 vel[MAX_DAME];
		float rad[MAX_DAME];
		float EaseT[MAX_DAME];
		float lifetime[MAX_DAME];
		bool flag[MAX_DAME];
		unsigned int color[MAX_DAME];
	};
	static struct Rune {
		int Time;

		Vec2 pos[MAX_RUNE];
		Vec2 vel[MAX_RUNE];
		float rad[MAX_RUNE];
		float EaseT[MAX_RUNE];
		float lifetime[MAX_RUNE];
		bool flag[MAX_RUNE];
		unsigned int color[MAX_RUNE];
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
	int  easing(float t, int start, int end) {

		return((1.0f - t) * start + t * end);
	};

public:
	Boss();
	void draw(Screen& screen);
	void set(Vec2 pos);
	void t_set(Vec2 pos);
	void Rand_Move(int rand);
	void Result(Player& player, Screen& screen,int rand,Sound& sound);
	void Keep_Up(Player& player);
	void t_draw(Screen& screen);
	void Init();
	void bossgekiha();
	void Dame_Par();
	void Rune_Par();
	
	bool Bullet_Player(Player& player);
	bool Bullet_Player_2(Player& player);
	bool Blade_Player(Player& player);
	bool Blade_Player_2(Player& player);
	bool Boss_Player(Player& player);
	
	float boss_easet;
	float boss_c_t;

	int rand_num;
	int shild;
	float theta;
	bool hit;
	unsigned int Boss_color;

	bool damepar;

	dame dame;
	Rune rune;
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
	bool dasita[MAX_BULLET_t];
	bool bakuha;
	bool bakuha_back;

	float bakuha_T;
	float bakuha_Tback;
	float radius_f;

	//ÇœÇΩÅ[ÇÒ2

	Vec2 bullet_pos[MAX_BULLET];
	int bullet_rad[MAX_BULLET];
	int bullet_rad_f;

	float Ease_t_rad[MAX_BULLET];
	float Ease_t_radback[MAX_BULLET];
	float EaseT_bullet[MAX_BULLET];
	bool bullet_flag[MAX_BULLET];
	float lifetime[MAX_BULLET];
	bool pattern_2;
	int flame_2;
	bool tyakkaman[MAX_BULLET];

	//ÇœÇΩÅ[ÇÒ3

	Blade blade;
	bool pattern_3;
	bool keep;
	unsigned int color[MAX_BULLET];
	int count;
	int cooltime;
	//4
	bool pattern_4;
};



