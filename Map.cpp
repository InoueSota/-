#include "Map.h"


void Map::DrawMap(Screen& screen) {

	screen.DrawEllipse(pos.x, pos.y, radius, radius, 0, color, kFillModeWireFrame);

}

void Map::Set_Map(float x, float y, float rad,unsigned int iro)
{
	pos.x = x;
	pos.y = y;
	radius = rad;
	color = iro;
}

bool Map::Map_Collision(Player& player)
{
	
	float a = pos.x - player.pos.x;
	float b = pos.y - player.pos.y;
	float c = sqrtf(a * a + b * b);
	
	if ((c >= radius)) {
		return false;
	}
	else if ((c < radius)) {
		return true;
	}

	








		

		

	

	
		

		

}
	

