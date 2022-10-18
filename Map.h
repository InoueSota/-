#pragma once
#include <math.h>
#include<Novice.h>
#include "Player.h"
#include "Screen.h"
//#include "Figure.h"
//#include "main.h"


class Map {

public:
	Vec2 pos;
	float radius;
	unsigned int color;
	void DrawMap(Screen& screen);
	void Set_Map(float x, float y, float rad, unsigned int iro);
	bool Map_Collision(Player& player);
};