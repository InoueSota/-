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
	float Stage_Max;
	float Radius_Now;

	void Update(Player player ,Map map,WAVE wave);
	void beasdraw(Screen screen);
	void draw(Screen screen);

};

