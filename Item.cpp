#include "Item.h"

Item::Item()
{
	pos.x = 0;
	pos.y = 0;
	radius = 0;
	item_rand = 0;
	flame = 60;
	speed_flame = 200;
	flag = false;
	speed_item=false;
	shild = false;
	length_up = false;
}

bool Item::Item_collision(Player& player, Screen& screen)
{
	

	Vec2 start_to_center = Vec2(pos - player.center);
	Vec2 start_to_end = Vec2(player.pos - player.center);
	Vec2 nomalize_stc = start_to_center.Normalized();

	float t = ((start_to_center.Dot(nomalize_stc)) / start_to_end.Length());
	t = Clamp(t, 0, 1);

	Vec2 f = (1.0f - t) * player.center + t * player.pos;

	float distance = (pos - f).Length();

	if (distance < player.radius / 50 + radius) {
		return true;
	}
	return false;

}

void Item::Randam_Item()
{
	
	if (item_rand == 0) {
		speed_item = true;
	}
	if (item_rand == 1) {
		shild = true;
		
	}
	if (item_rand == 2) {
		length_up = true;
	}
	

}

void Item::Set_Item(float x,float y,Player& player,int rand)
{
	if (flag == false) {
		pos.x = x;
		pos.y = y;
		radius = player.radius;
		item_rand = rand;
		
		speed_flame = 200;

		flag = true;
	}
}

void Item::Draw(Screen& screen, Player& player)
{
	
	if (flag == true && speed_item == false) {
		
		screen.DrawEllipse(pos.x, pos.y, radius,radius, 0, BLACK, kFillModeSolid);

	}
	if (speed_item == true) {
		screen.DrawEllipse(player.pos.x, player.pos.y, player.radius, player.radius, 0, BLUE, kFillModeSolid);

	}
}

void Item::Result(Player& player,Screen&screen)
{
	
	if (speed_item == true) {
		player.incDeg = 6.0f;
		speed_flame -= 1;
		if (flame == 0) {
			flame = 60;
		}
		flame -= 1;
		Clamp(flame,0, 60);
		Novice::ScreenPrintf(0, 60, "%d",flame);
		Novice::ScreenPrintf(0, 80, "%f", flame);
		if (speed_flame <= 0) {
			player.incDeg = 3.0f;
			speed_item = false;
			flag = false;
		}


	}
	
	Novice::ScreenPrintf(0, 80, "speedtime:::%d",speed_flame );

}
