#pragma once
#include "Screen.h"
#include "Quad.h"
#include "Player.h"
#include "Map.h"
#include <Novice.h>
#include "Wave.h"

class Bar
{
public:
	Bar();
	
	Quad beas;
	Quad now;
	Quad item_state;
	Quad item;
	Vec2 item_position;
	float Stage_Max;
	float Radius_Now;
	float t;
	bool next_map_flag;
	bool openflag;
	int Slash_mini;

	void Update(Player player ,Map map,WAVE wave);
	void beasdraw(Screen screen);
	void draw(Screen screen);
	void drawItem(Screen screen);
	void ItemUpdate();
};

