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
	virtual void CircleProcess() {};
	virtual void SetDegree() {};
	void Process(char prekeys, char keys, char predik_d, char dik_d);
	void Draw(Screen& screen);
private:

};

class CircleA : public Player {
public:
	void CircleProcess();
	void SetDegree();
};

class CircleB : public Player {
public:
	void CircleProcess();
	void SetDegree();
};