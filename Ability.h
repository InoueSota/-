#pragma once
#include "Player.h"

class Bubble{
public:

	Bubble() {
		Init();
	}

	static const int kBubbleMax = 30;
	static const int kBubbleTimeMax = 120;
	static const int kBubbleStanFrame = 120;
	static const int kBubbleInterval = 2;
	static const int kBubbleDistance = 100;

	Vec2 pos[kBubbleMax];
	Vec2 direvelo[kBubbleMax];
	Vec2 velo[kBubbleMax];
	bool isOccur[kBubbleMax];
	bool isRelease[kBubbleMax];
	int Shotframe[kBubbleMax];
	int Longpressframe;
	unsigned int color = 0xE5C210FF;
	float spd = 5;
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
	Vec2 Toppos;
	float spd;
	bool isTrigger;
	bool isOccur;
	bool isLoadTexture;
	int delayframe;
	int shotframe;
	int slashImage;	//画像用変数

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
		SRAND();
	}

	static const int kBeamSizeMax = 120;
	static const int kBeamTimeMax = 90;
	static const int kBeamInterval = 180;

	static const int kLineMax = 50;
	static const int kLineLife = 100;

	/*　ビーム変数　*/
	Quad op;
	Quad pos1, pos2;
	bool isOccur;
	bool isLoadTexture;
	int frame;
	int shotframe;
	int Lefttop1, Lefttop2;	//画像用変数
	int beamImage;			//画像用変数

	/*　ライン変数　*/
	Quad lineop;
	Quad linepos1[kLineMax], linepos2[kLineMax];
	Matrix33 linemat1, linemat2;
	Vec2 direvelo1, direvelo2;
	Vec2 velo1, velo2;
	Vec2 tmpcenter;
	float tmpdeg;
	int lineframe;
	int life[kLineMax];
	int spd;

	void Init();
	void Make(Player& players, Screen& screen);
	void Move(Player& players, Screen& screen);
	void Process(Player& players, Screen& screen);
	void Draw(Screen& screen);

	void MoveLine(Player& players, Screen& screen);

};

