#pragma once
#include "Figure.h"


class Boss;



class Boss:public Figure
{
	//pos,radius,color,flag

public:
	Boss();
	void draw(Screen& screen);
	void set(Vec2 pos);
	void Rand_Move();
	void Result();
	void Keep_Up(Player& player);

	int rand_num;
	int shild;
	bool pattern_1;
	bool pattern_2;
	bool pattern_3;


	int count;
	int cooltime;
};

