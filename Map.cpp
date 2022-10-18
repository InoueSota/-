#include "Map.h"

//void Map::draw() {
//	for (int y = -5000; y < 5000; y++) {
//		for (int x = -5000; x < 5000; x++) {
//			if()
//		}
//	}
//}

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

void Map::Map_Collision(Player& player)
{
	
	float a = pos.x - player.pos.x;
	float b = pos.y - player.pos.y;
	float c = sqrtf(a * a + b * b);
	
	if ((c >= radius)) {
		
	}
	else if ((c < radius)) {
		
	}

	








		

		

	

	
		

		

}
	

