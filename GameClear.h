#pragma once
#include "Screen.h"
#include "easing.h"

class GameClear
{
public:
	GameClear() {
		Init();
	}

	bool isGameClear;
	bool isLoadTexture;
	int Gameclear;

	int CircleFrame;
	Vec2 Circlepos[2];
	float CircleRadius[2];
	float CircleEasingt[2];
	unsigned int Circlecolor[2];

	float alphat;
	unsigned int color;

	void Init();
	void KillBoss();
	void DrawKillBoss();
	void Process(Screen& screen);
	void GLoadTexture();
	void Draw(Screen& screen);

};
