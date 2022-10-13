#pragma once
#include <Novice.h>
#include "Vec2.h"
#include "Screen.h"
#include "Player.h"


class Item {

	Vec2 pos;
	float radius;
	bool flag;
	bool speed_item;
	bool shild;
	bool length_up;

public:
	bool Item_collision(Player& player, Screen& screen);

	void Randam_Item(int rand);
	void Set_Item(float x,float y,Player&player);

};





//////////////プロとタイプレッシャー宣言

