#pragma once
#include <Novice.h>
#include "Vec2.h"
#include "Screen.h"
#include "Player.h"



class Item {

	Vec2 pos;
	float radius;
	int item_rand;
	bool speed_item;
	bool shild;
	bool length_up;
	int flame ;
	int speed_flame;

	



public:
	bool flag;

	Item();
	bool Item_collision(Player& player, Screen& screen);

	void Randam_Item();
	void Set_Item(float x,float y,Player&player,int rand);
	void Draw(Screen& screen, Player& player);
	void Result(Player& player,Screen& screen);
};





//////////////プロとタイプレッシャー宣言

