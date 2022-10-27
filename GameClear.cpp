#include "GameClear.h"

void GameClear::Init() {
	isGameClear = false;
	for (int i = 0; i < 2; i++) {
		Circlepos[i] = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
		CircleRadius[i] = 0;
		Circlecolor[0] = 0xE5C210FF;
		Circlecolor[1] = 0x2B1247FF;
	}
	alphat = 0.0f;
	color = 0xFFFFFF00;
	TTalphat = 0.0f;
	TTcolor = 0xFFFFFF00;
	isToTitle = false;
}
void GameClear::KillBoss() {
	CircleFrame++;
	if (CircleFrame >= 0){
		CircleEasingt[0] += (0.01f * kFrameMag);
		CircleEasingt[0] = Clamp(CircleEasingt[0], 0.0f, 1.0f);
		CircleRadius[0] = Lerp(Easing::easeOutSine(CircleEasingt[0]), SCREEN_WIDTH);
	}
	if (CircleFrame >= 90){
		CircleEasingt[1] += (0.01f * kFrameMag);
		CircleEasingt[1] = Clamp(CircleEasingt[1], 0.0f, 1.0f);
		CircleRadius[1] = Lerp(Easing::easeOutSine(CircleEasingt[1]), SCREEN_WIDTH);
	}
}
void GameClear::DrawKillBoss() {
	for (int i = 0; i < 2; i++){
		Novice::DrawEllipse(Circlepos[i].x, Circlepos[i].y, CircleRadius[i], CircleRadius[i], 0.0f, Circlecolor[i], kFillModeSolid);
	}
}
void GameClear::GLoadTexture() {
	if (isLoadTexture == false) {
		Gameclear = Novice::LoadTexture("./resource./Title./Gameclear.png");
		isLoadTexture = true;
	}
}
void GameClear::Process(Screen& screen) {
	alphat += (0.01f * kFrameMag);
	alphat = Clamp(alphat, 0.0f, 1.0f);
	color = 0xFFFFFF00 | static_cast<int>((1.0f - alphat) * 0x00 + alphat * 0xFF);
	theta += 1 / (8.0f * M_PI);
	Trianglepos.y = sinf(theta) * 10 - 650;

	if (isKillBoss == false){
		for (int i = 0; i < 2; i++) {
			Circlepos[i] = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
			CircleRadius[i] = 0;
			Circlecolor[0] = 0xE5C210FF;
			Circlecolor[1] = 0x2B1247FF;
		}
	}

}
void GameClear::Draw(Screen& screen) {
	Novice::DrawSprite(0, 0, Gameclear, 1, 1, 0.0f, color);
	screen.DrawTriangle(Trianglepos.x - 50, Trianglepos.y + 50, Trianglepos.x + 50, Trianglepos.y + 50, Trianglepos.x, Trianglepos.y - 50, WHITE, kFillModeSolid);
}
void GameClear::ToTitle() {
	TTalphat += (0.01f * kFrameMag);
	TTalphat = Clamp(TTalphat, 0.0f, 1.0f);
	TTcolor = 0x00000000 | static_cast<int>((1.0f - TTalphat) * 0x00 + TTalphat * 0xFF);
}
void GameClear::DrawToTitle() {
	Novice::DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, TTcolor, kFillModeSolid);
}