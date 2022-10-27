#include "Bar.h"

Bar::Bar() {
	beas = {
		{18,20},
		{18,70},
		{1886,20},
		{1886,70},
	};
	now = {
		{20,22},
		{20,22},
		{20,68},
		{20,68},
	};
	item = {
		{1836,20},
		{1836,70},
		{1886,20},
		{1886,70},
	};
	item_state = {
		{1836,20},
		{1836,70},
		{1886,20},
		{1886,70},
	};
	item_position = { 1861, 45 };
	next_map_flag = false;
	openflag = false;
}
void Bar::ItemUpdate() {
	t += 0.05;
	if (t > 1) {
		if (!openflag) {
			item.LeftTop.x -= 10;
			item.LeftTop.y -= 10;
			item.RightTop.x += 10;
			item.RightTop.y -= 10;
			item.LeftBottom.x -= 10;
			item.LeftBottom.y += 10;
			item.RightBottom.x += 10;
			item.RightBottom.y += 10;
			openflag = true;
		}
		if(openflag) {
			if (item.RightTop.x - item.LeftTop.x < 10) {
				openflag = false;
				t = 0;
				next_map_flag = true;
			}
			item.LeftTop.x += 4;
			item.LeftTop.y -= 4;
			item.RightTop.x -= 4;
			item.RightTop.y -= 4;
			item.LeftBottom.x += 4;
			item.LeftBottom.y += 4;
			item.RightBottom.x -= 4;
			item.RightBottom.y += 4;
		}
		
	}
	else {
		Quad op;
		Matrix33 mat;
		op = {
			{-25,25},
			{+25,+25},
			{-25,-25},
			{+25,-25},
		};
		mat = Matrix33::Identity();
		mat *= Matrix33::MakeScaling((1.0f - t) * 1 + t * 5);
		/*mat *= Matrix33::MakeRotation();*/
		mat *= Matrix33::MakeTranslation((1.0f - t) * 1861 + t * 1920 / 2, (1.0f - t) * 45 + t * 1080 / 2);

		item.LeftTop = op.LeftTop * mat;
		item.RightTop = op.RightTop * mat;
		item.LeftBottom = op.LeftBottom * mat;
		item.RightBottom = op.RightBottom * mat;
	}
}
void Bar::Update(Player player,Map map,WAVE wave) {
	Vec2 pos;
	if (wave.stage == wave.stage_1_only) {
		pos.x = ((player.radius - 25) / (wave.MapChenge(map) - 25)) * 1866;
	}
	if (wave.stage == wave.stage_2) {
		pos.x = ((player.radius - 80) / (wave.MapChenge(map) - 80)) * 1866;
	}
	if (wave.stage == wave.stage_3) {
		pos.x = ((player.radius - 80) / (240-80)) * 1866;
	}
	now.RightTop.x = pos.x + 20;
	now.RightBottom.x = pos.x + 20;

}


void Bar::draw(Screen screen) {
	
	Novice::DrawQuad(now.LeftTop.x + screen.ScreenShake.x, now.LeftTop.y + screen.ScreenShake.y, now.RightTop.x + screen.ScreenShake.x, now.RightTop.y + screen.ScreenShake.y, now.LeftBottom.x + screen.ScreenShake.x, now.LeftBottom.y + screen.ScreenShake.y, now.RightBottom.x + screen.ScreenShake.x, now.RightBottom.y + screen.ScreenShake.y, 0.0f, 0.0f, 0, 0, 0, 0xE80971FF);
	//Novice::DrawQuad(now.RightTop.x + screen.ScreenShake.x, now.RightTop.y + screen.ScreenShake.y, now.RightTop.x + screen.ScreenShake.x, now.RightTop.y + screen.ScreenShake.y, now.RightBottom.x + screen.ScreenShake.x, now.RightBottom.y + screen.ScreenShake.y, now.RightBottom.x+ screen.ScreenShake.x, now.RightBottom.y + screen.ScreenShake.y, geji_anime * 80, 0.0f, 80, 46, geji_gra, WHITE);
	
}
void Bar::beasdraw(Screen screen) {
	Novice::DrawQuad(beas.LeftTop.x + screen.ScreenShake.x, beas.LeftTop.y + screen.ScreenShake.y, beas.RightTop.x + screen.ScreenShake.x, beas.RightTop.y + screen.ScreenShake.y,beas.LeftBottom.x + screen.ScreenShake.x, beas.LeftBottom.y + screen.ScreenShake.y,beas.RightBottom.x + screen.ScreenShake.x, beas.RightBottom.y + screen.ScreenShake.y, 0.0f, 0.0f, 0, 0, 0, WHITE);
}

void Bar::drawItem(Screen screen) {
	Novice::DrawQuad(item.LeftTop.x + screen.ScreenShake.x, item.LeftTop.y + screen.ScreenShake.y, item.RightTop.x + screen.ScreenShake.x, item.RightTop.y + screen.ScreenShake.y, item.LeftBottom.x + screen.ScreenShake.x, item.LeftBottom.y + screen.ScreenShake.y, item.RightBottom.x + screen.ScreenShake.x, item.RightBottom.y + screen.ScreenShake.y, 0.0f, 0.0f, 50, 50, Slash_mini, WHITE);
}