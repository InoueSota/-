#include "Bar.h"

Bar::Bar() {
	beas = {
		{18,20},
		{18,70},
		{1900,20},
		{1900,70},
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
		pos.x = ((player.radius - 25) / (wave.MapChenge(map) - 25)) * 1880;
	}
	if (wave.stage_2) {
		pos.x = ((player.radius - 25) / (wave.MapChenge(map) - 25)) * 1880;
	}
	now.RightTop.x = pos.x + 20;
	now.RightBottom.x = pos.x + 20;

}

void Bar::draw() {
	Novice::DrawQuad(now.LeftTop.x, now.LeftTop.y, now.RightTop.x, now.RightTop.y, now.LeftBottom.x, now.LeftBottom.y, now.RightBottom.x, now.RightBottom.y, 0.0f, 0.0f, 0, 0, 0, 0xE80971FF);
}
void Bar::beasdraw() {
	Novice::DrawQuad(beas.LeftTop.x, beas.LeftTop.y, beas.RightTop.x, beas.RightTop.y,beas.LeftBottom.x, beas.LeftBottom.y,beas.RightBottom.x, beas.RightBottom.y, 0.0f, 0.0f, beas.RightTop.x - beas.LeftTop.x, beas.RightTop.y - beas.LeftTop.y, 0, WHITE);
}