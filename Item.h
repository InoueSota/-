#pragma once
#include <Novice.h>
#include "Vec2.h"
#include "Screen.h"
#include "Player.h"


class Item {

	Vec2 pos;
	float radius;
	bool flag;

public:
	bool Item_collision(Player& player, Screen& screen);
	void Set_Item(float x,float y);

};





//////////////プロとタイプレッシャー宣言

