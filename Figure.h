#pragma once
#include "Vec2.h"
#include "Screen.h"
#include "Player.h"


class Figure
{
public:
	Figure();
	//調整/////////////////////////////////////////
	static const int FigureMax = 500;
	float Area(Player& player ,Screen screen);
	float RadianMin(Player& player);
	float RadianMax(Player& player);
	///////////////////////////////////////////////

	virtual void draw(){};
	virtual void set() {};
	virtual void respon() {};
	virtual bool IsInStage() { return 0; };
	bool cheakdraw(Player player, Vec2 Position,Screen screen, bool Flag);
	//画面内かチェック
	bool InScreen(Player player, Vec2 Position, Screen screen);

	Vec2 position;
	float radian;
	unsigned int color;
	bool flag;
	int cooltime;
	//消
	float stage = 10000;
private:
	
};

class llipse:public Figure
{
public:
	llipse();
	void draw(Screen& screen, Player& players);
	void set(Player& player,Screen screen);
	void respon(Player player, Screen screen);
	bool IsInStage(float stage);
private:

};

class Triangle:public Figure
{
public:
	Triangle();
	void draw(Screen& screen);
	void set(Player& player,Screen screen);
	void respon(Player player, Screen screen);
	bool IsInStage(float stage);

	Vec2 top_position;
	Vec2 right_position;
	Vec2 left_position;
private:

};

class Quadrangle:public Figure
{
public:
	Quadrangle();
	void draw(Screen& screen);
	void set(Player& player, Screen screen);
	void respon(Player player, Screen screen);
	bool IsInStage(float stage);

	Vec2 top_left_position;
	Vec2 top_right_position;
	Vec2 bottom_left_position;
	Vec2 bottom_right_position;
private:
	float checkroll(float Theta);
	float top_right = 0.0f;
	float bottom_left = 0.0f;
	float bottom_right = 0.0f;
};

