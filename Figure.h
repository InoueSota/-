#pragma once
#include "Vec2.h"
#include "Screen.h"
#include "Player.h"

class Figure
{
public:

	//����/////////////////////////////////////////
	static const int FigureMax = 500;
	static const int Area = 5000;
	static const int RadianMin = 5;
	static const int RadianMax = 50;
	///////////////////////////////////////////////

	virtual void draw(){};
	virtual void set() {};
	virtual void respon() {};
	bool cheakdraw(Player player, Vec2 Position, bool Flag);
	//��ʓ����`�F�b�N
	bool InScreen(Player player, Vec2 Position);

	Vec2 position;
	float radian;
	unsigned int color;
	bool flag;
private:
	
};

class llipse:public Figure
{
public:
	llipse();
	void draw(Screen& screen);
	void set(int x,int y,int Radian);
	void respon(Player player);
private:

};

class Triangle:public Figure
{
public:
	Triangle();
	void draw(Screen& screen);
	void set(int x, int y, int Radian,float theta);
	void respon(Player player);

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
	void set(int x, int y,int Radian, float theta);
	void respon(Player player);

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

