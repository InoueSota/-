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
	static const int kBubbleInterval = 6;
	static const int kBubbleDistance = 100;

	Vec2 pos[kBubbleMax];
	Vec2 direvelo[kBubbleMax];
	Vec2 velo[kBubbleMax];
	bool isOccur[kBubbleMax];
	bool isRelease[kBubbleMax];
	int Shotframe[kBubbleMax];
	int Longpressframe;
	unsigned int color = 0xFF6E00FF;
	float spd = 3;
	float radius;

	void Init();
	void Make(Player& players, Screen& screen);
	void Move(char keys);
	void Process(Player& players, Screen& screen, char keys);
	void Draw(Screen& screen);

};

class Slash {
public:

	Slash() {
		Init();
	}

	static const int kSlashSizeMax = 100;
	static const int kSlashTimeMax = 120;

	Quad op;
	Quad pos;
	Vec2 direvelo;
	Vec2 velo;
	float spd;
	bool isTrigger;
	bool isOccur;
	bool isLoadTexture;
	int delayframe;
	int shotframe;
	int slashImage;	//‰æ‘œ—p•Ï”

	void Init();
	void Make(Player& players, Screen& screen);
	void Move();
	void Process(Player& players, Screen& screen, char prekeys, char keys);
	void Draw(Screen& screen);

};

class Beam {
public:

	Beam() {
		Init();
	}

	static const int kBeamSizeMax = 120;
	static const int kBeamTimeMax = 120;
	static const int kBeamInterval = 600;

	Quad op;
	Quad pos1, pos2;
	bool isOccur;
	bool isLoadTexture;
	int frame;
	int shotframe;
	int Lefttop;	//‰æ‘œ—p•Ï”
	int beamImage;	//‰æ‘œ—p•Ï”

	void Init();
	void Make(Player& players, Screen& screen);
	void Move(Player& players, Screen& screen);
	void Process(Player& players, Screen& screen);
	void Draw(Screen& screen);

};

