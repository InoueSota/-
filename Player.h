#pragma once
#include <Novice.h>
#include "Vec2.h"
#include "Screen.h"
#include "easing.h"

class Player
{
public:

	Player();
	~Player();

	//ïœêî
	Vec2 pos;
	Vec2 center;
	Vec2 add;
	Vec2 tmppos;
	float deg;
	float radius;

	int Reverse;
	int incDeg;
	int Length;

	bool isHit;


	bool isScroll;
	Vec2 tmpCenpos;
	Vec2 tmpMovepos;
	float easingt;
	float incT;

	//ä÷êî
	void Init();
	void SetPlayers(Player& players);
	virtual void CircleProcess(Player& players) {};
	virtual void SetDegree() {};
	void SetScrollPos(Screen& screen, Player& players, char prekeys, char keys);
	void Process(Player& players, char prekeys, char keys, char predik_d, char dik_d);
	void Draw(Screen& screen);
private:

};

class CircleA : public Player {
public:
	void CircleProcess(Player& players);
	void SetDegree();
};

class CircleB : public Player {
public:
	void CircleProcess(Player& players);
	void SetDegree();
};