#pragma once
#include "Player.h"

class Bubble{
public:

	Bubble() {
		Init();
	}

	static const int kBubbleMax = 12;
	static const int kBubbleTimeMax = 120;
	static const int kBubbleStanFrame = 120;
	static const int kBubbleInterval = 20;
	static const int kBubbleDistance = 100;

	Vec2 pos[kBubbleMax];
	Vec2 direvelo[kBubbleMax];
	Vec2 velo[kBubbleMax];
	bool isOccur[kBubbleMax];
	bool isRelease[kBubbleMax];
	int Shotframe[kBubbleMax];
	int Longpressframe;
	unsigned int color = 0xFFFF00FF;
	float spd = 3;
	float radius;

	void Init();
	void Make(Player& players, Screen& screen);
	void Move(char keys);
	void Process(Player& players, Screen& screen, char keys);
	void Draw(Screen& screen);

};

class Wave {
public:
	const int kWaveSizeMax = 10;


};

class Beam {
public:
	const int kBeamTimeMax = 10;

};

