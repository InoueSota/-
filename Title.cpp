#include "Title.h"

void Title::Init() {
	Titlepos = { 0,0 };
	Spacepos = { 0,0 };
	isLoadTexture = false;
}
void Title::Process(char prekeys, char keys) {
	if (isLoadTexture == false){
		title = Novice::LoadTexture("./resource/Title/Title.png");
		space = Novice::LoadTexture("./resource/Title/Space.png");
		isLoadTexture = true;
	}
	theta += 1 / (8.0f * M_PI);
	Spacepos.y = sinf(theta) * 20 - (SCREEN_HEIGHT / 4);
}
void Title::Draw(Screen& screen, Title& title) {
	Quad titles{
		{title.Titlepos.x - (kTitleWidth / 2), title.Titlepos.y + (kTitleHeight / 2)},
		{title.Titlepos.x + (kTitleWidth / 2), title.Titlepos.y + (kTitleHeight / 2)},
		{title.Titlepos.x - (kTitleWidth / 2), title.Titlepos.y - (kTitleHeight / 2)},
		{title.Titlepos.x + (kTitleWidth / 2), title.Titlepos.y - (kTitleHeight / 2)}
	}, spaces{
		{title.Spacepos.x - (kSpaceWidth / 2), title.Spacepos.y + (kSpaceHeight / 2)},
		{title.Spacepos.x + (kSpaceWidth / 2), title.Spacepos.y + (kSpaceHeight / 2)},
		{title.Spacepos.x - (kSpaceWidth / 2), title.Spacepos.y - (kSpaceHeight / 2)},
		{title.Spacepos.x + (kSpaceWidth / 2), title.Spacepos.y - (kSpaceHeight / 2)}
	};
	
	screen.DrawQuad2(titles, 0, 0, kTitleWidth, kTitleHeight, title.title, WHITE);
	screen.DrawQuad2(spaces, 0, 0, kSpaceWidth, kSpaceHeight, title.space, WHITE);
}