#include "Item.h"

bool Item::Item_collision(Player& player, Screen& screen)
{
	float a = player.pos.x - pos.x;
	float b = player.pos.y - pos.y;
	float c = sqrtf(a * a + b * b);

	if (c <= (player.radius*screen.Zoom.x + radius)) {
		return true;
	}
	else {
		return false;

	}

   
}

void Item::Set_Item(float x,float y)
{
	pos.x = x;
	pos.y = y;
}
