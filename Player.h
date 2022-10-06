#pragma once
#include <Novice.h>
#include "Vec2.h"
#include "Screen.h"

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

	//ä÷êî
	void Init();
	void SetPlayers(Player& players);
	virtual void CircleProcess(Player& players) {};
	virtual void SetDegree() {};
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