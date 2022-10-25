#include "Bar.h"

Bar::Bar() {
	beas = {
		{18,20},
		{18,70},
		{1896,20},
		{1896,70},
	};
	now = {
		{20,22},
		{20,22},
		{20,68},
		{20,68},
	};
}

void Bar::Update(Player player,Map map,WAVE wave) {
	Vec2 pos;
	if (wave.stage_1_only) {
		pos.x = ((player.radius - 25) / (wave.MapChenge(map) - 25)) * 1876;
	}
	if (wave.stage_2) {
		pos.x = ((player.radius - 25) / (wave.MapChenge(map) - 25)) * 1876;
	}
	now.RightTop.x = pos.x + 20;
	now.RightBottom.x = pos.x + 20;

}

void Bar::draw(Screen screen) {
	Novice::DrawQuad(now.LeftTop.x + screen.ScreenShake.x, now.LeftTop.y + screen.ScreenShake.y, now.RightTop.x + screen.ScreenShake.x, now.RightTop.y + screen.ScreenShake.y, now.LeftBottom.x + screen.ScreenShake.x, now.LeftBottom.y + screen.ScreenShake.y, now.RightBottom.x + screen.ScreenShake.x, now.RightBottom.y + screen.ScreenShake.y, 0.0f, 0.0f, 0, 0, 0, 0xE80971FF);
}
void Bar::beasdraw(Screen screen) {
	Novice::DrawQuad(beas.LeftTop.x + screen.ScreenShake.x, beas.LeftTop.y + screen.ScreenShake.y, beas.RightTop.x + screen.ScreenShake.x, beas.RightTop.y + screen.ScreenShake.y,beas.LeftBottom.x + screen.ScreenShake.x, beas.LeftBottom.y + screen.ScreenShake.y,beas.RightBottom.x + screen.ScreenShake.x, beas.RightBottom.y + screen.ScreenShake.y, 0.0f, 0.0f, 0, 0, 0, WHITE);
}