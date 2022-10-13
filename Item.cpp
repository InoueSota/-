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

void Item::Randam_Item(int rand)
{
	
	if (rand == 0) {
		shild == true;
	}
	if (rand == 1) {
		speed_item == true;
	}
	if (rand == 2) {
		length_up == true;
	}
	

}

void Item::Set_Item(float x,float y,Player& player)
{
	pos.x = x;
	pos.y = y;
	radius = player.radius;
	flag = true;
}
